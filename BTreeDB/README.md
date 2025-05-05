# Projet BTree Database

# Description

Ce projet est une base de données simplifiée en langage C, implémentée avec des arbres binaires de recherche (B-Tree). Il permet de réaliser des opérations de gestion de données (CRUD) avec une persistance des informations sur fichier.

#Objectifs :
-Créer une base de données simple avec des opérations CRUD (Create, Read, Update, Delete).
-Utiliser une structure d'arbre binaire pour stocker les données.
-Implémenter la persistance des données dans un fichier texte.
-Effectuer des tests unitaires pour valider le bon fonctionnement du projet.



# Installation et Lancement
Pour installer **GCC, Make, Valgrind** (Distribution Debian/Ubuntu:
sudo apt update
sudo apt install gcc make valgrind

Sur Red Hat/CentOS (ex : Fedora, CentOS, RHEL) :
sudo dnf install gcc make valgrind

Sur Arch Linux ou Manjaro :
sudo pacman -S gcc make valgrind

# Prérequis
-l'éditeur de texte n'a pas d'importance l'essentiel est d'avoir **GCC** et     **Make** installé

-Installer **Valgrind** pour détecter les fuites mémoire (éxplication de pourquoi "Valgrind" et détaille de l'utilisation dans le "Rapport
Final")

-Système Linux avec **gcc** installé
-Make d'installé

-Utilisation de Vim (pour ma part)

# Étapes

$ cd BTreeProject
1. Compiler le projet :
#bash/Vim
$ make
-----------------------------
"Bonus" Lancer Valgrind avec l’option de vérification des fuites mémoire :

    valgrind --leak-check=full --show-leak-kinds=all ./db

Si tout est correct, Valgrind affichera à la fin du test :

==XXXXXX== All heap blocks were freed -- no leaks are possible
==XXXXXX== 
==XXXXXX== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

Ce message signifie que le programme ne présente aucune fuite mémoire et fonctionne correctement.
Sinon sauter le bonus et reprendre à l'étape 3 
---------------------------

2. Lancer la base de données :
#bash/Vim
$ ./db

3. Pour exécuter les tests unitaires :
#bash/Vim
$ make tests
$ ./tests/test
-----------------------------
"Bonus" pour les tests, Après avoir compilé le programme avec "make tests", lancer :

    valgrind --leak-check=full --show-leak-kinds=all ./tests/test

Le même message que dans le "Bonus" juste au dessus doit apparaître.
----------------------------- 
4. Make clean ?
-Faire "make clean" avant de compiler le projet avec "make" en cas de besoin    pour ne pas conserver de fichiers objets ou d'exécutables précédents 



# Fonctionnalités
| Fonction       | Description                 |
|----------------|-----------------------------|
| Insert         | Permet d'insérer une ligne dans l'arbre |
| Select         | Parcours et affiche toutes les lignes |
| Update         | Met à jour une ligne par ID   |
| Delete         | Supprime une ligne par ID     |
| Persistance    | Sauvegarde automatique dans un fichier **db.txt** |



#Structure du Projet

#Arborescence des fichiers

BTreeProject/
├── btree.c        # Fonctions de gestion de l'arbre
├── btree.h        # Définition des structures et prototypes
├── persistence.c  # Persistance des données
├── persistence.h  # Prototypes pour la persistance
├── table.c        # Gestion des lignes de la table
├── table.h        # Définition de la structure de données
├── repl.c         # Interface REPL 
├── repl.h         # Prototypes REPL
├── main.c         # Point d'entrée principal
├── Makefile       # Compilation automatique
└── tests/         # Tests unitaires
    └── test_btree.c
```
#Comment utiliser ?
Voici des exemples de commandes :
bash/Vim
db > insert 1 anis anis@gmail.com (id | nom ou autre | mail, mdp ou autre)
___________________________________________________
db > select
db > (affiche) 1 anis anis@gmail.com
___________________________________________________
db > update 1 Anis2 anis_updated@gmail.com (id | nom ou autre | mail, mdp ou autre)
db > select
db >(affiche)  1 AnisUpdated anis_updated@gmail.com
___________________________________________________
db > delete 1  (juste delete id)
db > .exit
``


# Tests Unitaires
Les tests unitaires sont réalisés pour :
-L'insert
-Update
-Delete
-Persistance

Pour exécuter les tests :
bash/Vim
$ make tests
$ ./tests/test

#Auteur
-Anis Slimani - Angelov Onur - Étudiant en Bachelor Cybersécurité 

#Remarque
Ce projet a été réalisé dans le cadre de la formation Bachelor Cybersécurité à lESGI.


#Merci pour votre attention ! 

