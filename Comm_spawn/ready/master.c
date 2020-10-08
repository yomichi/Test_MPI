#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv)
{
  int num_spawn = 2;
  int num_loop = 60;
  int i;
  int* err_spawn = (int*)calloc(sizeof(int), num_spawn);
  MPI_Status status;

  int ret=-1;

  MPI_Comm child;
  MPI_Init(&argc, &argv);

  printf("I'm parent\n");

  for (i = 0; i < num_loop; i++){
    MPI_Comm_spawn("./worker", MPI_ARGV_NULL, num_spawn, MPI_INFO_NULL, 0, MPI_COMM_SELF, &child, err_spawn);
    MPI_Recv(&ret, 1, MPI_INT, 0, 0, child, &status);
    MPI_Comm_disconnect(&child);
    printf("Master received value: %d\n", ret);
  }

  free(err_spawn);

  MPI_Finalize();

  return 0;
}
