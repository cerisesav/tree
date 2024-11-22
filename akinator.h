#ifndef AKINATOR_H
#define AKINATOR_H

//colorful text with macros
#include "tree.h"
#include "stack.h"

static const char* YES = "yes";
static const char* NO = "no";

bool RunAkinator(Node* node);
bool SearchAndTrackWithDefinition(const Node* root, const char* word, Stack* pathStack, Stack* definitionStack);
void FindDefinition(Node* node, Stack* pathStack);
void SelectMode(Node* root, Stack* pathStack);

#endif
