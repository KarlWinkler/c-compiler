#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

int main(int args, char** argv) {
  if (args < 2) {
    printf("Usage: lexer <filename>\n");
    return 1;
  }

  char* filename = argv[1];
  char* buffer = malloc(BUFFER_SIZE); // 2^20 * sizeof(char) is 1 

  int i = tokens_from_file(filename, buffer);
  TokenList* tokens = lex_tokens(buffer);
  printf("%s\n", buffer);
  print_list(tokens);
  return i;
}

TokenList* lex_tokens(char* buffer) {
  TokenList* lexed_tokens = (TokenList *)malloc(sizeof(TokenList));
  lexed_tokens->len = 0;
  Token* current_token = NULL;

  int i = 0;
  while (buffer[i] != '\0'){
    char current_word[1024] = "\0";

    // skip whitespace
    if (buffer[i] == ' ' || buffer[i] == '\n' || buffer[i] == '\t') {
      i++;
      continue;
    }

    // process words
    if ((buffer[i] > 64 && buffer[i] < 91) || (buffer[i] > 96 && buffer[i] < 123)) {
      int j = 0;
      while ((buffer[i] > 64 && buffer[i] < 91) || (buffer[i] > 96 && buffer[i] < 123)) {
        current_word[j] = buffer[i];
        i++;
        j++;
      }
      current_word[j] = '\0';

      if (in_string_array(current_word, KEYWORDS, KEYWORD_LEN)) {
        current_token = add_token(lexed_tokens, current_token, KEYWORD, current_word);
        continue;
      } else {
        current_token = add_token(lexed_tokens, current_token, KEYWORD, current_word);
        continue;
      }
    }

    // process special characters
    if (in_char_array(buffer[i], CHARACTERS, CHARACTERS_LEN)) {
      current_word[0] = buffer[i];
      current_word[1] = '\0';
      i++;
      current_token = add_token(lexed_tokens, current_token, CHARACTER, current_word);
      continue;
    }

    // process integers
    if (buffer[i] > 47 && buffer[i] < 58) {
      int j = 0;
      while (buffer[i] > 47 && buffer[i] < 58) {
        current_word[j] = buffer[i];
        i++;
        j++;
      }
      current_word[j] = '\0';
      current_token = add_token(lexed_tokens, current_token, INTEGER, current_word);
      continue;
    }
  }

  return lexed_tokens;
}

Token* add_token(TokenList* token_list, Token* token, TokenType type, char* value) {
  Token* new_token = (Token *)malloc(sizeof(Token));
  char* new_val = malloc(sizeof(char) * strlen(value));
  strcpy(new_val, value);
  *new_token = (Token){type, new_val, NULL};

  if (token_list->head == NULL) {
    token_list->head = new_token;
  } else {
    token->next = new_token;
  }

  token_list->len++;
  // printf("%d\n", token_list->len);
  return new_token;
}

void print_list(TokenList* token_list) {
  Token* current_token = token_list->head;
  while (current_token != NULL) {
    printf("%s\n", current_token->value);
    current_token = current_token->next;
  }
}

int in_string_array(char* value, char** array, int array_len) {
  for (int i = 0; i < array_len; i++) {
    if (strcmp(array[i], value) == 0) {
      return 1;
    }
  }
  return 0;
}

int in_char_array(char value, char* array, int array_len) {
  for (int i = 0; i < array_len; i++) {
    if (array[i] == value) {
      return 1;
    }
  }
  return 0;
}

int tokens_from_file(char* filename, char* buffer) {
  FILE* file = fopen(filename, "r");

  if (file == NULL) {
    printf("File not found: %s\n", filename);
    return 1;
  }

  return fread(buffer, sizeof(char), BUFFER_SIZE, file);
}
