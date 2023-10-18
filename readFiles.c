#include <stdio.h>

int main(){
    char *input;
    printf("Ingresa el nombre del archivo que quieres leer: ");
    scanf("%s",input);
    FILE *fh;
    char ch[100];
    fh = fopen(input, "r");

    if (fh != NULL)
    {
        while(fgets(ch, sizeof(ch), fh) != NULL){
            printf("%s", ch);
        }
    }else{
        printf("Error opening the file\n");
    }
    return 0;
}
