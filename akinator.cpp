#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "akinator.h"
#include "functions.h"

static char* AskQuestion(Node* node);
static void ClearBuffer();

bool RunAkinator(Node* node) {
// types of functions, akinator works with 2 types: run

	Node* root = node;

    while (true) {

		char* answer = AskQuestion(node);

        if (!strcmp(answer, "yes")) {

            if (node->right != nullptr)
            {
                node = node->right;
            }

            else {
                puts("i guessed, you are so silly");
                return false;
            }
        }

        // separate functions
        else if (!strcmp(answer, "no")) {

            if (node->left != nullptr)
            {
                node = node->left;

            }

            else {
                puts("i am so sorry(");
				Insert(node);
				//node = root;
                return false;
            }
        }

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
