#ifndef TREE_H
#define TREE_H

#define CMP_EQ(a, b) ((a) == (b))
#define CMP_LT(a, b) ((a) < (b))
#define CMP_GT(a, b) ((a) > (b))

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
};

#endif