#include <omp.h>
#include <iostream>
#include <cassert>
#include <chrono>

int main(int argc, char *argv[])
{
	constexpr double alpha = 3.14;
	constexpr std::size_t array_size = 65536;

	// Allocate shared data
	double *x = new double[array_size];
	double *y = new double[array_size];

	// Initialize data
	#pragma omp parallel for
	for(std::size_t i=0; i<array_size; i++){
		x[i] = 42.0;
		y[i] = 0.0;
	}

	// Execute calculation
	#pragma omp parallel for
	for(std::size_t i=0; i<array_size; i++){
		y[i] += x[i] * alpha;
	}
	
	for(std::size_t i=0; i<array_size; i++){
		assert(y[i] == 42.0 * alpha);
	}
	std::cout << "DAXPY_OMP successful." << std::endl;

	// Delete shared data
	delete[] y;
	delete[] x;

	return 0;
}
