#include "repl.h"
#include "btree.h"
#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void repl() {
    BTreeNode* root = NULL;
    char buffer[256];
    printf("commande: \n insert, ex: insert 1 anis anis@gmail.com \n select \n delete\n update\n .exit\n"); 
    printf(" () Chargement de la base...\n");
    printf("Bienvenue dans la db ! ");

    FILE* file = fopen("database.db", "rb");
    if (file) {
        root = loadTree(file);
        fclose(file);
    }
    while (1) {
        printf("Séléctionner une commande dans la db >");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        if (strcmp(buffer, ".exit") == 0) {
	    printf("() Données sauvegardées avec succès !\n");
            printf("À Bientôt !\n");
            file = fopen("database.db", "wb");
            saveTree(root, file);
            fclose(file);
            freeTree(root);
            break;
        }

        if (strncmp(buffer, "insert", 6) == 0) {
            Line line;
            sscanf(buffer, "insert %d %s %s", &line.id, line.username, line.email);
            root = btree_insert(root, line);
            printf("Élément Inséré.\n");

        } else if (strcmp(buffer, "select") == 0) {
            printf("Parcour de l'arbre :\n");
            btree_traverse(root);

        } else if (strncmp(buffer, "update", 6) == 0) {
            int id;
            char username[COLUMN_USERNAME_SIZE], email[COLUMN_EMAIL_SIZE];
            sscanf(buffer, "update %d %s %s", &id, username, email);
            btree_update(root, id, username, email);
            printf("Élément Mis à jour.\n");

        } else if (strncmp(buffer, "delete", 6) == 0) {
            int id;
            sscanf(buffer, "delete %d", &id);
            root = btree_delete(root, id);
            printf("Élément Supprimé.\n");

        } else {
            printf("Commande non reconnue '%s'\n", buffer);
        }
    }
}

