#include <stdio.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char **argv)
{
  int nprocs=-1, rank=-1;
  int ret=12345;

  printf("worker starts\n");

  for(int i; i<argc; ++i){
    printf("%s ", argv[i]);
  }
  printf("\n");

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  for(int i=0; i<10; ++i){
    sleep(1);
    printf("%d\n",i);
  }

  MPI_Finalize();
  printf("worker ends\n");
  return 0;
}
