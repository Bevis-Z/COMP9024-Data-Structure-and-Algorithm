////////////////////////////// DO NOT CHANGE THIS FILE. //////////////////////////////
// THIS FILE IS NOT SUBMITTED AND WILL BE PROVIDED AS IS DURING TESTING AND MARKING //
////////////////////////////// DO NOT CHANGE THIS FILE. //////////////////////////////

#ifndef T_STRING
#define T_STRING

typedef char *string;

#endif // T_STRING

#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

#include <stdbool.h>
#include <stddef.h>

typedef struct PriorityQueueRepr *pqueue;

/**
 * In this priority queue, lower `priority` values have higher queue priority.
 * E.g. if priorities are (1.5, 0.2, 7.8, 8.3), then elements will be dequeued
 * in the following order:
 *
 * 0.2 then 1.5 then 7.8 then 8.3
 */
typedef double priority;

/**
 * pqueue_create
 * Allocates a new, empty pqueue.
 * 
 * Returns
 *     On success: Pointer to allocated pqueue
 *     On error: NULL
 */
pqueue pqueue_create();

/**
 * pqueue_destroy
 * Destroys a given pqueue, freeing all associated memory.
 * 
 * Parameters
 *     Pointer to the pqueue to destroy
 */
void pqueue_destroy(pqueue);

/**
 * pqueue_join
 * Adds a new string into the given pqueue.
 *
 * Parameters
 *     Pointer to pqueue to enqueue to,
 *     The string to enqueue into the pqueue,
 *     The priority of this string
 */
void pqueue_join(pqueue, string, priority);

/**
 * pqueue_leave
 * Removes the highest priority string in the given pqueue.
 *
 * It is up to the caller to free the memory associated with the returned string.
 *
 * Parameters
 *     Pointer to the pqueue to dequeue from
 *
 * Returns
 *    On success: The string with the highest priority in the pqueue
 *    On error: NULL
 */
string pqueue_leave(pqueue);

/**
 * pqueue_peek
 * Peeks at and returns the highest priority string in the pqueue,
 * without removing it.
 * 
 * Note: If `pqueue_peek` is called then `pqueue_destroy` is called on the same
 * pqueue, the memory associated with the string returned in `pqueue_peek` will
 * have been freed.
 *
 * Parameters
 *     Pointer to the pqueue to peek from
 *
 * Returns
 *     On success: The element at the front of the pqueue
 *     On error: NULL
 */
string pqueue_peek(pqueue);

/**
 * pqueue_empty
 * Determines whether a given pqueue is empty or not.
 * 
 * Parameters
 *     Pointer to the pqueue to check
 *
 * Returns
 *     true - If pqueue is empty or is NULL
 *     false - If pqueue is not empty
 */
bool pqueue_empty(pqueue);

#endif // PRIORITY_QUEUE
