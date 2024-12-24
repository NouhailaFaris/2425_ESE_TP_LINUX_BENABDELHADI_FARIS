# 2425_TP_LINUX_BENABDELHADI_FARIS

## Introduction

Ce TP, réalisé par **Mohamed Benabdelhadi** et **Nouhaila Faris**, utilise la carte **VEEK-MT2S** et a pour objectif de manipuler un système **Linux embarqué**. 

## Objectifs spécifiques

1. **Prise en main de l'environnement Linux embarqué** 
2. **Configuration matérielle et logicielle** 
3. **Développement de modules noyaux**

## Préparation de la carte SD
### Utilisation de Win32DiskImager

Nous utilisons **Win32DiskImager** pour flasher une carte SD avec une image système. Cette étape est cruciale dans les projets de systèmes embarqués, comme dans ce TP utilisant Linux embarqué sur la carte **VEEK-MT2S**.

### Utilisation de PuTTY

**PuTTY** est un client de communication essentiel pour interagir avec des systèmes embarqués comme la carte **VEEK-MT2S** dans ce TP. Il permet d'établir des connexions série et SSH avec le système Linux embarqué.

### Etapes:
1. Lancement du Win32DiskImager.
2. Sélection du  l’image (VEEK_MT2S_LXDE.img).
3. Sélection du lecteur .
4. Ecriture pour flasher la carte SD.
   
![image](https://github.com/user-attachments/assets/b3555d54-f6e2-4337-bcde-be3c87980b0c)

### Utilisation d'un logiciel de liaison série
1. Mode de connexion : Serial.
2. Port série : COM10.
3. Vitesse : 115200 bauds.
   
![image](https://github.com/user-attachments/assets/d61ea4de-69fb-4e8f-8611-320707ef7b16)

### identification:

![image](https://github.com/user-attachments/assets/8f5dbdf7-50ae-41d1-a41b-afd3065e56b2)

![image](https://github.com/user-attachments/assets/7ce8a41f-8ce5-4c7c-996c-8ac23ebc83c7)

## Une fois connecté au SoC :

On remarque que au début nous avons un total de 5go en stockage sachant qu'on a utilisé une carte sd de 32 go 

![image](https://github.com/user-attachments/assets/e8435da5-a060-4dbc-92f2-5fa204f26738)

## Gestion de l'espace disque sur la carte SD

### Commandes utilisées

- **`df -h`** : Affiche l'espace disque utilisé et disponible dans un format lisible.  
- **`./expand_rootfs.sh`** : Étend la partition principale pour utiliser tout l'espace disponible sur la carte SD.  
- **`./resize2fs_once`** : Redimensionne le système de fichiers pour occuper toute la partition étendue.

![image](https://github.com/user-attachments/assets/de458e7d-c605-4c9e-90e7-7cf30a5fad59)


![image](https://github.com/user-attachments/assets/9418fee4-4fed-4b9e-8dee-9b43137ecc52)

Apres l'utilisation du script d'augmentation de taille en retrouve nos 32 go 

![image](https://github.com/user-attachments/assets/f31da8d7-b78a-4f53-bc1d-372a0053ec0e)

## Configuration réseau

## Commande `ifconfig`

La commande **`ifconfig`** est utilisée pour afficher et configurer les interfaces réseau. Elle est essentielle dans ce TP pour vérifier l'état du réseau de la carte.

### Utilisations principales :
- Vérifier si une adresse IP a été attribuée à la carte après la configuration réseau.
- Diagnostiquer les connexions réseau et obtenir des informations sur les interfaces.


![image](https://github.com/user-attachments/assets/8854a7ac-e403-4a9a-a912-5a4afd551e36)

modification du fichier interfaces

![image](https://github.com/user-attachments/assets/9993bbc4-3da1-4e3d-aa99-3f920a1aff36)

## if config:

notre adresse IP: 192.168.0.235

![image](https://github.com/user-attachments/assets/959f6582-c77c-460f-a285-11d3de96d867)

## Ping:

J'ai pu ping la machine depuis mon PC 

![image](https://github.com/user-attachments/assets/79aec3d9-24aa-4ad1-9b5b-a72ba57992b7)

## permitEmptyPasswords

- Permet d'autoriser les connexions SSH à des comptes sans mot de passe.  
- Simplifie les connexions dans des environnements de test ou de développement, comme dans ce TP, pour interagir facilement avec le système embarqué.  

![image](https://github.com/user-attachments/assets/788bdbda-afab-43fd-8bef-65648f8f56ba)

## Connexion SSH 

![image](https://github.com/user-attachments/assets/52f6fb21-5082-4e22-a4f8-6f6d33953bce)

# Découverte de la cible
## Exploration des fichier 

![image](https://github.com/user-attachments/assets/19a888ae-4d52-4c24-9f7f-8cc169631911)

## Exploration des fichiers système : `/proc` et `/sys/class`

Dans ce TP, nous explorons des répertoires et fichiers spécifiques au système Linux embarqué. Ces fichiers permettent de mieux comprendre l'interaction entre le matériel et le noyau.

### 1. `/proc`

Le répertoire **`/proc`** est un système de fichiers virtuel qui fournit une vue en temps réel des données système. Son contenu est généré dynamiquement par le noyau et reflète l'état actuel du matériel.

#### Fichiers clés :
- **`/proc/cpuinfo`** :
  - Contient des informations détaillées sur le processeur, comme son modèle, sa fréquence, et le nombre de cœurs.
  - Utile pour comprendre les capacités matérielles de votre système embarqué.
- **`/proc/ioports`** :
  - Affiche les plages d'adresses des ports d'entrée/sortie utilisés par le matériel.
  - Permet d'identifier quels périphériques matériels occupent quelles plages d'E/S.
- **`/proc/iomem`** :
  - Liste les plages d'adresses mémoire réservées pour les périphériques matériels.
  - Permet de visualiser la manière dont le matériel est mappé en mémoire.
- **`/proc/device-tree/sopc@0`** :
  - Contient les données extraites du **Device Tree**, qui décrit la structure matérielle.
  - Utile pour faire correspondre les périphériques physiques et leurs adresses mémoire logiques.

---

### 2. `/sys/class`

Le répertoire **`/sys/class`** fait partie du système de fichiers **sysfs**, qui expose une interface directe au noyau pour accéder aux périphériques matériels.

#### Entrées clés :
- **`/sys/class/leds/fpga_ledX/`** :
  - Fournit une interface pour contrôler les LEDs de la carte FPGA.
  - Exemple d'utilisation pour allumer une LED :
    ```bash
    echo "1" > /sys/class/leds/fpga_led1/brightness
    ```
  - Exemple pour éteindre la LED :
    ```bash
    echo "0" > /sys/class/leds/fpga_led1/brightness
    ```

---

Ces fichiers permettent d'accéder directement au matériel, de diagnostiquer son fonctionnement et de configurer certains périphériques. Ils sont essentiels pour comprendre et manipuler un système Linux embarqué.


# hello world !

![image](https://github.com/user-attachments/assets/6e25a9e1-5e87-4d53-a794-0b079dbc4cc7)

Quand on essaie de lancer le programme sur la VM en recoit une Erreur 

![image](https://github.com/user-attachments/assets/7a0ae7b5-965d-4bb5-bab2-aff53cedb963)

Donc on a copier le fichier hello.o sur la carte et comme ca on a pu l'executer 

![image](https://github.com/user-attachments/assets/36385ff5-b0c2-4b79-9dda-a1b2a7a46d94)

Hello world dans SSh terminal

![image](https://github.com/user-attachments/assets/aafa0365-a296-452e-8675-283091c75773)

## Accès au matériel

### dossier des leds:

![image](https://github.com/user-attachments/assets/9095f4a6-ec87-4f08-b939-acd157c8043b)

led 1:

```
echo "1" > /sys/class/leds/fpga_led1/brightness

```

![image](https://github.com/user-attachments/assets/b2013747-b4f5-46ce-9f5f-fc7e78aedab7)


![WhatsApp Image 2024-12-02 at 17 14 29](https://github.com/user-attachments/assets/2810933a-10dc-4c37-8dd1-76df83204426)

d'autre leds(led 2):

![WhatsApp Image 2024-12-02 at 17 15 54](https://github.com/user-attachments/assets/70c9370d-a938-4003-a812-f7caf8f54a08)

## Chenillard

**Réalisation du code du Chenillard**: ( le code est déposé sur git :Teest.c)

**l'envoie du Code teest.o vers la carte**
![image](https://github.com/user-attachments/assets/9bb0c7c5-82d8-4d45-b52a-27dc3e2b7c9f)


### execution du Chenillard dans le SSH

![image](https://github.com/user-attachments/assets/9dc9b490-401d-4d43-8055-dcafbf9d08e1)

# 2 Modules kernel (TP2)

## 2.1 Accès aux registres

On a créer le fichier regictre2.c pour faire un chenillard des 3 premiers leds avec la méthodes 

![image](https://github.com/user-attachments/assets/a2489e51-08d7-4932-93c3-628591a12452)

### Limites et problèmes de cette méthode

- **Manque d'isolation** : 
  L'accès direct au matériel contourne l'abstraction offerte par le noyau, ce qui peut provoquer des conflits si d'autres parties du système utilisent les mêmes ressources.
  
- **Sécurité** : 
  L'accès direct peut exposer le système à des comportements imprévisibles si les permissions ou adresses sont mal configurées.
  
- **Prototypage uniquement** : 
  Cette méthode est utile pour tester rapidement une fonctionnalité, mais elle n'est pas adaptée pour un déploiement en production.
## 2.2 Compilation de module noyau sur la VM
### Télechargement des paquets pour compilation des modules noyau dans la VM:
```
sudo apt install linux-headers-amd64 bc
```

![image](https://github.com/user-attachments/assets/162572aa-547f-41e1-9fc9-615c590100e5)

**Compilation et test**

Apres le telechargement du makefile et du hello.c on a executer la commande **make**: 

![image](https://github.com/user-attachments/assets/fd128dee-4536-4e4d-a2e7-ee3562a2acc3)

### Test modinfo : (Affiche les informations sur le module)
![image](https://github.com/user-attachments/assets/95c98c1c-2005-4757-b9a4-38765a59c32b)

### Test insmod : (Charge le module dans le noyau)
![image](https://github.com/user-attachments/assets/10fa03e9-e714-45a1-86ea-d55b28d64d71)

### Test dmesg : (Vérifie les logs système pour valider l'exécution)
![image](https://github.com/user-attachments/assets/3161337b-939c-4e57-8cff-343aaeb46853)

### Test rmmod :( Décharge le module)
![image](https://github.com/user-attachments/assets/30e66b43-2a54-453b-8a20-f1bd810a42ef)


### Test lsmod : (afficher la liste des modules actuellement chargés dans le noyau Linux)

![image](https://github.com/user-attachments/assets/6cb26558-ab0d-451e-b3b0-e020b9ba8458)

### utilisation de paramètres au chargement du module:²
```
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int param = 1; // Paramètre par défaut
module_param(param, int, S_IRUGO); // Permet de définir un paramètre au chargement
MODULE_PARM_DESC(param, "A parameter for demonstration");
```
![image](https://github.com/user-attachments/assets/38a05a3f-a058-4a8c-96d7-cd1d8b53a56b)

L'erreur qu'on a :**ERROR: could not insert module hello.ko: File exists**, indique que le module hello.ko est déjà chargé dans le noyau.

![image](https://github.com/user-attachments/assets/ce5a33c5-a074-4c69-a4e1-33137094426b)

**Solution :**

1-Déchargez le module existant

2-Rechargez le module avec un paramètre

![image](https://github.com/user-attachments/assets/a2fc2656-da65-4788-ad44-8c8846d9cf92)

### Utilisation de paramètres au chargement du module et création d'une entrée dans /proc.

![image](https://github.com/user-attachments/assets/4350da24-52d0-4a65-9817-c70d27e2f500)

**Probleme rencontré:** le fichier timer_module.ko n'est pas créer quand on execute la commande make

![image](https://github.com/user-attachments/assets/ff656704-e61c-4135-a2fe-57f35297007f)

contenu fichier make :
```
obj-m:=hello.o
KERNEL_SOURCE=/lib/modules/$(shell uname -r)/build

all :
	make -C $(KERNEL_SOURCE) M=$(PWD) modules
clean :
	make -C $(KERNEL_SOURCE) M=$(PWD) clean
install :
	make −C $(KERNEL_SOURCE) M=$(PWD) modules install
```
 solution :
 ```
 obj-m += timer_module.o
```
![image](https://github.com/user-attachments/assets/35248af6-c30b-4b22-bc10-d789d53c6bf4)

### Timer:

![image](https://github.com/user-attachments/assets/e3db74cd-8286-4884-9ac7-b8d47fce6894)

## 2.3 CrossCompilation de modules noyau

### 2.3.0 Récupération du Noyau Terasic

Partie déjà faite pour tester on execute Uname -a

**Uname -a**

![image](https://github.com/user-attachments/assets/af07dbf0-0e7b-4a68-9253-40d151091e71)

### 2.3.1 Préparation de la compilation

![image](https://github.com/user-attachments/assets/cd3cdab9-443b-4154-905d-c985b4ec3e59)

 le chemin vers les compilateurs : **/usr/bin/arm-linux-gnueabihf-gcc**

### 2.3.2 Récupéreation de la configuration actuelle du noyau

On a envoyé le fichier à la VM et le renommé 
![WhatsApp Image 2024-12-12 at 11 30 26](https://github.com/user-attachments/assets/c88397b0-fc86-4d57-ae8f-8d67976502d6)

**Configuration du environnement pour la compilation croisée :** (on a <chemin_arm-linux-gnueabihf-> par le chemin correct vers votre compilateur croisé, sans le gcc final.)

Pour nous c'est **/usr/bin/arm-linux-gnueabihf-**.

![WhatsApp Image 2024-12-12 at 11 35 19](https://github.com/user-attachments/assets/478fdea4-b658-4a92-8398-b1d216460934)

### — Quel est le rôle des lignes commençant par export ?

-Exporter une ressource (par exemple, un GPIO, une LED, ou un périphérique).

-Cela rend un périphérique accessible depuis l'espace utilisateur ou visible pour d'autres modules/drivers.

-Dans le contexte des GPIOs, export permet de rendre un GPIO visible dans le répertoire /sys/class/gpio/.



**Make prepare:**

![WhatsApp Image 2024-12-12 at 11 36 44](https://github.com/user-attachments/assets/24fafa91-7f7b-4e05-8b2c-ef09c246fb6f)

**Make scripts**

![WhatsApp Image 2024-12-12 at 11 37 36](https://github.com/user-attachments/assets/109ffa57-0925-4aaa-a881-8fdbeae78807)

#### Pourquoi make prepare et make scripts ?

Ces commandes génèrent les fichiers nécessaires pour la compilation de modules, comme les fichiers d'en-tête et les scripts.

### 2.3.3 Hello World

**Modification du Makefile**

- Mise à jour le chemin vers le noyau
- Ajouter CFLAGS_MODULE=-fno-pic

![WhatsApp Image 2024-12-16 at 14 38 54](https://github.com/user-attachments/assets/5b2d5e24-0dbb-4287-bbe0-db3840b6180d)

**chargement et test sur la Carte**

- Modification de l'emplacement des fichiers en dehors du dossier SRC
- Execution du makefile et envoie du fichier hello.ko
- Test avec insmod et dmesg|tail

![image](https://github.com/user-attachments/assets/d2092a3c-9001-40d1-a005-8a0b68a3f467)

# TP3
## Device tree

**Telechargement du fichier VEEK-MT2S_v.1.0.3_SystemCD.zip**

![image](https://github.com/user-attachments/assets/9b6d3f9d-1497-44fc-af38-9904b91538dc)

### Recherche le fichier texte
![image](https://github.com/user-attachments/assets/a531d2b7-abee-4498-875c-39602391073f)

Déplacement du fichier :
**cp soc_system.dts ~/TP/**

**Remarque: le dossier TP est le nouveau dossier créer dans TP2 2.3.3**

![image](https://github.com/user-attachments/assets/8dc6a1d2-3f63-42ab-ac57-2f5271136dbd)

Montage de la partition

![image](https://github.com/user-attachments/assets/442df195-51d1-498d-a7fa-9623273830e1)

![image](https://github.com/user-attachments/assets/1a2824a0-816b-4309-93ab-3450a223977c)

Renommez le fichier dtb en .old 
![image](https://github.com/user-attachments/assets/ea2f432f-9e7a-4826-9fe9-076d0b5f59e2)

Envoie du Nouveau Fichier
![image](https://github.com/user-attachments/assets/4b523808-b440-42c6-8f9b-e5aa95fa9938)

Ajouter dans makefile 

![image](https://github.com/user-attachments/assets/96418cf2-bde3-4085-aa0a-5cacdc63f5de)

![image](https://github.com/user-attachments/assets/3d3631cc-fd79-4276-9fae-45256573966b)

Envoi vers la carte CD:
![image](https://github.com/user-attachments/assets/19bda25d-e8f0-4f21-a8c1-8036a5fc7d87)


**Chargement, test et verification des logs**

![image](https://github.com/user-attachments/assets/7354aea7-5949-48b2-a286-b808543d5057)


![WhatsApp Image 2024-12-16 at 16 07 27](https://github.com/user-attachments/assets/cc10d799-d171-42f5-9d23-96c618351307)


### Test du  fichier:

| **Fonction** | **Rôle** | **Moment d'exécution** |
|--------------|----------|------------------------|
| **`probe`** | Initialise le périphérique lorsqu'il est détecté (registre mémoire, fichier `/dev`). | Lors du chargement du module (`insmod`). |
| **`read`**  | Lit la valeur actuelle des LEDs et la transmet à l'espace utilisateur. | Lors d'une lecture du fichier `/dev/ensea_leds`. |
| **`write`** | Écrit une nouvelle valeur dans les registres pour contrôler les LEDs. | Lors d'une écriture dans `/dev/ensea_leds`. |
| **`remove`** | Libère les ressources, désactive les LEDs, et désenregistre le périphérique `/dev`. | Lors du retrait du module (`rmmod`). |

