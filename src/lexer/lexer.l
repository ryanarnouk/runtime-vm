/* lexer.l */
%{
#include "../parse/parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
%}

%%
"class"        return CLASS;
"{"            return LBRACE;
"}"            return RBRACE;
";"            return SEMICOLON;
"="            return ASSIGN;
"function"     return FUNCTION;
"return"       return RETURN;
"if"           return IF;
"else"         return ELSE;
"while"        return WHILE;
"("            return LPAREN;
")"            return RPAREN;
","            return COMMA;
"var"          return VAR; // variables only support integers for now until type inference is completed
"init"         return CONSTRUCTOR;
"print"        return PRINT;
[a-zA-Z_][a-zA-Z0-9_]*  {
    yylval.identifier = strdup(yytext);
    return IDENTIFIER;
}
[0-9]+         {
    yylval.integer = atoi(yytext);
    return INTEGER;
};
[ \t\r\n]+       /* ignore whitespace */;
.              {
    printf("Unknown character: %s\n", yytext);
    return yytext[0];
}
%%

int yywrap() {
    return 1;
}
