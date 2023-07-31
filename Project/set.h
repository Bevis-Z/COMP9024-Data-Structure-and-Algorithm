////////////////////////////// DO NOT CHANGE THIS FILE. //////////////////////////////
// THIS FILE IS NOT SUBMITTED AND WILL BE PROVIDED AS IS DURING TESTING AND MARKING //
////////////////////////////// DO NOT CHANGE THIS FILE. //////////////////////////////

#ifndef T_STRING
#define T_STRING

typedef char *string;

#endif // T_STRING

#ifndef SET_H
#define SET_H

#include <stdbool.h>
#include <stddef.h>

typedef struct SetRepr *set;

/**
 * set_create
 * Allocates a new, empty set.
 * 
 * Returns
 *     On success: Pointer to allocated set
 *     On error: NULL
 */
set set_create();

/**
 * set_destroy
 * Destroys a given set, freeing all associated memory.
 * 
 * Parameters
 *     Pointer to the set to destroy
 */
void set_destroy(set);

/**
 * set_insert
 * Inserts a new element into the set if it does not exist already.
 *
 * Parameters
 *     Pointer to set to insert into,
 *     The string to add to the set
 */
void set_insert(set, string);

/**
 * set_remove
 * Removes an element from the set if it exists.
 *
 * Parameters
 *     Pointer to the set to remove from,
 *     The string to remove from the set
 */
void set_remove(set, string);

/**
 * set_contains
 * Determines whether an element exists in the given set.
 * 
 * Parameters
 *     Pointer to the set to search through,
 *     String to search for
 *
 * Returns
 *    true - If string exists in the given set
 *    false - If string does not exist in given set, or there was some error
 */
bool set_contains(set, string);

#endif // SET_H
