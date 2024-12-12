#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define GPIO_BASE 0xFF203000
#define MAP_SIZE 4096UL
#define NUM_LEDS 4 // Nombre total de LEDs
#define DELAY 200000 // Délai en microsecondes (200 ms)

int main() {
    int fd;
    volatile unsigned int *gpio_addr;

    // Ouvrir /dev/mem
    fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd == -1) {
        perror("Error opening /dev/mem");
        return -1;
    }

    // Mapper la mémoire du registre GPIO
    gpio_addr = mmap(NULL, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO_BASE);
    if (gpio_addr == MAP_FAILED) {
        perror("Error mapping memory");
        close(fd);
        return -1;
    }

    // Chenillard
    while (1) {
        // Allumer les LEDs une par une dans l'ordre
        for (int i = 0; i < NUM_LEDS; i++) {
            *gpio_addr = (1 << i); // Allumer une LED (en mettant un bit correspondant à 1)
            usleep(DELAY);        // Attendre un délai
        }

        // Allumer les LEDs dans l'ordre inverse
        for (int i = NUM_LEDS - 1; i >= 0; i--) {
            *gpio_addr = (1 << i); // Allumer une LED (en mettant un bit correspondant à 1)
            usleep(DELAY);        // Attendre un délai
        }
    }

    // Nettoyer la mémoire mappée et fermer /dev/mem
    munmap((void *)gpio_addr, MAP_SIZE);
    close(fd);
    return 0;
}
