#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>

void read_file(char *, char *);

int main() {
  DIR *procptr;
  struct dirent *entry;
  int num_procs = 0;
  char filename[255];
  char procname[2048];
  int pID;
  char processName[2048];
  char state;
  char NA[300];

  procptr = opendir("/proc");
  if ( procptr == NULL ) {
    printf("No pude abrir el directorio /proc");
    exit(1);
  }

  while( (entry=readdir(procptr)) ) {
        num_procs++;
        printf("Process %s: ", entry->d_name);
        if ( ! isdigit(entry->d_name[0]) )
          continue;

        sprintf(filename, "/proc/%s/cmdline", entry->d_name);
        read_file(filename, procname);

        if( procname[0] != NULL ){
          printf("%s\n", procname);
          printf("Proceso de Usuario\n");
        }
        else
          printf("Proceso de kernel\n");

        sprintf(filename, "/proc/%s/stat", entry->d_name);
        read_file(filename, procname);
        printf("STAT: %s", procname);
        sscanf(procname, "%d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld",
            &pID, &processName, &state, &NA, &NA, &NA, &NA, &NA, &NA, &NA,
            &NA, &NA, &NA, &NA, &NA, &NA, &NA, &NA, &NA);
        printf("PID: %d\n", pID);
        printf("Process Name: %s\n", processName);
        printf("Process Status: %c\n", state);
        printf("----------------------------------\n");
			

  }

  printf("\nTotal de procesos: %d\n", num_procs);

  closedir(procptr);
}


void read_file(char *filename, char *procname) {
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  procname[0] = NULL;

  // Open file in read-only mode
  fp = fopen(filename,"r");

  // If file opened successfully, then print the contents
  if ( fp == NULL ) {
    printf("Error abriendo archivo %s\n", filename);
    exit(2);
   }

  while(getline(&line, &len, fp) != -1) {
    sprintf(procname, "%s%s", procname, line);
  }

  fclose(fp);
  free(line);
}