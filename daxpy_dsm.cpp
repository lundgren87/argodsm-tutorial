#include "argo.hpp"

#include <omp.h>
#include <iostream>
#include <cassert>

int main(int argc, char *argv[])
{
	constexpr double alpha = 3.14;
	constexpr std::size_t array_size = 65536;

	// Initialize ArgoDSM
	argo::init(128*1024*1024, 128*1024*1024);

	// Allocate shared data through ArgoDSM
	double *x = argo::conew_array<double>(array_size);
	double *y = argo::conew_array<double>(array_size);

	// Get ArgoDSM node id and number of nodes
	const int node_id = argo::node_id();
	const std::size_t num_nodes = argo::number_of_nodes();

	// Calculate this node's chunk to work on
	const std::size_t chunk_size = array_size/num_nodes;
	const std::size_t start = node_id*chunk_size;
	const std::size_t end = start+chunk_size;

	// Initialize data for this node's chunk
	#pragma omp parallel for
	for(std::size_t i=start; i<end; i++){
		x[i] = 42.0;
		y[i] = 0.0;
	}
	// Propagate initialization to all nodes
	argo::barrier();

	// Execute calculation for this node's chunk	
	#pragma omp parallel for
	for(std::size_t i=start; i<end; i++){
		y[i] += x[i] * alpha;
	}
	// Wait for all nodes and propagate result
	argo::barrier();
	
	// Verify calculation on node 0
	if (node_id == 0) {
		for(std::size_t i=0; i<array_size; i++){
			assert(y[i] == 42.0 * alpha);
		}
		std::cout << "DAXPY_DSM successful." << std::endl;
	}

	// Deallocate shared data through ArgoDSM
	argo::codelete_array(x);
	argo::codelete_array(y);

	// Finalize ArgoDSM
	argo::finalize();

	return 0;
}
