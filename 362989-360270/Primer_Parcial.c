#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void mostrarMemTotal() {
    FILE *meminfo_file = fopen("/proc/meminfo", "r");
    if (meminfo_file == NULL) {
        perror("Error al abrir el archivo /proc/meminfo");
        exit(1);
    }

    char line[100];
    while (fgets(line, sizeof(line), meminfo_file)) {
        if (strstr(line, "MemTotal:") != NULL) {
            printf("Memoria Física Total del Sistema: %s", line);
            break;
        }
    }

    fclose(meminfo_file);
}

int main() {
    DIR *dir;
    struct dirent *entry;

    // Abre el directorio /proc
    dir = opendir("/proc");
    if (dir == NULL) {
        perror("Error al abrir el directorio /proc");
        exit(1);
    }

    // Muestra la memoria física total del sistema
    mostrarMemTotal();

    // Itera sobre cada entrada en el directorio /proc
    while ((entry = readdir(dir))) {
        if (isdigit(entry->d_name[0])) {
            int pid = atoi(entry->d_name);
            char status_path[100];
            char name[100];
            FILE *status_file;

            // Construye la ruta al archivo "status" del proceso
            snprintf(status_path, sizeof(status_path), "/proc/%d/status", pid);

            // Abre el archivo "status" para leer el nombre del proceso
            status_file = fopen(status_path, "r");
            if (status_file == NULL) {
                continue;
            }

            // Lee el nombre del proceso
            while (fgets(name, sizeof(name), status_file)) {
                if (strstr(name, "Name:") != NULL) {
                    name[strlen(name) - 1] = '\0';
                    break;
                }
            }
            fclose(status_file);

            // Determina si es un proceso de kernel o de usuario
            if (pid > 0 && pid < 999) {
                printf("ID de proceso: %d (Proceso de Kernel)\n", pid);
            } else {
                printf("ID de proceso: %d (Proceso de Usuario)\n", pid);
            }
            printf("Nombre proceso: %s\n\n", name);
        }
    }

    // Cierra el directorio
    closedir(dir);

    return 0;
}
