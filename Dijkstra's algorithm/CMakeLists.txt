cmake_minimum_required(VERSION 3.24)
project(COMP9024_Bevis C)

set(CMAKE_C_STANDARD 11)

add_executable(Dij WGraph.c WGraph.h PQueue.c PQueue.h dijkstra.c "../Week 7/BSTree.c")