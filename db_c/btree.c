#include "btree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

TreeNode* insert_tree(TreeNode* root, Student student) {
    if (root == NULL) {
        TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
        new_node->data = student;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
    }

    if (student.id < root->data.id) {
        root->left = insert_tree(root->left, student);
    } else if (student.id > root->data.id) {
        root->right = insert_tree(root->right, student);
    }

    return root;
}

TreeNode* search_tree(TreeNode* root, int id) {
    if (root == NULL || root->data.id == id) {
        return root;
    }

    if (id < root->data.id) {
        return search_tree(root->left, id);
    } else {
        return search_tree(root->right, id);
    }
}

TreeNode* find_min(TreeNode* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

TreeNode* delete_tree(TreeNode* root, int id) {
    if (root == NULL) {
        return NULL;
    }

    if (id < root->data.id) {
        root->left = delete_tree(root->left, id);
    } else if (id > root->data.id) {
        root->right = delete_tree(root->right, id);
    } else {
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        TreeNode* temp = find_min(root->right);
        root->data = temp->data;
        root->right = delete_tree(root->right, temp->data.id);
    }

    return root;
}

void inorder_traversal(TreeNode* root) {
    if (root == NULL) return;

    inorder_traversal(root->left);
    printf("%d, %s, %.2f\n", root->data.id, root->data.name, root->data.grade);
    inorder_traversal(root->right);
}

void save_tree_to_file(TreeNode* root, FILE* file) {
    if (root == NULL || file == NULL) return;

    save_tree_to_file(root->left, file);
    fprintf(file, "%d,%s,%.2f\n", root->data.id, root->data.name, root->data.grade);
    save_tree_to_file(root->right, file);
}

void rewrite_file_from_tree(TreeNode* root, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file) {
        save_tree_to_file(root, file);
        fclose(file);
    }
}

void load_tree_from_file(TreeNode** root, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) return;

    char line[256];
    int max_id = 0;
    while (fgets(line, sizeof(line), file)) {
        Student student;
        sscanf(line, "%d,%49[^,],%f", &student.id, student.name, &student.grade);
        *root = insert_tree(*root, student);
        if (student.id > max_id) {
            max_id = student.id;
        }
    }
    fclose(file);

    FILE* fid = fopen("student_nextid.txt", "w");
    if (fid) {
        fprintf(fid, "%d", max_id);
        fclose(fid);
    }
}

int get_next_id() {
    int used[1000] = {0};

    FILE* f = fopen("students.csv", "r");
    if (f) {
        char line[256];
        int id;
        while (fgets(line, sizeof(line), f)) {
            if (sscanf(line, "%d,", &id) == 1) {
                if (id < 1000) used[id] = 1;
            }
        }
        fclose(f);
    }

    for (int i = 1; i < 1000; ++i) {
        if (!used[i]) return i;
    }

    return 1000;
}

void insert_credentials(TreeNode** root, const char* hostname, const char* password) {
    Student student;
    student.id = get_next_id();

    strncpy(student.name, hostname, sizeof(student.name) - 1);
    student.name[sizeof(student.name) - 1] = '\0';
    student.grade = 0.0f;

    *root = insert_tree(*root, student);
    rewrite_file_from_tree(*root, "students.csv");
    persist_btree(*root);
}

void insert_student(TreeNode** root, const char* name, float grade) {
    Student student;
    student.id = get_next_id();

    strncpy(student.name, name, sizeof(student.name) - 1);
    student.name[sizeof(student.name) - 1] = '\0';
    student.grade = grade;

    *root = insert_tree(*root, student);
    rewrite_file_from_tree(*root, "students.csv");
    persist_btree(*root);
}

void saveTreeBinary(TreeNode* root, FILE* file) {
    if (root == NULL) return;

    fwrite(&root->data, sizeof(Student), 1, file);
    saveTreeBinary(root->left, file);
    saveTreeBinary(root->right, file);
}

TreeNode* loadTreeBinary(FILE* file) {
    Student student;
    TreeNode* root = NULL;

    while (fread(&student, sizeof(Student), 1, file)) {
        root = insert_tree(root, student);
    }

    return root;
}

void persist_btree(TreeNode* root) {
    FILE* file = fopen("btree.bin", "wb");
    if (file) {
        saveTreeBinary(root, file);
        fclose(file);
    }
}

TreeNode* restore_btree() {
    FILE* file = fopen("btree.bin", "rb");
    if (!file) return NULL;

    TreeNode* root = loadTreeBinary(file);
    fclose(file);
    return root;
}
