#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
 * I implement the stack used the LinkedList
 */

/*
 * Rename the char type of pointer as string.
 */
typedef char* string;

/*
 * Rename the data struct as stack
 */
typedef struct StackRepr *stack;

/*
 * Define the data struct 'Node', used to store the info of the stack
 */
typedef struct node {
    string data;
    struct node *next;
} *Node;

/*
 * Define the data struct 'Node'
 * Contain node and the number of the nodes
 *
 */
typedef struct StackRepr {
    Node first;
    int total;
} *stack;


/*
 * Create the new stack
 * Allocate the dynamic memory for stack which could suitable for the datastruct StackRepr
 * You must free the memory after use this function
 */
stack stack_create() {
    stack newStack = malloc(sizeof (struct StackRepr));
    newStack->first = NULL;
    newStack->total = 0;

    return newStack;
}

/*
 * Free the memory of every node in the stack
 * Free empty stack
 */
void stack_destroy(stack s) {
    if (s == NULL) {
        return;
    }


    Node curNode = s->first;
    while (curNode != NULL) {
        Node nextNode = curNode->next;
        free(curNode->data);
        free(curNode);
        curNode = nextNode;
    }

    free(s);
    return;
}

/*
 * Create a new node
 * Push the given data into the new node and push it onto the top of the stack
 */
void stack_push(stack s, string data) {
    Node newNode = malloc(sizeof(struct node));
    newNode->data = malloc(sizeof(char) * (strlen(data) + 1));  // 为data分配内存

    strcpy(newNode->data, data);
    newNode->next = s->first;
    s->first = newNode;
    s->total++;
    return;
}

/*
 * Removes and returns the top element of the stack
 */
string stack_pop(stack s) {
    if (s == NULL || s->first == NULL) {
        return NULL;
    }

    Node topNode = s->first;
    string topData = topNode->data;
//    free(topNode->data);
    s->first = topNode->next;
    free(topNode);
    s->total--;

    return topData;
}

/*
 * Returns the top element of the stack but not removing it
 */
string stack_peek(stack s) {
    if (s == NULL || s->first == NULL) {
        return NULL;
    }
    return s->first->data;
}

/*
 * Checks whether the stack is empty or not
 */
bool stack_empty(stack s) {
    return s == NULL || s->total == 0;
}

