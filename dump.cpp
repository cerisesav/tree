#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "dump.h"
#include "tree.h"
#include "stack.h"

void StackDump(struct Stack* stk, const char *file, int line, const char *function)
{
    if (stk == NULL) {
        printf("Error: Stack pointer is NULL\n");
        return;
    }

    printf("\nStack Dump Info:\n");
    printf("Called from %s (%d) in function %s\n", file, line, function);
    printf("Stack[%p]\n", (void*)stk);

    printf("Stack Details:\n");
    printf("\tsize = %zu\n", stk->size);
    printf("\tcapacity = %lu\n", stk->capacity);
    printf("\tdata address = %p\n", (void*)stk->data);


    if (stk->data != NULL) {
        printf("Stack Contents:\n");
        for (size_t i = 0; i < stk->size && i < stk->capacity; i++) {
            printf("\tdata[%zu] = %p\n", i, stk->data[i]);
        }
    } else {
        printf("\tError: Stack data is NULL\n");
    }

    puts("-------------------------------------------------------------------");
}

void StackAssert(Stack* stk)
{
    if (stk == NULL) {
        printf("Error: Stack pointer is NULL\n");
        abort();
    }

    if (stk->size < 0 || stk->size > stk->capacity)
    {
        stk->err = Size;
        printf("Error: Invalid stack size\n");
        StackDumpMacro(stk);
        abort();
    }

    if (stk->capacity == 0 || stk->data == NULL)
    {
        stk->err = NullPointer;
        printf("Error: Invalid stack data\n");
        StackDumpMacro(stk);
        abort();
    }

    if (stk->err != NoError)
    {
        StackDumpMacro(stk);
        abort();
    }
}

void TreeDot(FILE *tree, Node *root) {

    if (root) {

        fprintf(tree, "    \"%s\" [label = \"{<root> %s? | {<left> left: %s | <right> right: %s}}\", "
               "shape=Mrecord, style=rounded, color=violet, fillcolor=pink, style=filled];\n",
                root->data,
                root->data,
                root->left ? root->left->data : "NULL",
                root->right ? root->right->data : "NULL");


        if (root->left) {
            fprintf(tree, "    \"%s\":left:c -> \"%s\":root [label=\"NO\", color=\"#ff0000\", fontcolor=\"#000000\"];\n",
                    root->data, root->left->data);
            TreeDot(tree, root->left);
        }

        if (root->right) {
            fprintf(tree, "    \"%s\":right:c -> \"%s\":root [label=\"YES\", color=\"#228b22\", fontcolor=\"#000000\"];\n",
                    root->data, root->right->data);
            TreeDot(tree, root->right);
        }
    }
}


void TreeDump(Node *root) {
    FILE *tree = fopen("tree.dot", "w");
    assert(tree);
    fprintf(tree, "digraph BinaryTree {\n");
    // fprintf(tree, "    splines = ortho\n");
    fprintf(tree, "    node [fontname=\"Arial\", color = \"violet\"];\n");
    TreeDot(tree, root);
    fprintf(tree, "}\n");
    fclose(tree);
    system("dot -Tpng tree.dot -o tree.png");
}

const char* StackError(Stack* stk)
{
    switch (stk->err)
    {
        case Overflow: return "Stack Overflow";
        case Size: return "Size/Capacity is not correct";
        case Underflow: return "Stack Underflow";
        case NoError: return "Stack is working fine";
        case NullPointer: return "Null Pointer Error";
        case CanaryError: return "Canary was poisoned";
        case HashError: return "Hash is not equal";
        default: return "Unknown Error";
    }
}
