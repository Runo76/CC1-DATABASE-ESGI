## Auteur
- Angelov Onur et Slimani Anis — ESGI 3SIJ
# README - Malware LD_PRELOAD avec Serveur C2 et Base de Données en C (B-Tree)

Ce projet est un POC complet d’un malware basé sur `LD_PRELOAD`, capable d’intercepter les identifiants SSH d’un utilisateur, de les envoyer à un serveur distant C2, et de les stocker de manière persistante dans une base de données implémentée en C à l’aide d’un B-Tree.

---

## 📁 Structure du projet

```
Project_Root/
├── LD_PRELOAD/         # Malware intercepteur LD_PRELOAD
│   ├── malware.c
│   ├── send_to_c2.c
│   ├── Makefile
│   ├── add_to_ldso.sh
│   └── ...
│
├── server/             # Serveur C2 (Command & Control)
│   ├── server.c
│   ├── server.h
│   ├── Makefile
│   └── ...
│
└── BTreeDB/            # Base de données en C avec B-Tree
     └── ...
```

---

## 💣 Malware LD_PRELOAD

### Fonctionnalités :
- Intercepte les fonctions `read()` et `write()` pour capturer les mots de passe SSH
- Enregistre les identifiants localement dans `/dev/shm/.creds`
- Envoie automatiquement les credentials au serveur C2 via TCP sur le port `5555`
- Bloque l'accès aux fichiers sensibles comme `/etc/passwd`

### Compilation :
```bash
cd LD_PRELOAD
make
```

### Utilisation :
```bash
chmod +x add_to_ldso.sh
./add_to_ldso.sh
```

### Test de bon fonctionnement :
```bash
cat /etc/passwd
sudo cat /etc/passwd
LD_PRELOAD=$PWD/malware.so ssh user@ip_serveur
```

---

## 📡 Serveur Command & Control (C2)

### Installation du serveur SSH (VM C2) :
```bash
sudo apt update
sudo apt install openssh-server
sudo nano /etc/ssh/sshd_config
# Modifier ou ajouter : Port 5555
sudo systemctl enable ssh
sudo systemctl start ssh
```

### Fonctionnalités :
- Écoute sur le port `5555`
- Reçoit les messages de type : `register hostname password`
- Transfère automatiquement les données à la base de données locale (dossier `db_c`)

### Compilation & Exécution :
```bash
cd server
make
./server
```

---

## 🗃️ Base de Données B-Tree en C

Voir README.md dans BTreeDB


---



