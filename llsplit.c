//
// Created by Bevis on 5/3/2023.
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
    if (list != NULL) {
        printf("List is ");
    }
    while (list != NULL) {
        printf("%d", list->data);
        if (list->next != NULL) {
            printf("-->");
        }
        list = list->next;
    }
    printf("\n");
}

//Display the separate list
void showSplitLL(NodeT *list) {
    while (list != NULL) {
        printf("%d", list->data);
        if (list->next != NULL) {
            printf("-->");
        }
        list = list->next;
    }
}

// Split one list into two separate one used two pointer methods
// The fast point move 2 steps when the slow pointer move one step
// When the fast point move to the end, the slow pointer whill locate the value in the middle
void split(NodeT *list, NodeT **first, NodeT **second) {
    if (list == NULL || list->next == NULL) {
        *first = list;
        *second = NULL;
        return;
    }

    NodeT *slow = list;
    NodeT *fast = list->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *first = list;
    *second = slow->next;
    slow->next = NULL;
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
// Call the split function to split the list into two separate one
// Print list one and list two.
int main() {
    NodeT *all = getNode();
    NodeT *first, *second;

    printf("Done. ");
    showLL(all);
    split(all, &first, &second);
    if (first != NULL) {
        printf("First part is ");
        showSplitLL(first);
        printf("\n");
    }
    if (second != NULL) {
        printf("Second part is ");
    }
    showSplitLL(second);
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
