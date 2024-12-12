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

Réalisation du code du Chenillard (Teest.c)

```
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define LED_PATH "/sys/class/leds/fpga_led%d/brightness"
#define NUM_LEDS 4  // Nombre total de LEDs disponibles
#define DELAY 200000 // Délai en microsecondes (200 ms)

void set_led(int led, int value) {
    char path[50];
    int fd;

    // Construire le chemin du fichier correspondant à la LED
    snprintf(path, sizeof(path), LED_PATH, led);

    // Ouvrir le fichier en écriture
    fd = open(path, O_WRONLY);
    if (fd < 0) {
        perror("Erreur d'ouverture du fichier LED");
        return;
    }

    // Écrire la valeur dans le fichier (1 pour allumer, 0 pour éteindre)
    if (write(fd, value ? "1" : "0", 1) < 0) {
        perror("Erreur lors de l'écriture dans le fichier LED");
    }

    // Fermer le fichier
    close(fd);
}

int main() {
    while (1) {
        // Allumer les LEDs une par une dans l'ordre
        for (int i = 0; i < NUM_LEDS; i++) {
            set_led(i, 1);  // Allumer la LED
            usleep(DELAY);  // Attendre un délai
            set_led(i, 0);  // Éteindre la LED
        }

        // Allumer les LEDs dans l'ordre inverse (optionnel)
        for (int i = NUM_LEDS - 1; i >= 0; i--) {
            set_led(i, 1);  // Allumer la LED
            usleep(DELAY);  // Attendre un délai
            set_led(i, 0);  // Éteindre la LED
        }
    }

    return 0;
}
```

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

### Télechargement des paquets pour compilation des modules noyau dans la VM:

![image](https://github.com/user-attachments/assets/47f59667-4b7a-4528-819a-2b59d9b3888c)

![image](https://github.com/user-attachments/assets/fd128dee-4536-4e4d-a2e7-ee3562a2acc3)

# Test insmod :
# Test modinfo :


