#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <ctype.h>

FILE *fp;

#define MAXBUFLEN 1000000 
unsigned char buf[MAXBUFLEN]; 
int buflen=0;

void read_file(char *);
void readCMDLine(char *filename);
void prueba(char *filename);

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
    printf("PID: %s\n", entry->d_name);
    if ( ! isdigit(entry->d_name[0]) ){
        printf("Es un proceso de kernel\n");
        continue;
    }
    sprintf(filename, "/proc/%s/cmdline", entry->d_name);

    read_file(filename);
    readCMDLine(filename);
    //prueba(filename);
    printf("\n");
        
  }

  printf("\nTotal de procesos: %d\n", num_procs);

  closedir(procptr);
}

void read_file(char *filename) {
  FILE *fp;
  char *line = NULL;
  size_t len = 0;


  fp = fopen(filename,"r");

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

void readCMDLine(char *filename){
    char cMDLinePath[100];
    char cMDLineBuffer[900];
    FILE * cMDLineFile;
    size_t bytes;
    snprintf(cMDLinePath, sizeof(cMDLinePath), filename, getpid());

    cMDLineFile = fopen(cMDLinePath, "r");

    if (cMDLineFile == NULL){
        printf("Error al abrir el archivo\n");
        exit(1);
    }

    bytes = fread(cMDLineBuffer, 1, sizeof(cMDLineBuffer), cMDLineFile);
  
    if (bytes > 0){
        printf("cmdline: %s\n", cMDLineBuffer);
    } else {
        printf("cmdline vacia\n");
    }

}


void prueba(char *filename){ 
   int i=0;
	 buflen=0;
	 fp = fopen(filename, "rb"); 
   if(fp!=NULL) { 
    while(!feof(fp)) { 
      buflen = fread(buf, 1, MAXBUFLEN, fp); 
      } fclose(fp); }


	 if(buflen>1) {	
	 	for(i=0;i<buflen;i++) { 
      printf("%02x ", buf[i]); 
      if(i%8==0) { 
        printf(" "); 
      } 
      if(i%16==0) { 
        printf("\n"); 
      } 
    } 
    printf("\n");
  }
}