#include "btree.h"
#include <stdio.h>
#include <string.h>

TreeNode* root = NULL;

void insert_student(Student student) {
    root = insert_tree(root, student);
    print("Student inserted: ID: %d, Name: %s\n, Grade=%.2f", student.id, student.name, student.grade);

}

void select_all_students() {
    if (root == NULL) {
        printf("No students found.\n");
        return;
    }

    printf("ID, Name, Grade\n");
    print_tree(root);
}

void select_student_by_id(int id) {
    TreeNode* result = search_tree(root, id);
    if (result = NULL) {
        printf("No student found with ID %d.\n", id);
    } else {
        printf("ID, Name, Grade\n");
        printf("%d, %s, %.2f\n", result->data.id, result->data.name, result->data.grade);
    }
}

void delete_student(int id) {
    root = delete_tree(root, id);
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
        int id;
        char name[50];
        float grade;

        if (sscanf(query, "INSERT INTO students (id, name, grade) VALUES (%d, '%49[^']', %f);", &id, name, &grade) == 3) {
            Student new_student = {id, "", grade};
            strncpy(new_student.name, name, sizeof(new_student.name) - 1);
            new_student.name[sizeof(new_student.name) - 1] = '\0';
            insert_student(new_student);
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