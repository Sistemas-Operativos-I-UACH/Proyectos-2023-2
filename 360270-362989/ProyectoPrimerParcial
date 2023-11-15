#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int main() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir("/proc");
    if (dir == NULL) {
        perror("Error al abrir el directorio /proc");
        exit(1);
    }

    while ((entry = readdir(dir))) {
        if (isdigit(entry->d_name[0])) {
            int pid = atoi(entry->d_name);
            char status_path[100];
            char name[100];
            FILE *status_file;

            snprintf(status_path, sizeof(status_path), "/proc/%d/status", pid);

            status_file = fopen(status_path, "r");
            if (status_file == NULL) {
                continue;
            }

            while (fgets(name, sizeof(name), status_file)) {
                if (strstr(name, "Name:") != NULL) {
                    name[strlen(name) - 1] = '\0';
                    break;
                }
            }
            fclose(status_file);

            if (pid > 0 && pid < 999) {
                printf("ID de proceso: %d (Proceso de Kernel)\n", pid);
            } else {
                printf("ID de proceso: %d (Proceso de Usuario)\n", pid);
            }
            printf("Nombre proceso: %s\n\n", name);
        }
    }

    closedir(dir);

    return 0;
}
