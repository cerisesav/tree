#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "akinator.h"
#include "functions.h"

static char* AskQuestion(Node* node);
static void ClearBuffer();
static bool HandleYes(Node** node);
static bool HandleNo(Node** node);

bool RunAkinator(Node* node) {
    while (true) {

        char* answer = AskQuestion(node);

        if (!strcmp(answer, "yes")) {
            if (!HandleYes(&node)) {
                return false;
            }
        }

		else if (!strcmp(answer, "no")) {
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

static char* AskQuestion(Node* node) {

	printf("%s ", node->data);
	char answer[MAX_LINE] = "";

	scanf("%s", answer);
	ClearBuffer();
	return answer;
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
