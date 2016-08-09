#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define EMPTY -1

Stack
*stack_new() {
	Stack *s;
	void **newA = NULL;
	s = (Stack*)malloc(sizeof(*s));
	newA = (void**)malloc(sizeof(*newA));
	assert(s!=NULL);
	assert(newA!=NULL);
	s->A = newA;
	s->size = 1;
	s->top = EMPTY;
	return s;
}

void
stack_push(Stack *s, void *item) {
	void **newitem;
	newitem = (void**)malloc(sizeof(void*));
	assert(newitem!=NULL);
	if (s->top==s->size-1) {
		s->size *= 2;
		s->A = (void**)realloc(s->A, s->size * sizeof(*(s->A)));
	}
	memcpy(newitem, &item, sizeof(void*));
	(s->top)++;
	(s->A)[s->top] = *newitem;
}

void
*stack_pop(Stack *s) {
	if (stack_isEmpty(s)) {
		fprintf(stderr, "Stack is empty\n");
		return NULL;
	}
	return s->A[s->top--];
}

int
stack_isEmpty(Stack *s) {
	return s->top<0;
}

void
stack_print(Stack *s, void(printFn)(void *)) {
	int i;
	if (stack_isEmpty(s)) {
		fprintf(stderr, "Empty Stack\n");
		return;
	}
	for (i=0;i<s->top;i++) {
		printFn(s->A[i]);
	}
	printf("\n");
}