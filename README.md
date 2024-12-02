# 2425_TP_LINUX_BENABDELHADI_FARIS
## Préparation de la carte SD

### Préparation de la carte SD
## Etapes:
1. Lancement du Win32DiskImager.
2. Sélection du  l’image (VEEK_MT2S_LXDE.img).
3. Sélection du lecteur .
4. Ecriture pour flasher la carte SD.
   
![image](https://github.com/user-attachments/assets/b3555d54-f6e2-4337-bcde-be3c87980b0c)

### Utilisation d'un logiciel de liaison série
1. Mode de connexion : Serial.
2. Port série : COMX (remplacez X par le numéro trouvé).
3. Vitesse : 115200 bauds.
   
![image](https://github.com/user-attachments/assets/d61ea4de-69fb-4e8f-8611-320707ef7b16)

### identification:

![image](https://github.com/user-attachments/assets/8f5dbdf7-50ae-41d1-a41b-afd3065e56b2)

![image](https://github.com/user-attachments/assets/7ce8a41f-8ce5-4c7c-996c-8ac23ebc83c7)

![image](https://github.com/user-attachments/assets/e8435da5-a060-4dbc-92f2-5fa204f26738)
![image](https://github.com/user-attachments/assets/de458e7d-c605-4c9e-90e7-7cf30a5fad59)
taille
![image](https://github.com/user-attachments/assets/9418fee4-4fed-4b9e-8dee-9b43137ecc52)

![image](https://github.com/user-attachments/assets/f31da8d7-b78a-4f53-bc1d-372a0053ec0e)

if config :

![image](https://github.com/user-attachments/assets/8854a7ac-e403-4a9a-a912-5a4afd551e36)

modif 
![image](https://github.com/user-attachments/assets/9993bbc4-3da1-4e3d-aa99-3f920a1aff36)
if confi 
![image](https://github.com/user-attachments/assets/959f6582-c77c-460f-a285-11d3de96d867)

Ping 

![image](https://github.com/user-attachments/assets/79aec3d9-24aa-4ad1-9b5b-a72ba57992b7)
permitEmptyPasswords

![image](https://github.com/user-attachments/assets/788bdbda-afab-43fd-8bef-65648f8f56ba)


Connexion SSH 

![image](https://github.com/user-attachments/assets/52f6fb21-5082-4e22-a4f8-6f6d33953bce)


Exploration des fichier 

![image](https://github.com/user-attachments/assets/19a888ae-4d52-4c24-9f7f-8cc169631911)

hello
![image](https://github.com/user-attachments/assets/6e25a9e1-5e87-4d53-a794-0b079dbc4cc7)

Erreur 

![image](https://github.com/user-attachments/assets/7a0ae7b5-965d-4bb5-bab2-aff53cedb963)


![image](https://github.com/user-attachments/assets/36385ff5-b0c2-4b79-9dda-a1b2a7a46d94)

Hello world dans SSh terminal

![image](https://github.com/user-attachments/assets/aafa0365-a296-452e-8675-283091c75773)

les leds:
![image](https://github.com/user-attachments/assets/9095f4a6-ec87-4f08-b939-acd157c8043b)

led 1:

```
echo "1" > /sys/class/leds/fpga_led1/brightness

```




![image](https://github.com/user-attachments/assets/b2013747-b4f5-46ce-9f5f-fc7e78aedab7)


![WhatsApp Image 2024-12-02 at 17 14 29](https://github.com/user-attachments/assets/2810933a-10dc-4c37-8dd1-76df83204426)

d'autre leds:

![WhatsApp Image 2024-12-02 at 17 15 54](https://github.com/user-attachments/assets/70c9370d-a938-4003-a812-f7caf8f54a08)


Teest.c

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


execution du Chenillard dans le SSH

![image](https://github.com/user-attachments/assets/9dc9b490-401d-4d43-8055-dcafbf9d08e1)

