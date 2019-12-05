#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
    int rank; //rank of the process
    int size; //number of processes

    MPI_Init(&argc,&argv); //inititate MPI environment
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    printf("Hello world from process %d of %d\n",rank,size);
    MPI_Finalize();
    return 0;
}
