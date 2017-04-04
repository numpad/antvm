#ifndef STACK_C
#define STACK_C

#include "stack.h"

/* returns a new stack */
stack_t stack_new(size_t default_memory) {
	stack_t stack;
	
	/* initialize memory */
	stack.elems = NULL;
	//stack.elems = sb_add(stack.elems, default_memory);
	stack.top = 0;

	return stack;
}

/* deletes resources */
void stack_delete(stack_t *stack) {
	sb_free(stack->elems);
}

/* pushes a new value on the stack */
void stack_push(stack_t *stack, stack_type val) {
	/* sets current top to _val_, then increases stack_top */
	sb_push(stack->elems, val);
	stack->top++;
}

/* pops a value from the stack, returns it */
int stack_pop(stack_t *stack) {
	/* decreases stack_top, then returns top value */
	return stack->elems[--stack->top];
}

/* returns the value on the stack, does not pop it */
int stack_top(stack_t *stack) {
	return stack->elems[stack->top - 1];
}

/* does the stack contain at least one element? */
int stack_empty(stack_t *stack) {
	return (stack->top > 0) ? 0 : 1;
}

#endif
