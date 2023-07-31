/*
 * degreeDetermine(verticesNumbers, g): O（N^2）
 *  Input graph g
 *  iterate the graph to determine verticals connected or not
 *      if true: degree++
 *      if find degree > max: maxDegree = degree
 *      if find degree < min: minDegree =  degree
 *  Determine which vertical's degree equals to max/min degrees
 *
 * trianglesOutput(int verticesNumbers, Graph g):O（N^3）
 *      Search every three verticals
 *      if they are connected:
 *          return
 *
 *
 */

#include <stdio.h>
#include "Graph.h"


void degreeDetermine(int verticesNumbers, Graph graph);

void trianglesOutput(int verticesNumbers, Graph g);

int main() {
    // The verticals of Graph
    int verticesNumbers;
    printf("Enter the number of vertices: ");
    scanf("%d", &verticesNumbers);
    Graph g = newGraph(verticesNumbers);

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
        insertEdge(g, edge);
        printf("Enter an edge (from): ");
    }
    printf("Done.\n");
    showGraph(g);

    // Calculate the Max and min degrees and which verticals contains the max or min dedree
    degreeDetermine(verticesNumbers, g);

    // Find and output the triangles
    trianglesOutput(verticesNumbers, g);

    freeGraph(g);
    return 0;
}

void trianglesOutput(int verticesNumbers, Graph g) {
    printf("Triangles:\n");
    // Search every third verticals and determine whether they are connected or not
    for (int i = 0; i < verticesNumbers; i++) {
        for (int j = i+1; j < verticesNumbers; j++) {
            for (int k = j+1; k < verticesNumbers; k++) {
                if (adjacent(g, i, j) == true && adjacent(g, i, k) == true && adjacent(g, k, j) == true){
                    printf("%d-%d-%d\n",i,j,k);
                }
            }
        }
    }
}

void degreeDetermine(int verticesNumbers, Graph g) {
    int minDegree = verticesNumbers;
    int maxDegree = 0;

    for (int i = 0; i < verticesNumbers; i++) {
        int degree = 0;
        for (int j = 0; j < verticesNumbers; j++) {
            if (adjacent(g, i, j) == true) {
                degree++;
            }

        }
        if (degree < minDegree){
            minDegree = degree;
        }
        if (degree > maxDegree){
            maxDegree = degree;
        }
    }

    printf("Minimum degree: %d\n", minDegree);
    printf("Maximum degree: %d\n", maxDegree);
    printf("Nodes of minimum degree: \n");

    for (int i = 0; i < verticesNumbers; i++) {
        int degree = 0;
        for (int j = 0; j < verticesNumbers; j++) {
            if (adjacent(g, i, j) == true) {
                degree++;
            }

        }
        if (degree == minDegree) {
            printf("%d\n", i);
        }

    }

    printf("Nodes of maximum degree: \n");
    for (int i = 0; i < verticesNumbers; i++) {
        int degree = 0;
        for (int j = 0; j < verticesNumbers; j++) {
            if (adjacent(g, i, j) == true) {
                degree++;
            }

        }
        if (degree == maxDegree) {
            printf("%d\n", i);
        }

    }
}


