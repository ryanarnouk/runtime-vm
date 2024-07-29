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
    // yylval.identifier = strdup(yytext);
    return IDENTIFIER;
}
[0-9]+         {
    printf("Token: INTEGER (%s)\n", yytext);
    // yylval.integer = atoi(yytext);
    return INTEGER;
};
[ \t\n]+       /* ignore whitespace */;
.              {
    printf("Unknown character: %s\n", yytext);
    return yytext[0];
}
%%

int yywrap() {
    return 1;
}
