#ifndef STACK_H
#define STACK_H

struct Stack {
    void** data;
    size_t size;
    size_t capacity;
};

Stack* StackCtor(size_t capacity);
void Push(Stack* stack, void* element);

void* Pop(Stack* stack);
void StackDtor(Stack* stack);

#endif
