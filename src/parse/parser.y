/* parser.y */
%{
#include <stdio.h>
#include <stdlib.h>
#include "../bytecode.h"

void yyerror(const char *s);
int yylex(void);

extern FILE *yyin;
IRNode *root = NULL;
%}

%union {
    char *identifier;
    int integer;
    struct IRNode *node;
}

%token <identifier> IDENTIFIER
%token <integer> INTEGER
%token CLASS FUNCTION RETURN IF ELSE WHILE
%token LBRACE RBRACE LPAREN RPAREN COMMA SEMICOLON ASSIGN
%token CONSTRUCTOR VAR PRINT

%type <node> program class_declaration class_body declaration constructor code_block statement
%type <node> expression class_member_list class_member

%%
program:
    class_declaration { root = $1; }
    ;
class_declaration:
    CLASS IDENTIFIER LBRACE class_body RBRACE SEMICOLON
    {
        $$ = create_class_node($2, $4);
    }
    ;
class_body:
    class_member_list { $$ = $1; }
    ;
class_member_list:
    /* Empty */ { $$ = NULL }
    | class_member_list class_member
    {
        // $$ = append_node($1, $2);
    }
    ;
class_member:
    declaration { $$ = $1; }
    | constructor { $$ = $1; }
    ;
declaration:
    VAR IDENTIFIER SEMICOLON
    {
        IRNode *node = create_identifier_node($2);
        $$ = create_var_decl_node(node);
    }
    | FUNCTION IDENTIFIER LPAREN RPAREN LBRACE RBRACE {
        // does not support arguments yet
        // stub
    }
    ;
constructor:
    CONSTRUCTOR LPAREN RPAREN LBRACE code_block RBRACE
    {
        $$ = create_constructor_node(NULL, $5);
    }
    ;
// method_definition:
//     FUNCTION IDENTIFIER LPAREN RPAREN LBRACE RBRACE
//     {
//         printf("There is a function definitoin");
//     }
//     ;
code_block:
    /* Empty */ { $$ = NULL }
    | code_block statement {
        // A code block is a collection of statements
        // $$ = append_node($1, $2);
    }
    ;
statement:
    RETURN expression SEMICOLON
    {
        // stub
    }
    | IF LPAREN expression RPAREN statement
    {
        // stub
    }
    | WHILE LPAREN expression RPAREN statement
    {
        // stub
    }
    | expression { $$ = $1 }
    | PRINT LPAREN IDENTIFIER RPAREN SEMICOLON
    {
        // TODO: add direct string support in the future
        // add support for any identifier for the first token, not just "print"
        // to support all methods once the method reference table is implemented
        $$ = create_method_call_node("print", create_identifier_node($3));
    }
    ;
expression:
    IDENTIFIER ASSIGN INTEGER SEMICOLON
    {
        IRNode *left = create_identifier_node($1);
        IRNode *right = create_integer_node($3);
        $$ = create_assignment_node(left, right);
    }
    |
    IDENTIFIER
    {
        // stub
    }
    ;
// Currently not being used
// identifier_list:
//     /* Empty */
//     {
//         $$ = NULL;
//     }
//     | identifier_list IDENTIFIER SEMICOLON
//     {
//         printf("Identifier name: %s \n", $2);
//     }
//     ;
%%

void yyerror(const char *s) {
    // extern int yylineno;
    extern char *yytext;
    // fprintf(stderr, "Error: %s at line %d near '%s'\n", s, yylineno, yytext);
    fprintf(stderr, "Error: %s near '%s' \n", s, yytext);
}
