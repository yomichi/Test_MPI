#include <string>
#include <sstream>
#include <fstream>
#include <unistd.h>

#include <mpi.h>

int main(int argc, char **argv){
  MPI_Init(&argc, &argv);

  int nprocs=1, rank=0;
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  std::stringstream ss;
  ss << "env_" << rank << ".dat";

  std::ofstream ofs(ss.str().c_str());

  extern char **environ;
  char **envs = environ;
  while(*envs){
    char *env = *envs;
    ofs << env << std::endl;
    ++envs;
  }

  MPI_Finalize();
  return 0;
}
