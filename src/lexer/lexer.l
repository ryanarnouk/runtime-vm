/* lexer.l */
%{
#include "../parse/parser.tab.h"
%}

%%
"class"        return CLASS;
"{"            return LBRACE;
"}"            return RBRACE;
";"            return SEMICOLON;
"="            return ASSIGN;
[a-zA-Z_][a-zA-Z0-9_]*  {
    printf("Token: IDENTIFIER (%s)\n", yytext);
    yylval.identifier = strdup(yytext);
    free(yytext);
    return IDENTIFIER;
}
[0-9]+         {
    printf("Token: INTEGER (%s)\n", yytext);
    yylval.integer = atoi(yytext);
    free(yytext);
    return INTEGER;
};
[ \t\n]+       /* ignore whitespace */;
.              {
    char* return_text = strdup(yytext);
    printf("Unknown character: %s\n", return_text);
    free(yytext);
    return return_text[0];
}
%%

int yywrap() {
    return 1;
}
