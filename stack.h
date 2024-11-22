#ifndef STACK_H
#define STACK_H

enum CodeError {
    Overflow,
    Size,
    Underflow,
    NullPointer,
    CanaryError,
    HashError,
    NoError
};

struct Stack {
    void** data;
    size_t size;
    size_t capacity;
	CodeError err;
};

Stack* StackCtor(size_t capacity);
void Push(Stack* stack, void* element);

void* Pop(Stack* stack);
void StackDtor(Stack* stack);

#endif
