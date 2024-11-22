#ifndef TREE_H
#define TREE_H

#include "stack.h"

#define MAX_LINE 256

#define LEFT_SEPARATOR '{'
#define RIGHT_SEPARATOR '}'

typedef char* data_t;

struct Node {
    data_t data;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
};

struct Tree {
    struct Node* root;
};

Node* Insert (Node* node);
void TreeDtor(Node *root);
Node* TreeFromFile(FILE* tree_file);

Node* FindNodeByWord(Node* root, const char* word, Stack* pathStack);

#endif
