//
// Created by Bevis on 4/4/2023.
//
#include <stdio.h>
#include "pqueue.h"

int main() {
    pqueue pq = pqueue_create();

    pqueue_join(pq, "banana", 3);
    pqueue_join(pq, "apple", 4);
    pqueue_join(pq, "pear", 2);

//    printf("%s\n", pqueue_leave(pq)); // 输出 "apple"

    pqueue_destroy(pq);

    return 0;
}
