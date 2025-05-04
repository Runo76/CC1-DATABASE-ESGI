#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../BTreeDB/btree.h"
#include "../BTreeDB/persistence.h"

// Chemin de ta vraie base
#define DB_PATH "../BTreeDB/database.db"

// Fonction appelée par server.c
void register_simple(const char* username, const char* password) {
    BTreeNode* root = NULL;

    // Chargement
    FILE* f = fopen(DB_PATH, "rb");
    if (f) {
        root = loadTree(f);
        fclose(f);
    }

    // Création de la ligne
    Line line;
    line.id = rand() % 10000;  // ou autre génération
    strncpy(line.username, username, sizeof(line.username) - 1);
    line.username[sizeof(line.username) - 1] = '\0';
    strncpy(line.email, password, sizeof(line.email) - 1);
    line.email[sizeof(line.email) - 1] = '\0';

    // Insertion
    root = btree_insert(root, line);

    // Sauvegarde
    f = fopen(DB_PATH, "wb");
    if (f) {
        saveTree(root, f);
        fclose(f);
    }

    freeTree(root);  // Nettoyage mémoire
}

