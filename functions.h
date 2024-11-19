#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "dump.h"
#include "tree.h"

#define MAX_LINE 256

Node* Insert (Node* node);
void TreeDtor(Node *root);
Node* TreeFromFile(FILE* tree_file);
char* Search(const Node* root, const char* word);
void Definition(Node* node);

#endif
