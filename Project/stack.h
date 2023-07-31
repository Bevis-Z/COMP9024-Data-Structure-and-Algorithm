////////////////////////////// DO NOT CHANGE THIS FILE. //////////////////////////////
// THIS FILE IS NOT SUBMITTED AND WILL BE PROVIDED AS IS DURING TESTING AND MARKING //
////////////////////////////// DO NOT CHANGE THIS FILE. //////////////////////////////

#ifndef T_STRING
#define T_STRING

typedef char *string;

#endif // T_STRING

#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stddef.h>

typedef struct StackRepr *stack;

/**
 * stack_create
 * Allocates a new, empty stack.
 * 
 * Returns
 *     On success: Pointer to allocated stack
 *     On error: NULL
 */
stack stack_create();

/**
 * stack_destroy
 * Destroys a given stack, freeing all associated memory.
 * 
 * Parameters
 *     Pointer to the stack to destroy
 */
void stack_destroy(stack);

/**
 * stack_push
 * Pushes a new string to the top of the stack.
 *
 * Parameters
 *     Pointer to stack to push to,
 *     The string to push onto the stack
 */
void stack_push(stack, string);

/**
 * stack_pop
 * Pops the first element off the given stack.
 *
 * It is up to the caller to free the memory associated with the returned string.
 *
 * Parameters
 *     Pointer to the stack to pop from
 *
 * Returns
 *    On success: The element at the top of the stack
 *    On error: NULL
 */
string stack_pop(stack);

/**
 * stack_peek
 * Peeks at and returns the top element in the stack, without removing it.
 * 
 * Note: If `stack_peek` is called then `stack_destroy` is called on the same
 * stack, the memory associated with the string returned in `stack_peek` will
 * have been freed.
 *
 * Parameters
 *     Pointer to the stack to peek from
 *
 * Returns
 *    On success: The element at the top of the stack
 *    On error: NULL
 */
string stack_peek(stack);

/**
 * stack_empty
 * Determines whether a given stack is empty or not.
 * 
 * Parameters
 *     Pointer to the stack to check
 *
 * Returns
 *     true - If stack is empty or is NULL
 *     false - If stack is not empty
 */
bool stack_empty(stack);

#endif // STACK_H
