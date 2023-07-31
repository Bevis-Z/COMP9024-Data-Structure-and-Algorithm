//
//Created by Bevis on 4/4/2023.
//
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef char * string;

typedef struct node {
    string data;
    double weight;
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
List createList() {
    List newList = malloc(sizeof(struct list));
    newList->first = NULL;
    newList->total = 0;

    return newList;
};

Node makeNode(string data, double weight) {
    Node newNode = malloc(sizeof (struct node));
    assert(newNode!=NULL);
    newNode->data = malloc(sizeof(char) * (strlen(data) + 1));
    strcpy(newNode->data, data);

    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;

}

/*
 * insert data to the list
 */
void insertList(List, string) {

};


List freeList (List list) {
    if (list != NULL) {
        Node cur = list -> first;
        Node next;
        while (cur!=NULL) {
            next = cur -> next;
            free(cur->data);
            free(cur);

            cur = next;
        }
        free(list);
    }

}

//void insertListToNeighbours(graph g, string v1, string v2, weight w) {
//    Node node1 = existsList(g, v1);  // 查找节点1是否存在
//    Node node2 = existsList(g, v2);  // 查找节点2是否存在
//    if (node1 == NULL) {             // 如果节点1不存在，创建节点1并添加到图中
//        node1 = makeNodeInGraph(v1, 0);
//        insertOrderValueInGraph(g, 0, node1);
//    }
//    if (node2 == NULL) {             // 如果节点2不存在，创建节点2并添加到图中
//        node2 = makeNodeInGraph(v2, 0);
//        insertOrderValueInGraph(g, 0, node2);
//    }
//    // 将节点2添加到节点1的邻居链表中
//    graph tmp = node1->neigh;
//    Node new_node = makeNodeInGraph(node2->data, w);
//    insertOrderValueInGraph(tmp, w, new_node);
//};


Node existsList (List list, string data) {
    Node result = NULL;
    Node cur = list->first;
    while(cur != NULL) {
        if ( strcmp(cur->data, data) == 0) {
            result = cur;
            break;
        }
        cur = cur -> next;
    }
    return result;
}

/*
 * insert data to the list
 */
void insertListFirst(List list, string data) {
    Node newNode = makeNode(data, 0.0);
    newNode -> next = list->first;
    list->first = newNode;
    list->total++;
}

string deleteListFirst(List list) {
    string result = NULL;
    if (list!= NULL && list->first!= NULL) {
        Node head = list->first;
        list->first = head->next;
        result = head->data;

        free(head);
    }
    return result;
}

void insertListLast(List list, string data) {
    if (list->first == NULL) {
        insertListFirst(list,data);
    } else {
        Node cur = list->first;
        while (cur->next == NULL) {
            cur = cur -> next;
        }

        cur->next = makeNode(data, 0.0);
        list->total ++;
    }
}

string deleteListLast(List list){

    string result = NULL;
    if (list!= NULL && list->first!= NULL) {
        if (list->total == 1) {
            result = deleteListFirst(list);
        } else {
            Node prev = list->first;
            Node cur = prev->next;
            while(cur->next!=NULL) {
                cur = cur->next;
                prev = prev->next;
            }

            prev->next = NULL;
            result = cur->data;
            free(cur);
        }
    }
    return result;
}

bool isEmptyList(List list) {
    if (list!=NULL && list->total != 0) {
        return true;
    } else {
        return false;
    }
}

int lengthOfList (List list) {
    return list->total;
}


string getListFromLast (List list) {
}

string getListFromHead(List list) {

}

int compareTwo(double w1, string d1, double w2, string d2) {
    if (w1 > w2) {
        return 1;
    } else if (w1 < w2) {
        return -1;
    } else {
        return strcmp(d1, d2);
    }
}
void insertListWithOrder(List list, string data, double weight) {
    if (list->first == NULL) {
        list->first = makeNode(data, weight);
        list->total++;
    } else {
        Node cur = list->first;
        if (compareTwo(weight, data, cur->weight, cur->data) > 0) {
            Node newNode = makeNode(data, weight);
            newNode->next = list->first;
            list->first = newNode;
            list->total++;
        } else {
            Node next = cur->next;
            while (next!=NULL) {
                if (compareTwo(cur->weight, cur->data, weight, data) > 0 && compareTwo(weight, data, next->weight, next->data)>0) {
                    break;
                }
                next = next->next;
            }
            Node newNode = makeNode(data, weight);
            newNode -> next = next;
            cur -> next = newNode;
            list->total++;
        }

    }
}

void insertListWithOrder(List list, string data, double weight) {
    if (list->first == NULL) {
        list->first = makeNode(data, weight);
        list->total++;
    } else {
        Node cur = list->first;
        if (compareTwo(weight, data, cur->priority, cur->data) > 0) {
            Node newNode = makeNode(data, weight);
            newNode->next = list->first;
            list->first = newNode;
            list->total++;
        } else {
            Node next = cur->next;
            while (next!=NULL) {
                if (compareTwo(cur->priority, cur->data, weight, data) > 0 && compareTwo(weight, data, next->priority, next->data)>0) {
                    break;
                }
                next = next->next;
            }
            Node newNode = makeNode(data, weight);
            newNode -> next = next;
            cur -> next = newNode;
            list->total++;
        }

    }
}

void showList(List list) {
    printf("List:\n");
    if (list != NULL) {
        Node cur = list -> first;
        Node next;
        while (cur!=NULL) {
            next = cur -> next;
            printf("data:%s, weight %.4f", cur->data, cur->weight);
            cur = next;
        }

    }

}


