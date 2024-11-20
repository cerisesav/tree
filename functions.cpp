#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "functions.h"
#include "stack.h"
#include "akinator.h"

static Node* NodeCtor (data_t value, Node *parent);
static Node* ReadNode(FILE* tree_file, Node* parent);
static void GetNodeFromFile(Node* node, FILE* file);
static void TrailingSpaces(char *buffer, size_t i);

// tree (ptr to root) TreeCtor (runs NodeCtor) NodeCtor NodeDtor
static void TrailingSpaces(char *buffer, size_t i) {

    while (i > 0 && buffer[i-1] == ' ') {
        buffer[--i] = '\0';
    }

    buffer[i] = '\0';
}

void GetNodeFromFile(Node* node, FILE* file) {

    int c = getc(file);

    char buffer[MAX_LINE] = {0};

    while(c != '{' && c != EOF)
        c = getc(file);

    if (c == EOF)
        return;

    // space after brace
    while((c = getc(file)) == ' ') {
        if (c == EOF) return;
    }

    ungetc(c, file);

    size_t i = 0;

    while ((c = getc(file)) != '{' && c != EOF && c != '}' && i < MAX_LINE - 1) {  // { } as a consts, function, checking signature
        buffer[i++] = (char) c;
    }

    TrailingSpaces(buffer, i);


    node->data = strdup(buffer);

    if (c == EOF) return;

    if (c == '}') {
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

bool SearchAndTrackWithDefinition(const Node* root, const char* word, Stack* pathStack, Stack* definitionStack) {
    if (!root) return false;

    Push(definitionStack, strdup(root->data));

    if (!strcmp(root->data, word)) {
        return true;
    }

    if (root->left) {
        Push(pathStack, strdup("NO"));

        if (SearchAndTrackWithDefinition(root->left, word, pathStack, definitionStack)) {
            return true;
        }

        Pop(pathStack);

    }

    if (root->right) {

        Push(pathStack, strdup("YES"));
        if (SearchAndTrackWithDefinition(root->right, word, pathStack, definitionStack)) {
            return true;
        }

        Pop(pathStack);

    }

    free(Pop(definitionStack));
    return false;
}

void FindDefinition(Node* node, Stack* pathStack) {

    char word[MAX_LINE];
    printf("Enter the word you want to find the definition for: ");
    scanf("%s", word);

    Stack* definitionStack = StackCtor(10);

    if (SearchAndTrackWithDefinition(node, word, pathStack, definitionStack)) {

        printf("%s = is ",  (char*)definitionStack->data[definitionStack->size-1]);

        for (size_t i = 0; i < pathStack->size; i++) {

            if (!strcmp((char*)pathStack->data[i], "NO")) {
                printf("%s %s, ", "not", (char*)definitionStack->data[i]);
            }
            else
                printf("%s, ", (char*)definitionStack->data[i]);
        }

        while (definitionStack->size > 0) {
            free(Pop(definitionStack));
        }

        StackDtor(definitionStack);

    } else {
            printf("Word not found in the tree.\n");
        }
}

Node* FindNodeByWord(Node* root, const char* word, Stack* pathStack) {

    if (!root || pathStack->size >= pathStack->capacity - 1) {
        return NULL;
    }

    if (!strcmp(root->data, word)) {
        return root;
    }

    if (root->left) {

        char* no_str = strdup("NO");
        Push(pathStack, no_str);

        Node* leftResult = FindNodeByWord(root->left, word, pathStack);
        if (leftResult) return leftResult;

        free(Pop(pathStack));
    }

    if (root->right) {

        char* yes_str = strdup("YES");
        Push(pathStack, yes_str);

        Node* rightResult = FindNodeByWord(root->right, word, pathStack);

        if (rightResult) return rightResult;

        free(Pop(pathStack));
    }

    return NULL;
}

void SelectMode(Node* root, Stack* pathStack) {

    printf("Choose an option:\n");
    printf("1. Run Akinator\n");
    printf("2. Find definition of a word\n");

    int choice = 0;
    scanf("%d", &choice);

    if (choice == 1) {
        RunAkinator(root);
    }

    else if (choice == 2) {
        FindDefinition(root, pathStack);
    }

    else {
        printf("Invalid choice.\n");
    }
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
