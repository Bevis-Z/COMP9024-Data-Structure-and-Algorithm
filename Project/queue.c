#include "queue.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef char* string;       // Define the string type


typedef struct node {
    string data;            // Store the string
    struct node *next;      // pointer to the next node
} *Node;


typedef struct list {
    Node first;             // First node in the list
    int total;              // Total number of nodes: A trick way to determine whether the list is empty or not.
} *List;

typedef struct QueueRepr{
    List list;
} *queue;

/*
 * Create a new list
*/
List createListInQ() {
    List newList = malloc(sizeof(struct list));
    newList->first = NULL;
    newList->total = 0;

    return newList;
}

/*
 * Create a new node with given string data
*/
Node makeNodeInQ(string data) {
    Node newNode = malloc(sizeof (struct node));
    newNode->data = malloc(sizeof(char) * (strlen(data) + 1));
    strcpy(newNode->data, data);

    newNode->next = NULL;
    return newNode;

}

/*
 * Create a new queue
*/
queue queue_create() {
    queue newQueue = malloc(sizeof(struct QueueRepr));
    newQueue->list = createListInQ();
    return newQueue;
}

/*
 * Free the memory allocated to a queue and its related list
*/
void queue_destroy(queue q) {
    if (q!= NULL) {
        if (q->list != NULL) {
            Node cur = q->list -> first;    // Free each node in the list
            Node next;
            while (cur!=NULL) {
                next = cur -> next;
                free(cur->data);
                free(cur);
                cur = next;
            }
            free(q->list);                  // Free the list itself
        }
        free(q);                            // Free the queue
    }

}


/*
 * 1. Create a new node to store the new data and allocate the memory for them
 * 2. Insert the new node into the queue
 */
void queue_enqueue(queue q, string dat) {
    Node newNode = makeNodeInQ(dat);           // Create a new node with the given data
    if (newNode == NULL) {
        return;
    }
    if (q->list->first == NULL) {                // If the list is empty, set the first node to be the new node
        q->list->first = newNode;
    } else {                                     // Otherwise, add the new node to the end of the list
        Node cur = q->list->first;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = newNode;
    }
    q->list->total++;                           // Update the total count

}


/*
 * Return the front string in the queue and delete it from the queue
 */
string queue_dequeue(queue q) {
    if (q == NULL || queue_empty(q)) {
        return NULL;
    }
    Node cur = q->list->first;
    if (cur == NULL) {
        return NULL;
    }
    string data = cur->data;
    q->list->first = cur->next;                 // Remove the first node and update the total count
    q->list->total--;
    free(cur);
    return data;
}

/*
 * Return the front string in the queue without deleting it from the queue
 */
string queue_peek(queue q) {
    if (queue_empty(q)) {
        return NULL;
    }
    return q->list->first->data;
}

/*
 * Determine whether a given pqueue is empty or not.
 */
bool queue_empty(queue q) {
    return q == NULL || q->list->total == 0;
}
