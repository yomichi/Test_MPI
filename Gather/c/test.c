#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

void gather(int N){
  int rank, size;
  int *sendbuf, *recvbuf;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  sendbuf = (int *)malloc(N * sizeof(int));
  recvbuf = (int *)malloc(N * size * sizeof(int));
  for (int i = 0; i < N; i++) {
    sendbuf[i] = rank * N + i;
  }

  MPI_Gather(sendbuf, N, MPI_INT, recvbuf, N, MPI_INT, 0, MPI_COMM_WORLD);
  if (rank == 0) {
    for(int r = 0; r < size; r++) {
      printf("%d: ", r);
      for(int i = 0; i < N; i++) {
        printf("%d ", recvbuf[r * N + i]);
      }
      printf("\n");
    }
    printf("\n");
  }
  free(recvbuf);
  free(sendbuf);
}

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);
  gather(2);
  gather(3);

  MPI_Finalize();
  return 0;
}
