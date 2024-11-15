#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "dump.h"
#include "tree.h"

#define MAX_LINE 256

void Insert (Node **head, data_t value, char* answer);
void TreeDtor(Node *root);
Node* TreeFromFile(FILE* tree_file);

#endif
