#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"

static void Realloc(Stack* stack);

Stack* StackCtor(size_t capacity) {
    Stack* stack = (Stack*)calloc(1, sizeof(Stack));
    assert(stack);

    stack->data = (void**)calloc(capacity, sizeof(void*));
    assert(stack->data);

    stack->size = 0;
    stack->capacity = capacity;

    return stack;
}

void Push(Stack* stack, void* element) {

    if (stack->size == stack->capacity)
		Realloc(stack);

    stack->data[stack->size++] = element;
}


void* Pop(Stack* stack) {

    if (stack->size == 0) {
        return nullptr;
    }

    return stack->data[--stack->size];
}

static void Realloc(Stack* stack) {

	stack->capacity *= 2;

	stack->data = (void**)realloc(stack->data, stack->capacity * sizeof(void*));
	assert(stack->data);
}

void StackDtor(Stack* stack) {
    free(stack->data);
    free(stack);
}
