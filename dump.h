#ifndef DUMP_H
#define DUMP_H

#include "tree.h"
#include "stack.h"

#define StackDumpMacro(stk) (StackDump(stk, __FILE__, __LINE__, __FUNCTION__))

void TreeDot(FILE *tree, Node *root);

void TreeDump(Node *root);

const char* StackError(Stack* stk);

void StackAssert(Stack* stk);

void StackDump(struct Stack* stk, const char *file, int line, const char *function);

#endif
