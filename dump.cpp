#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "dump.h"
#include "functions.h"

void TreeDot(FILE *tree, Node *root) {

    if (root) {

        fprintf(tree, "    \"%s\" [label = \"{<root> %s | {<left> left: %s | <right> right: %s}}\", "
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
    fprintf(tree, "    splines = ortho;\n");
    fprintf(tree, "    node [fontname=\"Arial\", color = \"violet\"];\n");
    TreeDot(tree, root);
    fprintf(tree, "}\n");
    fclose(tree);
    system("dot -Tpng tree.dot -o tree.png");
}
