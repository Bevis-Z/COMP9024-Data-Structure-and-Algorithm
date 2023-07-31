////////////////////////////// DO NOT CHANGE THIS FILE. //////////////////////////////
// THIS FILE IS NOT SUBMITTED AND WILL BE PROVIDED AS IS DURING TESTING AND MARKING //
////////////////////////////// DO NOT CHANGE THIS FILE. //////////////////////////////

#ifndef T_STRING
#define T_STRING

typedef char *string;

#endif // T_STRING

#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct GraphRepr *graph;

typedef double weight;

/**
 * graph_create
 * Allocates the required memory for a new graph.
 * 
 * Returns
 *     On success: Pointer to the new graph
 *     On error: NULL
 */
graph graph_create(void);

/**
 * graph_destroy
 * Frees all memory associated with a given graph.
 *
 * Parameters
 *     The graph to destroy
 */
void graph_destroy(graph);

/**
 * graph_show
 * Prints the contents of the graph to the given file.
 *
 * If the given file is NULL, print to stdout.
 * The graph should be printed in the following format:
 *      vertex1
 *      vertex2
 *      vertex3
 *      ...
 *      vertexN
 *      vertex1 vertex2 weight
 *      vertex2 vertex4 weight
 *      vertexN vertex4 weight
 * Where the name name of each vertex is first printed.
 * Then the directed edges between each vertex along with the edge weight is printed.
 *
 * Parameters
 *     The graph to print out,
 *     The file to print to
 */
void graph_show(graph, FILE *);

/**
 * graph_add_vertex
 * Adds a new vertex with a particular value to the graph.
 *
 * If a vertex with the same value already exists do not add a new vertex.
 *
 * Parameters
 *     The graph to add the vertex to,
 *     The vertex to add to the graph
 */
void graph_add_vertex(graph, string);

/**
 * graph_has_vertex
 * Determines whether a given graph has a given vertex.
 *
 * Parameters
 *     The graph to check against,
 *     The vertex to check for
 *
 * Returns
 *     true - Vertex was found in the graph
 *     false - Vertex was not found, or an error occurred
 */
bool graph_has_vertex(graph, string);

/**
 * graph_vertices_count
 * Counts the number of vertices in a given graph.
 *
 * Parameters
 *     The graph to count vertices from
 *
 * Returns
 *     On success - The number of vertices in the given graph
 *     On error - Simply return 0
 */
size_t graph_vertices_count(graph);

/**
 * graph_add_edge
 * Adds a new edge from a source vertex to a destination vertex in the graph.
 *
 * If an edge from the source vertex to the destination already exists, do not
 * add this edge (even if the weight is different!).
 * 
 * Parameters
 *     The graph to add the edge to,
 *     The source vertex,
 *     The destination vertex,
 *     The weight of this edge
 */
void graph_add_edge(graph, string, string, weight);

/**
 * graph_has_edge
 * Determines if an edge exists from the given source vertex to the given destination
 * vertex.
 *
 * Parameters
 *     The graph to search through,
 *     The source vertex,
 *     The destination vertex,
 *
 * Returns
 *     true - If edge exists FROM the source vertex TO the destination vertex,
 *     false - If that edge does not exist, or there was an error
 */
bool graph_has_edge(graph, string, string);

/**
 * graph_update_edge
 * Updates the weight of an edge from the given source vertex to the given destination
 * vertex.
 *
 * If no such edge exists, one should be created with the given weight.
 *
 * Parameters
 *     The graph to update the edge in,
 *     The source vertex,
 *     The destination vertex,
 *     The new weight of this edge
 */
void graph_update_edge(graph, string, string, weight);

/**
 * graph_get_edge
 * Gets the weight of the edge from the given source vertex to the given
 * destination vertex.
 *
 * Parameters
 *     The graph to get the edge weight from,
 *     The source vertex,
 *     The destination vertex,
 *
 * Returns
 *     On success: The weight of the specified edge
 *     On error: 0
 */
weight graph_get_edge(graph, string, string);

/**
 * graph_edges_count
 * Counts the number of outgoing + incoming edges to a given vertex.
 *
 * Parameters
 *     The graph to count edges in,
 *     The vertex to count edges of
 *
 * Returns
 *     The total number of outgoing + incoming edges to the given vertex
 */
size_t graph_edges_count(graph, string);

#endif //GRAPH_H
