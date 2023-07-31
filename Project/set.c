#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* string;

/*
 * Define the node data structure
 */
typedef struct node {
    string data;
    struct node *next;
} *Node;

/*
 * Define the set structure
 */
typedef struct SetRepr{
    Node head;
} *set;


/*
 * Create the new set by allocating memory for the sets
 * Set head to NULL
 */
set set_create() {
    set newSet = malloc(sizeof(struct SetRepr));
    newSet->head = NULL;
    return newSet;
}

/*
 * Destroy the set and free memory for all the nodes & data
 */
void set_destroy(set s) {
    if (s == NULL) {
        return;
    }

    Node curNode = s->head;
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
 * Insert a new string data into the set if it does not already exist
 * Exists Data will not be inserted
 */
void set_insert(set s, string dat) {
    if (set_contains(s, dat)) {
        return;
    }
    Node newNode = malloc(sizeof(struct node));
    newNode->data = malloc(sizeof(char) * (strlen(dat) + 1));
    strcpy(newNode->data, dat);
    newNode->next = NULL;
    if (s->head == NULL) {
        s->head = newNode;
    } else {
        Node cur = s->head;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = newNode;
    }

}

/*
 * Remove a string data from the set if it exists
 */
void set_remove(set s, string dat) {
    if (s->head == NULL) {
        return;
    }
    Node cur = s->head;
    Node dummy = NULL;
    while (cur != NULL) {
        if (strcmp(cur->data, dat) == 0) {
            if (dummy == NULL) {
                s->head = cur->next;
            } else {
                dummy->next = cur->next;
            }
            free(cur->data);
            free(cur);
            return;
        }
        dummy = cur;
        cur = cur->next;
    }
}

/*
 * Check whether the string exists in the set or not
 */
bool set_contains(set s, string dat) {
    Node cur = s->head;
    while (cur != NULL) {
        if ((strcmp(cur->data, dat) == 0)) {
            return true;
        }
        cur = cur->next;
    }
    return false;

}
