//
// Created by Bevis on 20/3/2023.
//
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "WGraph.h"

typedef struct {
    int vertex;
    float value;
} vertexValue;

void popularityRankCal(vertexValue *VertexValue, int verticesNumbers, Graph g);

void bubbleSort(vertexValue vertexValue01[], int size) ;


int main() {
    vertexValue VertexValue[100];
    // The verticals of Graph
    int verticesNumbers;
    printf("Enter the number of vertices: ");
    scanf("%d", &verticesNumbers);
    Graph g = newGraph(verticesNumbers);

    printf("Enter an edge (from): ");
    // Define two verticals
    int v, w;

    while (scanf("%d", &v) == 1) {
        printf("Enter an edge(to): ");
        if (scanf("%d", &w) != 1) {
            break;
        }
        // Create Edge
        Edge edge = {v, w, 1};
        //insert edge into graph
        insertEdge(g, edge);
        printf("Enter an edge (from): ");
    }
    printf("Done.\n\n");

    popularityRankCal(VertexValue, verticesNumbers, g);


    freeGraph(g);
    return 0;

}

void popularityRankCal(vertexValue *VertexValue, int verticesNumbers, Graph g) {// printf("%d",verticesNumbers);
    for (int i = 0; i < verticesNumbers; i++) {
        int inDegree = 0;
        int outDegree = 0;
        double pupolarityRank = 0;
        for (int j = 0; j < verticesNumbers; j++) {
            if (adjacent(g, i, j) != 0) {
                outDegree += adjacent(g, i, j);
                // printf("fuch%d", outDegree);

            }
            if (adjacent(g, j, i) != 0) {
                inDegree += adjacent(g, j, i);
            }
            // printf("fuck%d", outDegree);

        }
        if (outDegree == 0) {
            pupolarityRank = inDegree / 0.5;
        } else if (outDegree != 0) {
            pupolarityRank = (double)inDegree / outDegree;
        }

        VertexValue[i].vertex = i;
        VertexValue[i].value = pupolarityRank;

    }

    printf("Popularity ranking:\n");

    bubbleSort(VertexValue, verticesNumbers);

    // 输出排序结果
// printf("\nSorted:\n");
    for (int i = 0; i < verticesNumbers; i++) {
        printf("%d %.1f\n", VertexValue[i].vertex, VertexValue[i].value);
    }
}


void bubbleSort(vertexValue vertexValue01[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (vertexValue01[j].value < vertexValue01[j + 1].value) {
                vertexValue01[j].value += vertexValue01[j + 1].value;
                vertexValue01[j + 1].value = vertexValue01[j].value - vertexValue01[j + 1].value;
                vertexValue01[j].value -= vertexValue01[j + 1].value;

                vertexValue01[j].vertex += vertexValue01[j + 1].vertex;
                vertexValue01[j + 1].vertex = vertexValue01[j].vertex - vertexValue01[j + 1].vertex;
                vertexValue01[j].vertex -= vertexValue01[j + 1].vertex;
            }
        }
    }
}

