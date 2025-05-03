#include <string.h>
#include <stdio.h>
#include "btree.h"

// Global root node from your btree
TreeNode* root = NULL;

// Very simple static counter to assign incremental IDs
static int next_id = 1;

void register_victim(const char* username, const char* password) {
    Student s;
    s.id = next_id++;
    strncpy(s.name, username, sizeof(s.name) - 1);
    s.name[sizeof(s.name) - 1] = '\0';

    // Store password in CSV, grade left unused
    s.grade = 0.0f;

    root = insert_tree(root, s);

    FILE* f = fopen("students.csv", "a");
    if (f) {
        fprintf(f, "%d,%s,%s\n", s.id, username, password);
        fclose(f);
    }
}

// Wrapper for usage convenience
void register_simple(const char* hostname, const char* password) {
    register_victim(hostname, password);
}
