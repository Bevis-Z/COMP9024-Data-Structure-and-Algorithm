////////////////////////////// DO NOT CHANGE THIS FILE. //////////////////////////////
// THIS FILE IS NOT SUBMITTED AND WILL BE PROVIDED AS IS DURING TESTING AND MARKING //
////////////////////////////// DO NOT CHANGE THIS FILE. //////////////////////////////

#ifndef PAGERANK_H
#define PAGERANK_H

#include "graph.h"

/**
 * graph_pagerank
 * Calculates the pagerank of every vertex in the given graph, based on the
 * provided damping/delta values.
 * 
 * Parameters:
 *     The graph to search in,
 *     The damping factor to apply,
 *     The delta value to apply,
 */
void graph_pagerank(graph, double, double);

/**
 * graph_show_pagerank
 * Prints each url and corresponding pagerank to the given file.
 *
 * NOTE: This function assumes that `graph_pagerank()` has already been called.
 *
 * URLs should be sorted by:
 *     - Highest pagerank then
 *     - lexiographically
 *
 * Printing should be in the format below (Pageranks should be printed to 3dp)
 * url1 (pagerank)
 * url2 (pagerank)
 * url3 (pagerank)
 * url4 (pagerank)
 * url5 (pagerank)
 * url6 (pagerank)
 * ...
 * 
 * Parameters:
 *     The graph to show pageranks from,
 *     The file to print to,
 */
void graph_show_pagerank(graph, FILE *);

#endif // PAGERANK_H
