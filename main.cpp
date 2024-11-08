#include <stdio.h>

#include "dump.h"
#include "tree.h"
#include "functions.h"

int main() {

    Node *root = nullptr;

    Insert(&root, 10);
    Insert(&root, 12);
    Insert(&root, 45);
	Insert(&root, 8);

    TreeDump(root);

    return 0;
}
