//
// Created by Bevis on 4/4/2023.
//
#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

int main() {
    stack s = stack_create();

    stack_push(s, "Hello");
    stack_push(s, "World");

    printf("Peek: %s\n", stack_peek(s));

    while (!stack_empty(s)) {
        string top = stack_pop(s);
        printf("Popped: %s\n", top);
        free(top);
    }

    stack_destroy(s);
    return 0;
}