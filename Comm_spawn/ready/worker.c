#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv)
{
  MPI_Comm parent;
  int nprocs=-1, rank=-1;
  int ret=12345;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  printf("I'm %d of %d\n", rank, nprocs);

  MPI_Comm_get_parent(&parent);
  if(parent != MPI_COMM_NULL){
    printf("I'm spawned by MPI_Comm_spawn\n");
    MPI_Send(&ret, 1, MPI_INT, 0, 0, parent);
  }

  MPI_Finalize();
  return 0;
}
