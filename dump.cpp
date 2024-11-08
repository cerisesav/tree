#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "dump.h"

void TreeDot(FILE *tree, Node *root) {

    if (root) {
        if (root->parent) {
            fprintf(tree, "    \"%d\" -> \"%d\" [color = \"blue\"];\n", root->parent->data, root->data);
        }
        TreeDot(tree, root->left);
        TreeDot(tree, root->right);
    }
}

void TreeDump(Node *root) {

    FILE *tree = fopen("tree.dot", "w");
    assert(tree);

    fprintf(tree, "digraph BinaryTree {\n");
	fprintf(tree, "splines = ortho\n");
    fprintf(tree, "    node [fontname=\"Arial\", color = \"violet\"];\n");
    TreeDot(tree, root);
    fprintf(tree, "}\n");
    fclose(tree);

    system("dot -Tpng tree.dot -o tree.png");
}
