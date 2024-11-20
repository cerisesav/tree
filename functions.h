#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "dump.h"
#include "tree.h"

#define MAX_LINE 256

Node* Insert (Node* node);
void TreeDtor(Node *root);
Node* TreeFromFile(FILE* tree_file);
bool SearchAndTrackWithDefinition(const Node* root, const char* word, Stack* pathStack, Stack* definitionStack);
void FindDefinition(Node* node, Stack* pathStack);
void SelectMode(Node* root, Stack* pathStack);
Node* FindNodeByWord(Node* root, const char* word, Stack* pathStack);

#endif
