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