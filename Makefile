# Set your ArgoDSM installation directory
ARGO_INSTALL_DIRECTORY=${HOME}/libraries/argodsm

CXX      =mpic++
CXXFLAGS =-O3 -fopenmp

IDFLAGS +=-I${ARGO_INSTALL_DIRECTORY}/include/argo
LDFLAGS +=-L${ARGO_INSTALL_DIRECTORY}/lib
LDFLAGS +=-Wl,-rpath=${ARGO_INSTALL_DIRECTORY}/lib
LDLIBS  +=-largo -largobackend-mpi

all: daxpy_dsm daxpy_omp

daxpy_dsm: daxpy_dsm.cpp
	$(CXX) $(CXXFLAGS) -o $@.out $(IDFLAGS) $(LDFLAGS) $< $(LDLIBS)

daxpy_omp: daxpy_omp.cpp
	$(CXX) $(CXXFLAGS) -o $@.out $<

clean:
	rm -f *.out
