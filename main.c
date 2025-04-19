#include <stdio.h>
#include <string.h>
#include "commands.h"
#include "btree.h"

extern TreeNode* root;

int main() {
    char query[256];
    load_tree_from_file(&root, "students.csv");

    while (1) {
        printf("db > ");
        fgets(query, sizeof(query), stdin);
        query[strcspn(query, "\n")] = 0; // Remove newline character

        if (strcmp(query, ".exit") == 0) {
            save_tree_to_file(root, fopen("students.csv", "w"));
            break;
        }

        execute_command(query);
    }

    return 0;
}
