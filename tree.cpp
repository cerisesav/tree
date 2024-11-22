#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "tree.h"
#include "dump.h"
#include "stack.h"
#include "akinator.h"

static Node* NodeCtor (data_t value, Node *parent);
static Node* ReadNode(FILE* tree_file, Node* parent);
static void GetNodeFromFile(Node* node, FILE* file);
static void TrailingSpaces(char *buffer, size_t i);
static void SkipToBrace(FILE* file, int c);
static void SkipSpaces(FILE* file, int c);
static void ProcessNodeChildren(Node* node, FILE* file, int c);


// tree (ptr to root) TreeCtor (runs NodeCtor) NodeCtor NodeDtor
static void TrailingSpaces(char *buffer, size_t i) {

    while (i > 0 && buffer[i-1] == ' ') {
        buffer[--i] = '\0';
    }

    buffer[i] = '\0';
}

static void ProcessNodeChildren(Node* node, FILE* file, int c) {

    if (c == RIGHT_SEPARATOR) {
        node->left = nullptr;
        node->right = nullptr;

    } else {

        ungetc(c, file);

        node->right = (Node*)calloc(1, sizeof(Node));
        node->left = (Node*)calloc(1, sizeof(Node));

        if (node->right && node->left) {
            node->right->parent = node;
            node->left->parent = node;

            GetNodeFromFile(node->right, file);
            GetNodeFromFile(node->left, file);
        }
    }

}

static void SkipToBrace(FILE* file, int c) {

    while(c != LEFT_SEPARATOR && c != EOF)
        c = getc(file);

    if (c == EOF)
        return;
}

static void SkipSpaces(FILE* file, int c) {

    while((c = getc(file)) == ' ') {
        if (c == EOF) return;
    }

    ungetc(c, file);
}

void GetNodeFromFile(Node* node, FILE* file) {

    int c = getc(file);

    char buffer[MAX_LINE] = {0};
    SkipToBrace(file,c);


    SkipSpaces(file, c);

    size_t i = 0;

    while ((c = getc(file)) != LEFT_SEPARATOR && c != EOF && c != RIGHT_SEPARATOR && i < MAX_LINE - 1) {  // { } as a consts, function, checking signature
        buffer[i++] = (char) c;
    }

    TrailingSpaces(buffer, i);


    node->data = strdup(buffer);

    if (c == EOF) return;

    ProcessNodeChildren(node, file, c);
}


static Node* NodeCtor (data_t value, Node *parent) {

	Node* temp = (Node*) calloc(1, sizeof(Node));

	assert(temp); // code errors)

	temp->left = nullptr;
    temp->right = nullptr;

	temp->data = strdup(value);

	temp->parent = parent;

	return temp;
}

void TreeDtor(Node *root) {

    if (root) {
        TreeDtor(root->left);
        TreeDtor(root->right);
        free(root->data);
        free(root);
    }
}

static Node* ReadNode(FILE* tree_file, Node* parent) {

    char* empty_string = (char*)"";

    Node* node = NodeCtor(empty_string, parent);
    GetNodeFromFile(node, tree_file);
    return node;
}

Node* TreeFromFile(FILE* tree_file) {
    assert(tree_file);
    Node* root = ReadNode(tree_file, nullptr);

    if (root) {
        puts("tree is okay)");
    } else {
        puts("something went wrong..");
    }

    return root;
}

Node* Insert (Node* node) {

    puts("Enter the word you have guessed:");
    char word[MAX_LINE] = "";

    scanf(" %[^\n]", word);

    puts("Enter the option of difference:");

    char new_option[MAX_LINE] = "";

    scanf(" %[^\n]", new_option);

    Node* NewNode = NodeCtor(new_option, node->parent);

    NewNode->right = node;
    node->parent = NewNode;

    Node* NewWord= NodeCtor(word, NewNode);
    NewNode->left = NewWord;

    if (NewNode->parent) {
        if (NewNode->parent->left == node) {
            NewNode->parent->left = NewNode;
        } else {
            NewNode->parent->right = NewNode;
        }
    }

    TreeDump(NewNode);
    return NewNode;
}
