#include <stdio.h>
#include <assert.h>

#include "dump.h"
#include "tree.h"
#include "functions.h"
#include "akinator.h"

static int ARGS_REQUIRED_NUMBER = 2;
static size_t INPUT_FILE_NAME_INDEX = 1;

int main(int argc, const char** argv) {

    assert(argc == ARGS_REQUIRED_NUMBER);
    assert(argv[INPUT_FILE_NAME_INDEX]);

    FILE* tree_file = fopen(argv[INPUT_FILE_NAME_INDEX], "r");
    assert(tree_file);

    Node* root = TreeFromFile(tree_file);
    fclose(tree_file);

    // Definition(root);
    RunAkinator(root);

    if (root) {
        TreeDump(root);
        TreeDtor(root);
    }

    return 0;
}
