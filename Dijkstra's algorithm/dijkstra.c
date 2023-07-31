////
//// Created by Bevis on 30/3/2023.
////
//// Starting code for Dijkstra's algorithm ... COMP9024 23T1
//
//#include <stdio.h>
//#include <stdbool.h>
//#include "PQueue.h"
//
//#define VERY_HIGH_VALUE 999999
//
//void dijkstraSSSP(Graph g, Vertex source) {
//    int  dist[MAX_NODES];
//    int  pred[MAX_NODES];
//    bool vSet[MAX_NODES];  // vSet[v] = true <=> v has not been processed
//    int s;
//
//    PQueueInit();
//    int nV = numOfVertices(g);
//    for (s = 0; s < nV; s++) {
//        joinPQueue(s);
//        dist[s] = VERY_HIGH_VALUE;
//        pred[s] = -1;
//        vSet[s] = true;
//    }
//    dist[source] = 0;
//
//    while (!PQueueIsEmpty()) {
//        Vertex u = leavePQueue(dist);
//        vSet[u] = false;
//        for (Vertex v = 0; v < nV; v++) {
//            if (adjacent(g, u, v)) {
//                int newDist = dist[u] + adjacent(g, u, v);
//                if (newDist < dist[v]) {
//                    dist[v] = newDist;
//                    pred[v] = u;
//                    if (vSet[v]) {
//                        joinPQueue(v);
//                        vSet[v] = false;
//                    }
//                }
//            }
//        }
//    }
//
//    for (Vertex i = 0; i < nV; i++) {
//        printf("%d: ", i);
//        if (dist[i] == VERY_HIGH_VALUE) {
//            printf("no path\n");
//        } else {
//            int path[MAX_NODES];
//            int count = 0;
//            Vertex current = i;
//            while (current != source) {
//                path[count++] = current;
//                current = pred[current];
//            }
//            path[count] = source;
//            printf("distance = %d, shortest path: %d", dist[i], path[count]);
//            for (int j = count - 1; j >= 0; j--) {
//                printf("-%d", path[j]);
//            }
//            printf("\n");
//        }
//    }
//
//}
//
//void reverseEdge(Edge *e) {
//    Vertex temp = e->v;
//    e->v = e->w;
//    e->w = temp;
//}
//
//int main(void) {
//    Edge e;
//    int  n, source;
//
//    printf("Enter the number of vertices: ");
//    scanf("%d", &n);
//    Graph g = newGraph(n);
//
//    printf("Enter the source node: ");
//    scanf("%d", &source);
//    printf("Enter an edge (from): ");
//    while (scanf("%d", &e.v) == 1) {
//        printf("Enter an edge (to): ");
//        scanf("%d", &e.w);
//        printf("Enter the weight: ");
//        scanf("%d", &e.weight);
//        insertEdge(g, e);
//        reverseEdge(&e);               // ensure to add edge in both directions
//        insertEdge(g, e);
//        printf("Enter an edge (from): ");
//    }
//    printf("Done.\n");
//
//    dijkstraSSSP(g, source);
//    freeGraph(g);
//    return 0;
//}