#include "btree.h"
#include <stdio.h>
#include <string.h>

// Global root node for the binary tree
TreeNode* root = NULL;

extern void insert_student(TreeNode** root, const char* name, float grade);

void select_all_students() {
    if (root == NULL) {
        printf("No students found.\n");
        return;
    }

    printf("ID, Name, Grade\n");
    inorder_traversal(root);
}

void select_student_by_id(int id) {
    TreeNode* result = search_tree(root, id);
    if (result == NULL) {
        printf("No student found with ID %d.\n", id);
    } else {
        printf("ID, Name, Grade\n");
        printf("%d, %s, %.2f\n", result->data.id, result->data.name, result->data.grade);
    }
}

void delete_student(int id) {
    root = delete_tree(root, id);
    rewrite_file_from_tree(root, "students.csv");
    persist_btree(root);
    printf("Student with ID %d deleted.\n", id);
}

void execute_command(const char* query) {
    if (strncmp(query, "SELECT", 6) == 0) {
        if (strcmp(query, "SELECT * students;") == 0) {
            select_all_students();
        } else if (strncmp(query, "SELECT FROM students WHERE id =", 31) == 0) {
            int id;
            if (sscanf(query, "SELECT FROM students WHERE id = %d;", &id) == 1) {
                select_student_by_id(id);
            } else {
                printf("Error: Malformed SELECT query.\n");
            }
        } else {
            printf("Error: Malformed SELECT query.\n");
        }
    } else if (strncmp(query, "INSERT", 6) == 0) {
        char name[50];
        float grade;

        if (sscanf(query, "INSERT INTO students (name, grade) VALUES ('%49[^']', %f);", name, &grade) == 2) {
            insert_student(&root, name, grade);
        } else {
            printf("Error: Malformed INSERT query.\n");
        }
    } else if (strncmp(query, "DELETE", 6) == 0) {
        int id;
        if (sscanf(query, "DELETE FROM students WHERE id = %d;", &id) == 1) {
            delete_student(id);
        } else {
            printf("Error: Malformed DELETE query.\n");
        }
    } else {
        printf("Unknown command: '%s'\n", query);
    }
}
