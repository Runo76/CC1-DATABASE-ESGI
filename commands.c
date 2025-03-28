//#include "tree.h"
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

    printf("All students:\n");
    print_tree(root);
}

void select_student_by_id(int id) {
    TreeNode* student_node = search_tree(root, id);
    if (student_node != NULL) {
        printf("Student found: ID: %d, Name: %s, Grade=%.2f\n", student_node->student.id, student_node->student.name, student_node->student.grade);
    } else {
        printf("Student with ID %d not found.\n", id);
    }
}
