#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include "stretchy_buffer.h"

/* What data types to store? */
typedef unsigned short stack_type;

typedef struct {
	stack_type *elems;
	size_t top;
} stack_t;

/* returns a new stack */
stack_t stack_new(size_t default_memory);

/* deletes resources */
void stack_delete(stack_t *stack);

/* pushes a new value on the stack */
void stack_push(stack_t *stack, stack_type val);

/* pops a value from the stack, returns it */
int stack_pop(stack_t *stack);

/* returns the value on the stack, does not pop it */
int stack_top(stack_t *stack);

/* does the stack contain at least one element? */
int stack_empty(stack_t *stack);

#endif
