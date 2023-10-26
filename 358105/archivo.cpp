#include<stdio.h>

int main()
{
  FILE *archivo;
  char c;
  archivo = fopen("/home/enriquebatista21/lista.txt","r");

  if(archivo==NULL)
  {
	printf("NO se pudo abrir el archivo\n");
  }
  while((c=fgetc(archivo))!=EOF)
  {
	printf("%c",c);
  }

   fclose(archivo);
   return 0;

}

