project(trackmpicomm C CXX)
cmake_minimum_required(VERSION 3.23)

cmake_policy(SET CMP0074 NEW)

Find_package(MPI REQUIRED)
find_package(SCOREC REQUIRED)

add_executable(testmpi testmpi.cc)
target_link_libraries(testmpi PUBLIC MPI::MPI_C SCOREC::pcu)
