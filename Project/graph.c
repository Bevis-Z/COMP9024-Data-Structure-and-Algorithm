#include "graph.h"
#include "pagerank.h"
#include "dijkstra.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <math.h>
//#include <vector.h>


typedef char *string;           // Define the string type
typedef double weight;
typedef struct listL *List;


typedef struct Node {
    string data;          // Store the string
    double weight;
    double oldRank;
    double pagerank;
    int index;
    int num_outgoing;
    List neigh;
    struct Node *next;    // pointer to the next node
} *Node;

struct listL {
    Node first;
    int total;
};

typedef struct GraphRepr {
    List vertices;
    int source;
//    double *oldrank;
//    double *pagerank;
} *graph;


// Create a new list in the graph
List createListInGraph() {
    List list = malloc(sizeof(struct listL));
    assert(list != NULL);
    list->first = NULL;
    list->total = 0;

    return list;
}

// Create a new graph
graph graph_create(void) {
    graph g = malloc(sizeof(struct GraphRepr));
    assert(g != NULL);
    g->vertices = createListInGraph();
    g->source = -1;
//    g->pagerank = NULL;
//    g->dist = NULL;
//    g->pred = NULL;

    return g;
}


// Check if a node with the given data exists in the list
Node existsList (List list, string data) {
    Node result = NULL;
    Node cur = list->first;
    while(cur != NULL) {
        if ( strcmp(cur->data, data) == 0) {
            result = cur;
            break;
        }
        cur = cur -> next;
    }
    return result;
}

// Create a new node in the graph with the given data and weight
Node makeNodeInGraph(string data, weight w) {
    Node newNode = malloc(sizeof (struct Node));
    assert(newNode!=NULL);

    newNode->data = malloc(sizeof(char) * (strlen(data) + 1));
    strcpy(newNode->data, data);
    newNode->pagerank = -1;
    newNode->oldRank = -1;

    newNode->weight = w;

    newNode->neigh = createListInGraph();
    newNode->next = NULL;
    newNode->index = -1;
    return newNode;
}


// Compare two values based on their weights
int compareTwo(double w1, string d1, double w2, string d2) {
    if (w1 > w2) {
        return 1;
    } else if (w1 < w2) {
        return -1;
    } else {
        return strcmp(d1, d2);
    }
}


// Insert a new node in the graph, ordered by weight value
void insertOrderValueInGraph(List list, string data, weight w) {

    if (list->first == NULL) {
        list->first = makeNodeInGraph(data, w);

//        list->total++;
    } else {
        Node cur = list->first;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        Node newNode = makeNodeInGraph(data, w);

        cur->next = newNode;
//        list->total++;
    }
}


// Insert a new edge between two nodes, v1 and v2, with the given weight
void insertListToNeighbours(List list, string v1, string v2, weight w) {
    Node cur = list->first;
    Node node1 = NULL, node2 = NULL;
    while (cur != NULL) {
        if (strcmp(cur->data, v1) == 0) {
            node1 = cur;
        }
        if (strcmp(cur->data, v2) == 0) {
            node2 = cur;
        }
        if (node1 != NULL && node2 != NULL) {
            break;
        }
        cur = cur->next;
    }
    if (node1 != NULL && node2 != NULL) {
        if (node1->neigh == NULL) {
            node1->neigh = createListInGraph();
        }
        // Check if v2 already exists as a neighbour, if not, add it to the end of the list
        Node newCur = node1->neigh->first;
        while (newCur != NULL) {
            if (strcmp(newCur->data, v2) == 0) {
                // v2 already exists as a neighbour, do nothing
                return;
            }
            newCur = newCur->next;
        }
        // Insert v2 as neighbour of v1 with the given weight
        insertOrderValueInGraph(node1->neigh, v2, w);
        node1->num_outgoing++;
    }
}


//  Prints the vertex data and its neighbour data
void showListWithNeighbours(graph g, FILE *output) {
    if (g->vertices != NULL && g->vertices->first != NULL) {
        Node cur = g->vertices->first;
        while (cur != NULL) {
            fprintf(output, "%s\n", cur->data);
            cur = cur->next;
        }
        cur = g->vertices->first;
        while (cur != NULL) {
            if (cur->neigh!=NULL) {
                Node neigh = cur->neigh->first;

                while (neigh!=NULL){
                    fprintf(output, "%s", cur->data);
                    fprintf(output, " %s %.3f\n", neigh->data, neigh->weight);
                    neigh = neigh->next;
                }
            }
            cur = cur->next;
        }
    }
}


// Free the memory of a graph
void graph_destroy(graph g) {
    if (g != NULL) {
        Node cur = g ->vertices-> first;
        Node next;
        while (cur!=NULL) {
            next = cur -> next;
            free(cur->data);
            free(cur);

            cur = next;
        }
        free(g);
    }

}


// Adds a new vertex to the graph
void graph_add_vertex(graph g, string v) {
    if (graph_has_vertex(g, v)) {
        return;
    }
    Node newNode = makeNodeInGraph(v, 0.0);           // Create a new node with the given data
    if (newNode == NULL) {
        return;
    }
    if (g->vertices->first == NULL) {                // If the list is empty, set the first node to be the new node
        g->vertices->first = newNode;
    } else {                                     // Otherwise, add the new node to the end of the list
        Node cur = g->vertices->first;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = newNode;
    }
    g->vertices->total++;                           // Update the total count
}

// Check whether the graph has this vertex or not
bool graph_has_vertex(graph g, string v) {
    if (g!=NULL) {
        return existsList(g->vertices, v) != NULL;
    }
    return false;
}



// Return the number of the vertices in the graph
size_t graph_vertices_count(graph g) {
    if (g!=NULL) {
        return g->vertices->total;
    }
    return 0;
}

// Link the edge in the graph
void graph_add_edge(graph g, string v1, string v2, weight w) {
    if (g != NULL && g->vertices->first != NULL) {
        insertListToNeighbours(g->vertices, v1, v2, w);
    }
}


// Check whether the graph has this edge or not
bool graph_has_edge(graph g, string v1, string v2) {
    if (g != NULL) {
        List neigh = (List)existsList(g->vertices, v1);
        return existsList(neigh, v2) != NULL;
    }
    return false;
}

// Update the weight of the existed edge
void graph_update_edge(graph g, string v1, string v2, weight w) {
    if (g!=NULL) {
        Node neigh = existsList(g->vertices, v1);
        Node node2 = existsList(neigh->neigh, v2);
        if (node2!=NULL) {
            node2->weight = w;
        }
    }

}


// Find the node corresponding to v1 in the graph
weight graph_get_edge(graph g, string v1, string v2) {
    Node node1 = g->vertices->first;
    while (node1 != NULL) {
        if (strcmp(node1->data, v1) == 0) {
            List neigh = node1->neigh;
            Node node2 = neigh->first;
            while (node2 != NULL) {
                if (strcmp(node2->data, v2) == 0) {
                    return node2->weight;
                }
                node2 = node2->next;
            }
            return 0;
        }
        node1 = node1->next;
    }
    return 0;
}

// Show the graph using the function showListWithNeighbours
void graph_show(graph g, FILE *output) {
    showListWithNeighbours(g, output);
}





void graph_pagerank(graph g, double damping_factor, double epsilon) {
    int N = g->vertices->total;
    Node cur = g->vertices->first;

    // Initialize pagerank and oldrank for all vertices
    while (cur != NULL) {
        cur->pagerank = 1.0 / N;
        cur->oldRank = 0.0;
        cur = cur->next;
    }

    double diff;
    do {
        diff = 0.0;
        cur = g->vertices->first;

        // Update oldrank for all vertices
        while (cur != NULL) {
            cur->oldRank = cur->pagerank;
            cur->pagerank = 0.0;
            cur = cur->next;
        }



        double sink_rank = 0.0;
        cur = g->vertices->first;

        // Calculate sink_rank
        while (cur != NULL) {
            if (cur->num_outgoing == 0) {
                sink_rank += (damping_factor * (cur->oldRank / N));
            }
            cur = cur->next;
        }

        cur = g->vertices->first;

        // Update pagerank for all vertices
        while (cur != NULL) {
            cur->pagerank += sink_rank + ((1.0 - damping_factor) / N);
            Node neigh = cur->neigh->first;            // Calculate sum of pagerank of in-neighbours
            while (neigh != NULL) {
                cur->pagerank += damping_factor * (neigh->oldRank / neigh->num_outgoing);
                neigh = neigh->next;
            }
            diff += fabs(cur->pagerank - cur->oldRank);
            cur = cur->next;
        }
    } while (diff > epsilon);
}




void graph_show_pagerank(graph g, FILE *file) {
    Node curr = g->vertices->first;
    while (curr != NULL) {
        fprintf(file, "%s (%f)\n", curr->data, curr->pagerank);
        curr = curr->next;
    }
}

void graph_worst_path(graph g, string source, double damping, double delta) {

}

void graph_show_path(graph g, string destination) {

}
