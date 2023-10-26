#include <stdio.h>

int main(int argc, char*argv[])
{
    char *input;
    char ch[100];
    FILE *fh;
    input = argv[1];
    fh = fopen(input, "r");

    if (fh != NULL){
        
       while (fgets(ch, sizeof(ch), fh) != NULL){
        printf("%s", ch);
       }
    }else{
        printf("Error opening the file\n");
    }
    
    return 0;
}
