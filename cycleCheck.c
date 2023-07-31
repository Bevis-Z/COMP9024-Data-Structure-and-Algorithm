/*
 * hasCycle(G):
 *  Input graph G
 *  Output true if G has a cycle, false otherwise
 *
 *  choose any vertex v∈G
 *
 *  return dfsCycleCheck(G,v,NULL)
 *
 * dfsCycleCheck(G,v,p):
 *  mark v as visited
 *  for each (v,w)∈edges(G) do
 *      if w is marked as visited and w is not the parent of v then
 *      return true // found cycle
 *      else if w is not marked as visited and dfsCycleCheck(G,w,v) then
 *      return true
 * end for
 * unmark v as visited
 * return false
 */

#include "Graph.h"
#include <stdio.h>


typedef struct GraphRep {
    int  **edges;   // adjacency matrix
    int    nV;      // #vertices
    int    nE;      // #edges
} GraphRep;

// DFS to determine it has cycle or not
bool dfsCycleCheck(Graph g, int v, bool visited[], int parent[]);

bool hasCycle(Graph g);


int main() {
    // The verticals of Graph
    int verticesNumbers;
    printf("Enter the number of vertices: ");
    scanf("%d", &verticesNumbers);
    Graph graph = newGraph(verticesNumbers);

    printf("Enter an edge (from): ");
    // Define two verticals
    int v, w;

    while (scanf("%d", &v) != 0) {
        printf("Enter an edge(to): ");
        if (scanf("%d", &w) != 1) {
            break;
        }
        // Create Edge
        Edge edge = {v, w};
        //insert edge into graph
        insertEdge(graph, edge);
        printf("Enter an edge (from): ");
    }
    printf("Done.\n");

    if(hasCycle(graph) == true) {
        printf("The graph has a cycle.");
    } else {
        printf("The graph is acyclic.");
    }
    return 0;
}


bool dfsCycleCheck(Graph g, int v, bool *visited, int *parent) {
    visited[v] = true;

    // Recurse on all adjacent vertices
    for (int w = 0; w < numOfVertices(g); w++) {
        if (adjacent(g, v, w)) { //Check if the v is adjacent with w
            // If w has not been visited, recurse on it
            if (!visited[w]) {
                parent[w] = v;
                // set the parent of vertex w to v
                if (dfsCycleCheck(g, w, visited, parent)) {
                    // recursive call to dfsCycleCheck function
                    return true;
                }
            }
                // If w has been visited and is not the parent of v, a cycle exists
            else if (w != parent[v]) {
                return true;
            }
        }
    }

    return false;
}

bool hasCycle(Graph g) {
    int numVertices = numOfVertices(g);
    bool visited[numVertices];
    int parent[numVertices];


    for (int i = 0; i < numVertices; i++) {
        // Initialize visited and parent arrays
        visited[i] = false;
        parent[i] = -1;
    }


    for (int i = 0; i < numVertices; i++) {
        // Call dfsCycleCheck() for each unvisited vertex
        if (!visited[i] && dfsCycleCheck(g, i, visited, parent)) {
            return true;
        }
    }

    return false;
}
