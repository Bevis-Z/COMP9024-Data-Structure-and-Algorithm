////////////////////////////// DO NOT CHANGE THIS FILE. //////////////////////////////
// THIS FILE IS NOT SUBMITTED AND WILL BE PROVIDED AS IS DURING TESTING AND MARKING //
////////////////////////////// DO NOT CHANGE THIS FILE. //////////////////////////////

#ifndef T_STRING
#define T_STRING

typedef char *string;

#endif // T_STRING

#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct QueueRepr *queue;

/**
 * queue_create
 * Allocates a new, empty queue.
 * 
 * Returns
 *     On success: Pointer to allocated queue
 *     On error: NULL
 */
queue queue_create();

/**
 * queue_destroy
 * Destroys a given queue, freeing all associated memory.
 * 
 * Parameters
 *     Pointer to the queue to destroy
 */
void queue_destroy(queue);

/**
 * queue_enqueue
 * Enqueues a new string to the end of the given queue.
 *
 * Parameters
 *     Pointer to queue to enqueue to,
 *     The string to enqueue into the queue
 */
void queue_enqueue(queue, string);

/**
 * queue_dequeue
 * Dequeues the first element in the given queue.
 *
 * It is up to the caller to free the memory associated with the returned string.
 *
 * Parameters
 *     Pointer to the queue to dequeue from
 *
 * Returns
 *    On success: The element at the front of the queue
 *    On error: NULL
 */
string queue_dequeue(queue);

/**
 * queue_peek
 * Peeks at and returns the front element in the queue, without removing it.
 *
 * Note: If `queue_peek` is called then `queue_destroy` is called on the same
 * queue, the memory associated with the string returned in `queue_peek` will
 * have been freed.
 * 
 * Parameters
 *     Pointer to the queue to peek from
 *
 * Returns
 *    On success: The element at the front of the queue
 *    On error: NULL
 */
string queue_peek(queue);

/**
 * queue_empty
 * Determines whether a given queue is empty e not.
 * 
 * Parameters
 *     Pointer to the queue to check
 *
 * Returns
 *     true - If queue is empty or is NULL
 *     false - If queue is not empty
 */
bool queue_empty(queue);

#endif // QUEUE_H
