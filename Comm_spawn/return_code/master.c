#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv)
{
  int mpisize, mpirank;
  char *spawn_argv_success[] = {"0", NULL};
  char *spawn_argv_fail[] = {"1", NULL};
  int maxprocs = (argc>1 ? atoi(argv[1]): 1);
  MPI_Info info;
  MPI_Comm inter_comm;
  MPI_Status mpistatus;
  int *universe_size, usize_flag;
  int ret;
  int iproc;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &mpisize);
  MPI_Comm_rank(MPI_COMM_WORLD, &mpirank);

  MPI_Comm_get_attr(MPI_COMM_WORLD, MPI_UNIVERSE_SIZE, &universe_size, &usize_flag);
  if(usize_flag){
    printf("MPI_UNIVERSE_SIZE: %d\n", *universe_size);
  }

  printf("MPI_size: %d\n", mpisize);

  MPI_Info_create(&info);

  MPI_Comm_spawn("./worker", spawn_argv_success, maxprocs, info, 0, MPI_COMM_SELF, &inter_comm, MPI_ERRCODES_IGNORE);

  for(iproc=0; iproc<maxprocs; ++iproc){
    MPI_Recv(&ret, 1, MPI_INT, iproc, 0, inter_comm, &mpistatus);
    printf("return code from %d: %d\n", iproc, ret);
  }

  MPI_Comm_spawn("./worker", spawn_argv_fail, maxprocs, info, 0, MPI_COMM_SELF, &inter_comm, MPI_ERRCODES_IGNORE);
  for(iproc=0; iproc<maxprocs; ++iproc){
    MPI_Recv(&ret, 1, MPI_INT, iproc, 0, inter_comm, &mpistatus);
    printf("return code from %d: %d\n", iproc, ret);
  }

  MPI_Info_free(&info);

  MPI_Finalize();
  return 0;
}
