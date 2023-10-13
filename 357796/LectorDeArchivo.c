#include <stdio.h>
int main(int argc, char *argv[]) {
  	FILE *Archivo;
  	char *NombreArchivo, Caracteres[200];
  	NombreArchivo=argv[1];
  	Archivo=fopen(NombreArchivo,"r");
	  if (Archivo==NULL){
	    printf("El Archivo no existe\n");
	    return 1;
   	}
	  while(fgets(Caracteres,200,Archivo)!=NULL){
		  printf("%s",Caracteres);
	  }
	return 0;
}
