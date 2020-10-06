#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char **argv)
{
  int num_spawn = 2;
  int* err_spawn = (int*)calloc(sizeof(int), num_spawn);
  MPI_Status status;
  int ret=-1;
  int remotesize=-1;

  printf("master starts\n");

  MPI_Comm remote;
  MPI_Init(&argc, &argv);

  char* as[] = {">", "hoge.dat", 0};
  MPI_Comm_spawn("worker", as, num_spawn, MPI_INFO_NULL, 0, MPI_COMM_WORLD, &remote, err_spawn);

  sleep(2);

  MPI_Comm_remote_size(remote, &remotesize);

  MPI_Comm_free(&remote);

  MPI_Finalize();

  free(err_spawn);
  printf("master ends\n");
  return 0;
}
