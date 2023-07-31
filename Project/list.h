//
// Created by Bevis on 4/4/2023.
//

//
// Created by Bevis on 4/4/2023.
//
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

typedef char * string;

typedef struct node {
    string data;
    struct node *next;
} *Node;


typedef struct list {
    Node first;
    int total;
} *List;

/*
 * Create a new list
 * @return a new list
 */
List createList ();


/*
 * free list
 *
 */
List freeList (List list);


Node existsList (List, string);

Node makeNodeInGraph(string data, double weight);

/*
 * insert data to the list
 */
void insertListFirst(List, string);

Node existsList (List list, string data);


string deleteListFirst(List, string);

void insertListLast(List, string);

string deleteListLast(List, string);

bool isEmptyList(List);

int lengthOfList (List);

string getListFromLast(List);

string getListFromHead(List);



