#include "include/lexer.h"
#include "include/macros.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

lexer_T* init_lexer(char* src)
{
    lexer_T* lexer = calloc(1, sizeof(struct LEXER_STRUCT));
    lexer->src = src;
    lexer->src_size = strlen(src);
    lexer->i = 0;
    lexer->c = src[lexer->i];

    return lexer;

}

//advance the lexer
void lexer_advance(lexer_T* lexer){
    if(lexer->i < lexer->src_size && lexer->c != '\0'){
        lexer->i ++;
        lexer->c = lexer->src[lexer->i];
    }
}

char lexer_peek(lexer_T* lexer, int offset){
    return lexer->src[MIN(lexer->i + offset, lexer->src_size) ];
}

token_T* lexer_advance_current(lexer_T* lexer, int type){
    char* value = calloc(2, sizeof(char));
    value[0] = lexer->c;
    value[1] = '\0';

    token_T* token = init_token(value, type);
    lexer_advance(lexer);
    return token;
}

token_T* lexer_parse_id(lexer_T* lexer){
    char* value = calloc(1, sizeof(char));
    while(isalpha(lexer->c)){
        value = realloc(value, (strlen(value) + 2) * sizeof(char));
        strcat(value, (char[]){lexer->c, 0});
        lexer_advance(lexer);
    }

    return init_token(value, TOKEN_ID);
}

token_T* lexer_parse_num(lexer_T* lexer){
    char* value = calloc(1, sizeof(char));
    while(isdigit(lexer->c)){
        value = realloc(value, (strlen(value) + 2) * sizeof(char));
        strcat(value, (char[]){lexer->c, 0});
        lexer_advance(lexer);
    }

    return init_token(value, TOKEN_INT);
}


token_T* lexer_next_token(lexer_T* lexer){
    while (lexer->c != '\0'){
        // check if series of string
        if(isalpha(lexer->c)){
            token_T* tok = lexer_parse_id(lexer);
            lexer_advance(lexer);
            return tok;
        }

        if (isdigit(lexer->c)){
            token_T* tok = lexer_parse_num(lexer);
            lexer_advance(lexer);
            return tok;
        }

        switch (lexer->c){
            case '=':
                { 
                    if (lexer_peek(lexer, 1) == '>'){
                        lexer_advance(lexer);
                        return lexer_advance_current(lexer, TOKEN_ARROW_RIGHT);
                    }
                    return lexer_advance_current(lexer, TOKEN_EQUALS);
                }
            case '(':
                return lexer_advance_current(lexer, TOKEN_LPAREN);
            case ')':
                return lexer_advance_current(lexer, TOKEN_RPAREN);
            case '{':
                return lexer_advance_current(lexer, TOKEN_LBRACE);
            case '}':
                return lexer_advance_current(lexer, TOKEN_LBRACE);
            case ':':
                return lexer_advance_current(lexer, TOKEN_COLON);
            case ',':
                return lexer_advance_current(lexer, TOKEN_COMMA);
            case '<':
                return lexer_advance_current(lexer, TOKEN_LT);
            case '>':
                return lexer_advance_current(lexer, TOKEN_GT);
            case ';':
                return lexer_advance_current(lexer, TOKEN_SEMI);
            case '\0':
                break;
            case ' ':
                lexer_advance(lexer);
                continue;
            case '\n':
                lexer_advance(lexer);
                continue;
            case '\t':
                lexer_advance(lexer);
                continue;
            default: 
                printf("[Lexer]: unexpected character `%d`\n", lexer->c);
                exit(1);
                break;
        }
    }
    return init_token(0, TOKEN_EOF);
}