//Lexer forms the first phase of a compiler front end in modern processing.
#ifndef CAT_LEXER_H
#define CAT_LEXER_H
#include "token.h"
#include <stdio.h>

typedef struct LEXER_STRUCT{
    char* src;
    size_t src_size;
    char c;
    unsigned int i;
}lexer_T;

lexer_T* init_lexer(char* src);

char lexer_peek(lexer_T* lexer, int offset);

void lexer_skip_whitespace(lexer_T* lexer);

void lexer_advance(lexer_T* lexer);

token_T* lexer_parse_id(lexer_T* lexer);

token_T* lexer_parse_num(lexer_T* lexer);

token_T* lexer_advance_with(lexer_T* lexer, token_T* token);

token_T* lexer_advance_current(lexer_T* lexer, int type);

token_T* lexer_next_token(lexer_T* lexer);
#endif