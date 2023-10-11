/***************************************************
 * Reads a file from a command line argument       *
 * Iván Chavero <ichavero@chavero.com.mx>          *
 ***************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *fp;
  char *filename;
  char ch;

  // Check if a filename has been specified in the command
  if (argc < 2) {
   printf("Missing Filename\n");
   exit(1);
  }

  filename = argv[1];
  printf("Filename : %s\n", filename);

  // Open file in read-only mode
  fp = fopen(filename,"r");

  // If file opened successfully, then print the contents
  if ( fp == NULL ) {
    printf("Failed to open the file\n");
    exit(2);
   }

  printf("File contents:\n");
  while ( (ch = fgetc(fp)) != EOF ) {
    printf("%c",ch);
  }

  exit(0);
}

