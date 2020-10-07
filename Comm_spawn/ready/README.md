# Small example for MPI_Comm_spawn

```
$ vim Makefile  # to modify compiler name and options 
$ make
$ mpiexec -np 1 ./master  # mpiexec may require some options to invoke MPI_Comm_spawn
```

Expected output is the following:

```
I'm parent
  I'm 0 of 1
  I'm spawned by MPI_Comm_spawn
Master received value: 12345
```
