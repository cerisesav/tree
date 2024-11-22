#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "tree.h"
#include "akinator.h"

static void AskQuestion(Node* node, char* answer);
static void ClearBuffer();
static bool HandleYes(Node** node);
static bool HandleNo(Node** node);

bool RunAkinator(Node* node) {
    while (true) {

        char answer[MAX_LINE] = "";

        AskQuestion(node, answer);

        if (!strcmp(answer, YES)) {
            if (!HandleYes(&node)) {
                return false;
            }
        } else if (!strcmp(answer, NO)) {
            if (!HandleNo(&node)) {
                return false;
            }
        }
    }
}

static bool HandleYes(Node** node) {
    if ((*node)->right != nullptr) {
        *node = (*node)->right;
        return true;
    } else {
        puts("i guessed, you are so silly");
        return false;
    }
}

static bool HandleNo(Node** node) {
    if ((*node)->left != nullptr) {
        *node = (*node)->left;
        return true;
    } else {
        puts("i am so sorry(");
        Insert(*node);
        return false;
    }
}

static void AskQuestion(Node* node, char* answer) {

	printf("%s ", node->data);

	scanf("%s", answer);
	ClearBuffer();
}

static void ClearBuffer() {
    int symbol = getchar();

    assert (symbol != EOF);

    while(symbol != '\n') {
        if (symbol == EOF)
            break;
        symbol = getchar();
    }
}

// handle , with the size of stack, bool stack
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
    assert(node);
    assert(pathStack);

    char word[MAX_LINE] = "";

    printf("Enter the word you want to find the definition for: ");
    scanf("%s", word);

    Stack* definitionStack = StackCtor(10);

    if (SearchAndTrackWithDefinition(node, word, pathStack, definitionStack)) { // if with function, divide to var

        printf("%s = is ",  (char*)definitionStack->data[definitionStack->size-1]); // var

        for (size_t i = 0; i < pathStack->size; i++) {

            if (!strcmp((char*)pathStack->data[i], "NO")) {
                printf("%s %s, ", "not", (char*)definitionStack->data[i]); //stack size
            }
            else
                printf("%s, ", (char*)definitionStack->data[i]);
        }

        while (definitionStack->size > 0) {
            free(Pop(definitionStack)); // pop free by itself, memcpy by a pointer -> free by pointer
        }

        StackDtor(definitionStack);

    } else {
            printf("Word not found in the tree.\n");
        }
}

Node* FindNodeByWord(Node* root, const char* word, Stack* pathStack) {

    if (!root || pathStack->size >= pathStack->capacity - 1) {
        return nullptr;
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

        char* yes_str = strdup("YES"); // consts or bool stack, bs is better
        Push(pathStack, yes_str);

        Node* rightResult = FindNodeByWord(root->right, word, pathStack);

        if (rightResult) return rightResult;

        free(Pop(pathStack));
    }

    return nullptr;
}

void SelectMode(Node* root, Stack* pathStack) { // user interact

    printf("Choose an option:\n");
    printf("1. Run Akinator\n");
    printf("2. Find definition of a word\n");

    int choice = 0;
    scanf("%d", &choice);

    if (choice == 1) {
        RunAkinator(root);
    }

    else if (choice == 2) { // enum
        FindDefinition(root, pathStack);
    }

    else {
        printf("Invalid choice.\n");
    }
}
