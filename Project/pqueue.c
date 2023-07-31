#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "pqueue.h"

typedef char *string;      // Define the string type


/*
 * Define the node data structure
 */
typedef struct Node {
    string data;          // Store the string
    priority pri;
    struct Node *next;    // pointer to the next node
} Node;


/*
 * Define the Pqueue structure
 */
struct PriorityQueueRepr {
    Node *head;           // First node in the list
};

/*
 * Create the new queue
 */
pqueue pqueue_create() {
    pqueue pq = malloc(sizeof(struct PriorityQueueRepr));
    if (pq != NULL) {
        pq->head = NULL;
    }
    return pq;
}

/*
 * Destroy a pqueue
 */
void pqueue_destroy(pqueue pq) {
    if (pq != NULL) {
        while (pq->head != NULL) {
            Node *tmp = pq->head;
            pq->head = pq->head->next;
            free(tmp->data);
            free(tmp);
        }
        free(pq);
    }
}

/*
 * Determine the new string's priority is high or not
 * If higher, put into the head of the queue
 * otherwise put into the node after the head.
 */
void insertOrderValueInPq(pqueue pq, priority prio, Node *newNode) {
    if (pq->head == NULL) {
        pq->head = newNode;
    } else if (prio < pq->head->pri) {
        newNode->next = pq->head;
        pq->head = newNode;
    } else {
        Node *cur = pq->head;
        Node *prev = NULL;
        while (cur != NULL && prio >= cur->pri) {
            prev = cur;
            cur = cur->next;
        }
        newNode->next = cur;
        prev->next = newNode;
    }
}

/*
 * 1. Create a new node to store the new data and allocate the memory for them
 * 2. Call the insertOrderValueInPq function to determine which location should be stored.
 */
void pqueue_join(pqueue pq, string data, priority prio) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    if (newNode == NULL) {
        return;
    }
    newNode->data = (string) malloc(strlen(data) + 1);
    if (newNode->data == NULL) {
        free(newNode);
        return;
    }
    strcpy(newNode->data, data);
    newNode->pri = prio;
    newNode->next = NULL;

    insertOrderValueInPq(pq, prio, newNode);
}


/*
 * Return the high priority string and delete it from the pqueue
 */
string pqueue_leave(pqueue pq) {
    if (pq == NULL || pq->head == NULL) {
        return NULL;
    }
    Node *result = pq->head;
    string data = result->data;
    pq->head = pq->head->next;
    free(result);
    return data;
}

/*
 * Return the high priority string without deleting it from the pqueue
 */
string pqueue_peek(pqueue pq) {
    if (pq == NULL || pq->head == NULL) {
        return NULL;
    }
    return pq->head->data;
}

/*
 * Determine whether a given pqueue is empty or not.
 */
bool pqueue_empty(pqueue pq) {
    return pq == NULL || pq->head == 0;
}


