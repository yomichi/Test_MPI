cmake_minimum_required(VERSION 2.8.0 FATAL_ERROR)
project(hoge C)

find_package(OpenMP)
if(OPENMP_FOUND)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
endif(OPENMP_FOUND)

find_package(MPI)
if(MPI_FOUND)
  include_directories(${MPI_C_INCLUDE_PATH})
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${MPI_C_LINK_FLAGS}")
endif(MPI_FOUND)

add_executable(hoge test.c)
target_link_libraries(hoge "${MPI_C_LIBRARIES}")

message(STATUS ${CMAKE_C_COMPILER})
