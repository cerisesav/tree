#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "functions.h"

Node* FreeNode (int value, Node *parent) {
	Node* temp = (Node*) calloc(1, sizeof(Node));

	temp->left = temp->right = nullptr;
	temp->data = value;

	temp->parent = parent;

	return temp;
}

void Insert (Node **head, int value) {

    Node *temp = nullptr;

    if (*head == nullptr) {
        *head = FreeNode(value, nullptr);
        return;
    }

    temp = *head;

    while (temp) {

        if (CMP_GT(value, temp->data)) {

            if (temp->right) {
                temp = temp->right;
                continue;

            } else {
                temp->right = FreeNode(value, temp);
                return;
            }

        } else if (CMP_LT(value, temp->data)) {

            if (temp->left) {
                temp = temp->left;
                continue;

            } else {
                temp->left = FreeNode(value, temp);
                return;
            }

        } else {
            return;
        }
    }
}
