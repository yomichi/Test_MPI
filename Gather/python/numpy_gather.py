import sys
import numpy as np
from mpi4py import MPI

def gather(N):
    comm = MPI.COMM_WORLD
    size = comm.Get_size()
    rank = comm.Get_rank()

    send = np.array([rank * N + i for i in range(N)], dtype="i")
    if rank == 0:
        recv = np.empty([size, N], dtype="i")
    else:
        recv = np.empty([0,0], dtype="i")
    comm.Gather(send, recv, root=0)
    if rank == 0:
        for r in range(size):
            print(f"{r}:", end="")
            for x in recv[r, :]:
                print(f" {x}", end="")
                sys.stdout.flush()
            print()
        print()

gather(2)
gather(3)
