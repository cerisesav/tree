bool RunAkinator(Node* node) {

    while (true) {

        printf("%s ", node->data);
        char answer[MAX_LINE] = "";
// types of functions, akinator works with 2 types: run
        scanf("%s", answer);
        ClearBuffer();

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
                return false;
            }
        }

    }
}
