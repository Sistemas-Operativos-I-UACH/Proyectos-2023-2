#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_PATH 4096

void statsss(pid_t pid) {
struct stat stat_info;
    char proc_path[MAX_PATH];
    sprintf(proc_path, "/proc/%d/status", pid);

    FILE *fp = fopen(proc_path, "r");
    if (fp == NULL) {
        perror("Error al abrir el archivo de estado del proceso");
        return;
    }

    char line[256];
    char name[256];
    int process_id = -1;

    while (fgets(line, sizeof(line), fp) != NULL) {
        // Buscar la línea que comienza con "Name:"
        if (sscanf(line, "Name:\t%s", name) == 1) {
            printf("Nombre del proceso: %s\n", name);
        }

        // Buscar la línea que comienza con "Pid:"
        if (sscanf(line, "Pid:\t%d", &process_id) == 1) {
            printf("ID del proceso: %d\n", process_id);
        }
    }
    
    // Obtener la información del proceso
    if (stat(proc_path, &stat_info) == 0) {
        // Verificar si el proceso está en modo kernel o usuario
        if (stat_info.st_uid == 0) {
            printf("El proceso está en modo kernel.\n");
        } else {
            printf("El proceso está en modo usuario.\n");
        }
    }
    fclose(fp);
}
void memoriaaaa(pid) {
    char proc_path[MAX_PATH];
    sprintf(proc_path, "/proc/meminfo", pid);

    FILE *fp = fopen(proc_path, "r");
    if (fp == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    char line[256];
    char name[256];
    
    fgets(line, sizeof(line), fp);
        if (sscanf(line, "MemTotal:\t%s", name) == 1) {
            printf("Total de memoria %skB\n", name);
        }
    
    fclose(fp);
}

int main() {
    DIR *dir;
    struct dirent *entry;

    // Abrir el directorio /proc
    dir = opendir("/proc");
    if (dir == NULL) {
        perror("Error al abrir el directorio /proc");
        return 1;
    }

    // Leer los directorios en /proc
    while ((entry = readdir(dir)) != NULL) {
        // Verificar si el nombre del directorio es un número (PID)
        if (entry->d_type == DT_DIR && atoi(entry->d_name) != 0) {
            pid_t pid = atoi(entry->d_name);
            statsss(pid);
        }
    }
            memoriaaaa();

    
    closedir(dir);

    return 0;
}
