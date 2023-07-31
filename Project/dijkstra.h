////////////////////////////// DO NOT CHANGE THIS FILE. //////////////////////////////
// THIS FILE IS NOT SUBMITTED AND WILL BE PROVIDED AS IS DURING TESTING AND MARKING //
////////////////////////////// DO NOT CHANGE THIS FILE. //////////////////////////////

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"

/**
 * graph_worst_path
 * Calculates the worst path from a given source vertex to all other
 * vertices. Worst path is calculated by first determining the pagerank of
 * each vertex then finding the minimum cost (sum of pageranks) from the source
 * vertex to each other vertex.
 * 
 * Parameters:
 *     The graph to find worst paths in,
 *     The vertex to search from,
 *     The damping factor for pagerank calculations,
 *     The delta factor for pagerank calculations,
 */
void graph_worst_path(graph, string, double, double);

/**
 * graph_show_path
 * Prints the path traversed to reach the given destination vertex to stdout.
 *
 * NOTE: This assumes that `graph_worst_path()` has already been called to
 * calculate the path to this destination vertex.
 *
 * Printing should be in the following format:
 * source_vertex
 * -> vertex2
 * -> vertex3
 * ...
 * -> destination_vertex
 *
 * Parameters:
 *    The graph to print from,
 *    The destination vertex,
 */
void graph_show_path(graph, string);

#endif // DIJKSTRA_H
