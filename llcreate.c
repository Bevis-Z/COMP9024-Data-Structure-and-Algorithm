//
// Created by Bevis on 3/3/2023.
//
#include <stdio.h>
#include <stdlib.h>

// define the Node Struct to store each value of the list
typedef struct Node {
    int data;
    struct Node *next;
} NodeT;

NodeT *getNode();

NodeT *getNode1(NodeT *list, NodeT *newNode);

// free the memory
void freeLL(NodeT *list) {
    while (list != NULL) {
        NodeT *temp = list;
        list = list->next;
        free(temp);
    }
}

// display the list
void showLL(NodeT *list) {
    // Judge the list is NULL or not
    if (list != NULL) {
        printf("List is ");
    }
    // print the value
    while (list != NULL) {
        printf("%d", list->data);
        // if the next one still has the value print"-->"
        if (list->next != NULL) {
            printf("-->");
        }
        // Move node to the next
        list = list->next;
    }
    printf("\n");
}

// Give node their value
NodeT *joinLL(NodeT *list, int v) {
    NodeT *newNode = (NodeT *) malloc(sizeof(NodeT));
    newNode->data = v;
    newNode->next = NULL;

    return getNode1(list, newNode);

}

// Move node the next one and give its value
NodeT *getNode1(NodeT *list, NodeT *newNode) {
    if (list == NULL) {
        return newNode;
    }

    NodeT *curNode = list;
    while (curNode->next != NULL) {
        curNode = curNode->next;
    }
    curNode->next = newNode;
    return list;
}

// Create the list all, and use getNode() function to give value of the all list
// Print the list
// Free the memory
int main() {
    NodeT *all = getNode();

    printf("Done. ");
    showLL(all);
    freeLL(all);
    return 0;
}

NodeT *getNode() {
    #define MAXINUM 100
    NodeT *all = NULL;
    int value;
    char input[MAXINUM];

    printf("Enter an integer: ");
    while (fgets(input, sizeof(input), stdin) != NULL) {
        if (sscanf(input, "%d", &value) == 1) {
            all = joinLL(all, value);
        } else {
            break;
        }
        printf("Enter an integer: ");
    }
    return all;
}

