#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv)
{
  MPI_Comm parent;
  int ret = (argc>1 ? atoi(argv[1]) : 0);
  int mpisize;
  int mpirank;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &mpirank);
  printf("worker %d start\n", mpirank);

  MPI_Comm_get_parent(&parent);
  if(parent != MPI_COMM_NULL){
    MPI_Send(&ret, 1, MPI_INT, 0, 0, parent);
  }
  

  MPI_Finalize();
  printf("worker %d finish\n", mpirank);

  return ret;
}
