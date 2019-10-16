%option noyywrap
%option yylineno
%{
	
	#include "parser.tab.h"
	#include <string.h>
	#include <stdlib.h>

	int lineno = 1;
	char * translateString(char *, int);
  void printScannerTable(int,const char*,const char*);
%}


CHAR (\.|[^\"])

espacio [ \r\t\v\f]
saltoLinea \n


%%
	/* Operadores  */
"+"                              {
                                  printScannerTable(lineno,"plus","+");
                                  return (plus);
                                }
"-"                              {
                                  printScannerTable(lineno,"minus","-");
                                  return (minus);
                                }
"*"                              {
                                  printScannerTable(lineno,"mult","*");
                                  return (mult);
                                }
"/"                            {
                                  printScannerTable(lineno,"token_div","/");
                                  return (token_div);
                                }
"%"                              {
                                  printScannerTable(lineno,"mod","%");
                                  return (mod);
                                }

"<"                              {
                                  printScannerTable(lineno,"menor","<");
                                  return (menor);
                                }
"<="                              {
                                  printScannerTable(lineno,"menorEql","<=");
                                  return (menorEql);
                                }
">"                              {
                                  printScannerTable(lineno,"mayor",">");
                                  return (mayor);
                                }
">="                              {
                                  printScannerTable(lineno,"mayorEql",">=");
                                  return (mayorEql);
                                }
"="                              {
                                  printScannerTable(lineno,"eql","=");
                                  return (eql);
                                }								
"=="                              {
                                  printScannerTable(lineno,"eqlEql","==");
                                  return (eqlEql);
                                }
"!="                              {
                                  printScannerTable(lineno,"nEql","!=");
                                  return (nEql);
                                }
								
								
 /* conditional operators  */
"&&"                            {
                                  printScannerTable(lineno,"token_and","&&");
                                  return (token_and);
                                }
"||"                            {
                                  printScannerTable(lineno,"token_or","||");
                                  return (token_or);
                                }
								
 /*Parentesis*/
 
"("                              {printScannerTable(lineno,"opar","(");
                                  return (opar);
                                }
")"                              {printScannerTable(lineno,"cpar",")");
                                  return (cpar);
                                }
"{"                              {printScannerTable(lineno,"ocur","{");
                                  return (ocur);
                                }
"}"                              {printScannerTable(lineno,"ccur","}");
                                  return (ccur);
                                }								
"["                              {
                                  printScannerTable(lineno,"osqu","[");
                                  return (osqu);
                                }
"]"                              {
                                  printScannerTable(lineno,"csqu","]");
                                  return (csqu);
                                }

 /*Palabras Reservadas*/
void							{printScannerTable(lineno,"void","");return (token_void); }

int								{printScannerTable(lineno,"Type_int","");return (Type_int); }

double							{printScannerTable(lineno,"Type_double",""); return (Type_double); }

bool							{printScannerTable(lineno,"Type_bool",""); return (Type_bool); }

string                          {printScannerTable(lineno,"Type_string",""); return (Type_string); }

class                         	{printScannerTable(lineno,"token_class",""); return (token_class); }

interface                       {printScannerTable(lineno,"token_interface",""); return (token_interface); }

null                         	{printScannerTable(lineno,"null",""); return (null); }

this                         	{printScannerTable(lineno,"token_this",""); return (token_this); }

extends                         {printScannerTable(lineno,"token_extends",""); return (token_extends); }		

implements                         	{printScannerTable(lineno,"token_implements",""); return (token_implements); }	

for                         	{printScannerTable(lineno,"token_for",""); return (token_for); }	

while                         	{printScannerTable(lineno,"token_while",""); return (token_while); }

if                         		{printScannerTable(lineno,"token_if",""); return (token_if); }		

else                         		{printScannerTable(lineno,"token_else",""); return (token_else); }	

return                         		{printScannerTable(lineno,"token_return",""); return (token_return); }	

break                         		{printScannerTable(lineno,"token_break",""); return (token_break); }	

New                         		{printScannerTable(lineno,"token_new",""); return (token_new); }	

NewArray						{printScannerTable(lineno,"token_newArray",""); return (token_newArray); }	

Print							{printScannerTable(lineno,"print","");return (print); }	

ReadInteger							{printScannerTable(lineno,"readInteger",""); return (readInteger); }

ReadLine							{printScannerTable(lineno,"readLine",""); return (readLine); }

true                            {printScannerTable(lineno,"boolConstant","true");  return (boolConstant); }
false                           {printScannerTable(lineno,"boolConstant","false");  return (boolConstant); }


	/* Numbers, Strings and Others */
	

0x[0-9a-fA-F][0-9a-fA-F]*       { 
                                    printScannerTable(lineno,"hex",yytext);

                                    return (intConstant); }
[0-9]+                          { printScannerTable(lineno,"decimal",yytext);
                                    yylval.ival = atoi(yytext); return (intConstant); }
\"{CHAR}*\"                     { printScannerTable(lineno,"string",yytext);
                                  yylval.sval = translateString(yytext + 1, strlen(yytext) - 2); return (stringConstant);}
[a-zA-Z_][a-zA-Z0-9_]*          {  printScannerTable(lineno,"id\t",yytext);
								   yylval.sval = strdup(yytext);
								  return (ident); }

  /* Special Characters */
!                               {printScannerTable(lineno,"token_not","!"); return (token_not); }
;                               {printScannerTable(lineno,"scolon",";");   return (scolon); }
,                               {printScannerTable(lineno,"comma",",");  return (comma); }
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

void printScannerTable(int line,const char* tkn, const char* value){
  printf("Line: %d   Token: %s \t Value: %s\n", line,tkn,value);
}