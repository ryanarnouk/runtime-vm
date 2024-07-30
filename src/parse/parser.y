/* parser.y */
%{
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

void yyerror(const char *s);
int yylex(void);

extern FILE *yyin;
Node *root = NULL;
%}

%union {
    char *identifier;
    int integer;
    struct Node *node;
}

%token <identifier> IDENTIFIER
%token <integer> INTEGER
%token CLASS LBRACE RBRACE SEMICOLON ASSIGN

%type <node> class_decl identifier_list

%%
program:
    class_decl { root = $1; }
    ;

class_decl:
    CLASS IDENTIFIER LBRACE identifier_list RBRACE SEMICOLON
    {
        $$ = malloc(sizeof(Node));
        $$->type = CLASS_NODE;
        $$->data.class.name = $2;
        $$->data.class.body = $4;
        $$->next = NULL;
    }
    ;

identifier_list:
    /* Empty */
    {
        $$ = NULL;
    }
    | identifier_list IDENTIFIER SEMICOLON
    {
        Node* newNode = malloc(sizeof(Node));
        newNode->type = IDENTIFIER_NODE;
        newNode->data.identifier = $2;
        newNode->data.class.body = $$; // Append to the existing list
        newNode->next = $1;
        $$ = newNode;
    }
    ;
%%

void yyerror(const char *s) {
    extern int yylineno;
    extern char *yytext;
    fprintf(stderr, "Error: %s at line %d near '%s'\n", s, yylineno, yytext);
}
