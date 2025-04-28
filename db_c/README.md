ANGELOV Onur 3SIJ
## Fonctionnalités

- **Ajout d'un étudiant** (via `INSERT`).
- **Consultation de tous les étudiants** (via `SELECT`).
- **Consultation d'un étudiant par ID**.
- **Suppression d'un étudiant** (via `DELETE`).


---

## Installation

Clonez ce dépôt GitHub sur votre machine locale :

```bash
https://github.com/Runo76/CC1-DATABASE-ESGI
Lancement
Compilez et exécutez le projet :
mingw32-make clean
mingw32-make
./db

Exemple de requêtes SQL

Ajouter un étudiant :
INSERT INTO students (id, name, grade) VALUES (1, 'Kiko', 15);

Consulter tous les étudiants :
SELECT * students;

Consulter un étudiant par ID :
SELECT FROM students WHERE id = 1;

Supprimer un étudiant :
DELETE FROM students WHERE id = 1;

Quitter le programme :
.exit
