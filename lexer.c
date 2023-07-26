#include <stdio.h>
#include <string.h>

int tokens_from_file(char* filename, char** tokens);

int main(int args, char** argv) {
  if (args < 2) {
    printf("Usage: lexer <filename>\n");
    return 1;
  }

  char* filename = argv[1];
  char** tokens;
  int i = tokens_from_file(filename, tokens);

  for(int j = 0; j < i; j++) {
    printf("%s", tokens[j]);
  }
}

int tokens_from_file(char* filename, char** tokens) {
  FILE* file = fopen(filename, "r");

  if (file == NULL) {
    printf("File not found: %s\n", filename);
    return 1;
  }

  char word[50];

  // fgets(word, 50, file);
  // printf("%s", word);

  int i = 0;
  while(fscanf(file, "%50s", word) != EOF) {
    strcpy(tokens[i], word);
    i++;
  }

  return i;
}