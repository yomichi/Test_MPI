#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
  int rank, size;
  int N;
  int *sendbuf, *recvbuf;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  N = 3;
  sendbuf = (int *)malloc(N * sizeof(int));
  recvbuf = (int *)malloc(N * size * sizeof(int));
  for (int i = 0; i < N; i++) {
    sendbuf[i] = rank * N + i;
  }

  MPI_Gather(sendbuf, N, MPI_INT, recvbuf, N, MPI_INT, 0, MPI_COMM_WORLD);
  if (rank == 0) {
    printf("first result\n");
    for(int r = 0; r < size; r++) {
      printf("%d: ", r);
      for(int i = 0; i < N; i++) {
        printf("%d ", recvbuf[r * N + i]);
      }
      printf("\n");
    }
  }

  for (int i = 0; i < N; i++) {
    sendbuf[i] = (size+rank) * N + i;
  }

  MPI_Gather(sendbuf, N, MPI_INT, recvbuf, N, MPI_INT, 0, MPI_COMM_WORLD);
  if (rank == 0) {
    printf("\nsecond result\n");
    for(int r = 0; r < size; r++) {
      printf("%d: ", r);
      for(int i = 0; i < N; i++) {
        printf("%d ", recvbuf[r * N + i]);
      }
      printf("\n");
    }
  }

  free(recvbuf);
  free(sendbuf);
  MPI_Finalize();
  return 0;
}
