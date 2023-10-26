#include <stdio.h>

int main(int argc, Caracterar*argv[]){
    char *ArCaracterivoIngresado, Caracter[255];
    FILE *Archivo;
    
    ArCaracterivoIngresado = argv[1];
    Archivo = fopen(ArCaracterivoIngresado, "r");

    if(Archivo == NULL){
    	printf("Archivo no encontrado\n");
        return 1;
    }
    
	while(fgets(Caracter, sizeof(Caracter), Archivo) != NULL){
		printf("%s", Caracter);
    }
    return 0;
}
