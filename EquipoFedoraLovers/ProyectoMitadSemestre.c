/*
    Proyecto de Mitad de Semestre
    Equipo FedoraLovers:
        -Kevin Gabriel Balderrama Nevarez...361247
        -Daniel Grado Rubio.................361430
        -José Miguel Romanos Mora...........341970
        -Oscar Alberto Sanchez Molina.......357271
*/
#include <stdio.h>
#include <dirent.h>
#include <string.h>

long ObtenerMemoriaTotal() {
    FILE *meminfo = fopen("/proc/meminfo", "r");
    if (meminfo == NULL) {
        fprintf(stderr, "No se pudo abrir /proc/meminfo\n");
        return -1; 
    }

    char linea[100];
    long memoria_total = -1;

    while (fgets(linea, sizeof(linea), meminfo) != NULL) {
        if (strncmp(linea, "MemTotal:", 9) == 0) {
            sscanf(linea, "MemTotal: %ld", &memoria_total);
            break;
        }
    }

    fclose(meminfo);
    return memoria_total;
}


int ObtenerNombrePrograma(const char *pid, char *nombre, size_t tamano) {
    char archivo[100];
    sprintf(archivo, "/proc/%s/cmdline", pid);

    FILE *cmdline = fopen(archivo, "r");
    if (cmdline) {
        if (fgets(nombre, tamano, cmdline)) {
            fclose(cmdline);
            return 1; 
        }
        fclose(cmdline);
    }
    return 0; 
}

void ListarProcesos() {
    DIR *dir;
    struct dirent *ent;
    dir = opendir("/proc");

    if (dir != NULL) {
        printf("ID de proceso | Nombre proceso | Tipo\n");
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_DIR) {
                char *nombre = ent->d_name;
                if (strspn(nombre, "0123456789") == strlen(nombre)) {
                    char nombrePrograma[100];
                    int tieneNombre = ObtenerNombrePrograma(nombre, nombrePrograma, sizeof(nombrePrograma));
                    const char *Tipo = tieneNombre ? "Usuario" : "Kernel";
                    printf("%s | %s | %s\n", nombre, tieneNombre ? nombrePrograma : "N/A", Tipo);
                }
            }
        }
        closedir(dir);
    } else {
        fprintf(stderr, "No se pudo abrir el directorio /proc");
    }
    long memoria_total = ObtenerMemoriaTotal();
    if (memoria_total != -1) {
        printf("\nMemoria Total: %ld kB\n", memoria_total);
    }
}

int main() {
    ListarProcesos();
    return 0;
}
