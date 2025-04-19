#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "btree.h"

TreeNode* root = NULL;

void test_insert_student() {
    // Reset file
    FILE* file = fopen("teststudents.csv", "w");
    fclose(file);
    root = NULL;

    Student student = {1, "Alice", 95.5};
    root = insert_tree(root, student);

    file = fopen("teststudents.csv", "w");
    save_tree_to_file(root, file);
    fclose(file);

    // Read back the file and check
    file = fopen("teststudents.csv", "r");
    assert(file != NULL);

    char line[256];
    fgets(line, sizeof(line), file);
    fclose(file);

    line[strcspn(line, "\r\n")] = 0;
    assert(strcmp(line, "1,Alice,95.50") == 0);

    printf("test_insert_student passed.\n");
}

