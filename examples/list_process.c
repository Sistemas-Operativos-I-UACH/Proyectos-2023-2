#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <ctype.h>

void read_file(char *);

int main() {
  DIR *procptr;
  struct dirent *entry;
	int num_procs = 0;
	char filename[255];

  procptr = opendir("/proc");
  if ( procptr == NULL ) {
    printf("No pude abrir el directorio /proc");
    exit(1);
  }

	while( (entry=readdir(procptr)) ) {
        num_procs++;
        printf("Process: %s\n", entry->d_name);
				if ( ! isdigit(entry->d_name[0]) )
					continue;
				sprintf(filename, "/proc/%s/cmdline", entry->d_name);

    		read_file(filename);
  }

	printf("\nTotal de procesos: %d\n", num_procs);

  closedir(procptr);
}


void read_file(char *filename) {
  FILE *fp;
	char *line = NULL;
  size_t len = 0;

  // Open file in read-only mode
  fp = fopen(filename,"r");

  // If file opened successfully, then print the contents
  if ( fp == NULL ) {
    printf("Error abriendo archivo %s\n", filename);
    exit(2);
   }

	while(getline(&line, &len, fp) != -1) {
		printf("%s\n", line);
	}

	fclose(fp);
	free(line);
}
