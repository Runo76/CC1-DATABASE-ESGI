#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../BTreeDB/btree.h"
#include "../BTreeDB/persistence.h"

#define DB_PATH "../BTreeDB/database.db"
#define ID_FILE "../BTreeDB/id_counter.txt"

void register_simple(const char* username, const char* password) {
    BTreeNode* root = NULL;

    // Chargement de la base existante
    FILE* f = fopen(DB_PATH, "rb");
    if (f) {
        root = loadTree(f);
        fclose(f);
    }

    // Créer la ligne à insérer
    Line line;

    // Lire et incrémenter ID unique
    int id = 1;
    FILE* fid = fopen(ID_FILE, "r+");
    if (fid) {
        fscanf(fid, "%d", &id);
        rewind(fid);
        fprintf(fid, "%d\n", id + 1);
        fclose(fid);
    } else {
        fid = fopen(ID_FILE, "w");
        if (fid) {
            fprintf(fid, "2\n");
            fclose(fid);
        }
    }
    line.id = id;

    // Remplir les champs
    strncpy(line.username, username, sizeof(line.username) - 1);
    line.username[sizeof(line.username) - 1] = '\0';
    strncpy(line.email, password, sizeof(line.email) - 1);
    line.email[sizeof(line.email) - 1] = '\0';

    // Insertion dans l’arbre
    root = btree_insert(root, line);

    // Sauvegarde
    f = fopen(DB_PATH, "wb");
    if (f) {
        saveTree(root, f);
        fclose(f);
    }

    freeTree(root);
}

