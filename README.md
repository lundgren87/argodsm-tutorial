# ArgoDSM tutorial

This repository contains a simple OpenMP implementation
of the DAXPY kernel and it's corresponding ArgoDSM port
intended for the ArgoDSM presentation on Monday Nov 8
2021.

To build both versions, set the `ARGO_INSTALL_DIRECTORY`
to point to your local ArgoDSM installation and execute
`make`.

To execute the OpenMP version run:
```
./daxpy_omp
```

To execute the ArgoDSM version (on 2 nodes) run:
```
mpirun -n 2 ./daxpy_dsm
```
