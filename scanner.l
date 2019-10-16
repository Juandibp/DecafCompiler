%option noyywrap
%option yylineno
%{
	
	#include "parser.tab.h"
	#include <string.h>
	#include <stdlib.h>
	int lineno = 0;
	char * translateString(char *, int);
%}


CHAR (\.|[^\"])

espacio [ \r\t\v\f]
saltoLinea \n


%%
	/* Operadores  */
"+"                              {
                                  return (plus);
                                }
"-"                              {
                                  return (minus);
                                }
"*"                              {
                                  return (mult);
                                }
"/"                            {
                                  return (token_div);
                                }
"%"                              {
                                  return (mod);
                                }

"<"                              {
                                  return (menor);
                                }
"<="                              {
                                  return (menorEql);
                                }
">"                              {
                                  return (mayor);
                                }
">="                              {
                                  return (mayorEql);
                                }
"="                              {
                                  return (eql);
                                }								
"=="                              {
                                  return (eqlEql);
                                }
"!="                              {
                                  return (nEql);
                                }
								
								
 /* conditional operators  */
"&&"                            {
                                  //printf("and\n");
                                  return (token_and);
                                }
"||"                            {
                                  //printf("or\n");
                                  return (token_or);
                                }
								
 /*Parentesis*/
 
"("                              {printf("Lex: (\n");
                                  return (opar);
                                }
")"                              {printf("Lex: )\n");
                                  return (cpar);
                                }
"{"                              {printf("Lex: {\n");
                                  return (ocur);
                                }
"}"                              {printf("Lex: }\n");
                                  return (ccur);
                                }								
"["                              {
                                  return (osqu);
                                }
"]"                              {
                                  return (csqu);
                                }

 /*Palabras Reservadas*/
void							{printf("Lex: void\n");return (token_void); }

int								{return (Type_int); }

double							{return (Type_double); }

bool							{return (Type_bool); }

string                          {return (Type_string); }

class                         	{printf("Lex: class\n");return (token_class); }

interface                       {return (token_interface); }

null                         	{return (null); }

this                         	{return (token_this); }

extends                         {return (token_extends); }		

implements                         	{return (token_implements); }	

for                         	{return (token_for); }	

while                         	{return (token_while); }

if                         		{return (token_if); }		

else                         		{return (token_else); }	

return                         		{return (token_return); }	

break                         		{return (token_break); }	

New                         		{return (token_new); }	

NewArray						{return (token_newArray); }	

Print							{printf("Lex: print\n");return (print); }	

ReadInteger							{return (readInteger); }

ReadLine							{return (readLine); }

true                            { return (boolConstant); }
false                           { return (boolConstant); }


	/* Numbers, Strings and Others */
	

0x[0-9a-fA-F][0-9a-fA-F]*       { //printf("hex\n");
                                    return (intConstant); }
[0-9]+                          { //printf("decimal\n");
                                    yylval.ival = atoi(yytext); return (intConstant); }
\"{CHAR}*\"                     { printf("string\n");
                                  yylval.sval = translateString(yytext + 1, strlen(yytext) - 2); return (stringConstant);}
[a-zA-Z_][a-zA-Z0-9_]*          {  printf("Lex: ident\n");
								   yylval.sval = strdup(yytext);
								  return (ident); }

  /* Special Characters */
!                               { return (token_not); }
;                               {printf("Lex: ;\n");   return (scolon); }
,                               {  return (comma); }
\t
\n                              {lineno++;}
" "
.				                {printf("Error here\n");}

  /* Comment Line */
\/\/(.*)"\n"





					
	
%%

char * translateString(char * string, int size) {
    char * ch = string;
    char * newString = (char *) malloc(size + 1);
    char * temp = newString;
    int i;
    for (i = 0; i < size; i++) {
        switch (*ch) {
            case '\\':
                i++;
                ch++;
                switch (*ch) {
                    case 'a':
                        *temp = '\a';
                        break;
                    case 'b':
                        *temp = '\b';
                        break;
                    case 'f':
                        *temp = '\f';
                        break;
                    case 'n':
                        *temp = '\n';
                        break;
                    case 'r':
                        *temp = '\r';
                        break;
                    case 't':
                        *temp = '\t';
                        break;
                    case 'v':
                        *temp = '\v';
                        break;
                    case '\\':
                        *temp = '\\';
                        break;
                    case '\'':
                        *temp = '\'';
                        break;
                    case '\"':
                        *temp = '\"';
                        break;
                    case '?':
                        *temp = '\?';
                        break;
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                        // TODO: Fill
                        break;
                    case 'x':
                        // TODO: Fill
                        break;
                    default:
                        break;
                }
                break;
            default:
                *temp = *ch;
                break;
        }
        ch++;
        temp++;
    }
    *temp = '\0';
    return newString;
}