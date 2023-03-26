#include <PCU.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

int main(int argc, char** argv) {
  if(argc != 2) {
    std::abort();
  }
  const int ndups = std::atoi(argv[1]);
  static constexpr int ncoms = 2;
  MPI_Init(&argc, &argv);
  PCU_Comm_Init();
  MPI_Comm comms[ncoms];
  int rank, size;
  for(int i=0; i<ncoms; ++i) {
    MPI_Comm_dup((i%ncoms==0)?MPI_COMM_WORLD:MPI_COMM_SELF, &comms[i]);
  }
  std::vector<int> data(100, 5); 
  for( int i=0; i<ndups; ++i) {
    auto comm = comms[i%ncoms];
    rank = MPI_Comm_rank(comm, &rank);
    size = MPI_Comm_rank(comm, &size);
    PCU_Switch_Comm(comm);
    PCU_Comm_Begin();
    PCU_Comm_Write((size==1)?0:i%(size-1), data.data(), data.size()*sizeof(int));
    PCU_Comm_Send();
    void * recv;
    int recv_from;
    size_t recv_size;
    while(PCU_Comm_Read(&recv_from, &recv, &recv_size)) {}

  }
  for(int i=0; i<ncoms; ++i) {
    MPI_Comm_free(&comms[i]);
  }
  PCU_Comm_Free();
  MPI_Finalize();
}
