#ifndef LEXER_H
#define LEXER_H


typedef struct TokenList TokenList;
typedef enum TokenType TokenType;
typedef struct Token Token;

int tokens_from_file(char* filename, char* buffer);
TokenList* lex_tokens(char* buffer);
int in_char_array(char value, char* array, int array_len);
int in_string_array(char* value, char** array, int array_len);
Token* add_token(TokenList* token_list, Token* token, TokenType type, char* value);
void print_list(TokenList* token_list);


char* KEYWORDS[] = {"int", "return"};
int KEYWORD_LEN = 2;
char CHARACTERS[] = {'{', '}', '(', ')', ';'};
int CHARACTERS_LEN = 5;
char* INTEGER_REGEX = "[0-9]+";
char* INDETIFIER_REGEX = "[a-zA-Z]\\w*";
int BUFFER_SIZE = 1048576;

enum TokenType {
  NULL_T,
  KEYWORD,
  CHARACTER,
  INTEGER,
  IDENTIFIER
};

struct Token {
  TokenType token_type;
  char* value;
  Token* next;
};

struct TokenList {
  Token* head;
  int len;
};

#endif 
