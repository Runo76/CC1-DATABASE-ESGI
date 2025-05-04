#ifndef TEST_MAIN
#define TEST_MAIN

#include "btree.h"
#include "persistence.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void test_insert() {
    BTreeNode* root = NULL;
    Line line = {1, "anis", "anis@gmail.com"};

    root = btree_insert(root, line);
    assert(root != NULL);
    assert(root->line.id == 1);
    printf("[✓] Test Insert OK \n");

    freeTree(root);
}

void test_select() {
    BTreeNode* root = NULL;
    Line line1 = {1, "anis", "anis@gmail.com"};
    Line line2 = {2, "amine", "amine@gmail.com"};

    root = btree_insert(root, line1);
    root = btree_insert(root, line2);

    printf("[✓] Test Select :\n");
    btree_traverse(root);

    freeTree(root);

}

void test_update() {
    BTreeNode* root = NULL;
    Line line = {1, "anis", "anis@gmail.com"};

    root = btree_insert(root, line);
    btree_update(root, 1, "AnisUpdated", "anis_updated@gmail.com");

    assert(strcmp(root->line.username, "AnisUpdated") == 0);
    printf("[✓] Test Update OK \n");
    
    freeTree(root);

}

void test_delete() {
    BTreeNode* root = NULL;
    Line line = {1, "anis", "anis@gmail.com"};

    root = btree_insert(root, line);
    root = btree_delete(root, 1);

    assert(root == NULL);
    printf("[✓] Test Delete OK \n");

    freeTree(root);

}

void test_persistence() {
    FILE* file = fopen("db.txt", "w");
    BTreeNode* root = NULL;

    Line line = {1, "anis", "anis@gmail.com"};
    root = btree_insert(root, line);
    saveTree(root, file);
    fclose(file);

    file = fopen("db.txt", "r");
    BTreeNode* loaded_tree = loadTree(file);
    fclose(file);

    assert(loaded_tree->line.id == 1);
    printf("[✓] Test Persistance OK \n");

    freeTree(root);
    freeTree(loaded_tree);

}

#ifdef TEST_MAIN
int main() {
    printf("\n--- Lancement des Tests ---\n");

    test_insert();
    test_select();
    test_update();
    test_delete();
    test_persistence();

    printf("\n TOUS LES TESTS SONT PASSÉS AVEC SUCCÈS \n");

    return 0;
}
#endif

#endif

