cmake_minimum_required(VERSION 3.24)
project(COMP9024_Bevis C)

set(CMAKE_C_STANDARD 11)

add_executable(test test.c)
add_executable(palindrome palindrome.c)
add_executable(llcreate llcreate.c )
add_executable(llsplit llsplit.c)
add_executable(Graph Graph.c Graph.h graphAnalyser.c)
add_executable(Graph2 Graph.c Graph.h cycleCheck.c)
add_executable(WGraph WGraph.c popularityRank.c)
add_executable(Warshall 0702.Warshall.c)
add_executable(Dij WGraph.c WGraph.h PQueue.c PQueue.h dijkstra.c dij/dijkstra.c dij/dijkstra.c lab/main.c)

