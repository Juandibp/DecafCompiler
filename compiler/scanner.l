%option noyywrap
%option yylineno
%{
	
	#include "parser.tab.h"
	#include <string.h>
	#include <stdlib.h>

	int lineno = 1;
	char * translateString(char *, int);
  void printScannerTable(int,int,const char*,const char*);
  int column = 0;
   
%}


CHAR (\.|[^\"])

espacio [ \r\t\v\f]
saltoLinea \n


%%

  /* Comentarios */
\/\/(.*)"\n"
"/*"([^*]|\*+[^*/])*\*+"/"

	/* Operadores  */
"+"                              {column = column + yyleng;
                                  printScannerTable(lineno,column,"plus","+");
                                  return (plus);
                                }
"-"                              {column = column + yyleng;
                                  printScannerTable(lineno,column,"minus","-");
                                  return (minus);
                                }
"*"                              {column = column + yyleng;
                                  printScannerTable(lineno,column,"mult","*");
                                  return (mult);
                                }
"/"                            {column = column + yyleng;
                                  printScannerTable(lineno,column,"token_div","/");
                                  return (token_div);
                                }
"%"                              {column = column + yyleng;
                                  printScannerTable(lineno,column,"mod","%");
                                  return (mod);
                                }

"<"                              {column = column + yyleng;
                                  printScannerTable(lineno,column,"menor","<");
                                  return (menor);
                                }
"<="                              {column = column + yyleng;
                                  printScannerTable(lineno,column,"menorEql","<=");
                                  return (menorEql);
                                }
">"                              {column = column + yyleng;
                                  printScannerTable(lineno,column,"mayor",">");
                                  return (mayor);
                                }
">="                              {column = column + yyleng;
                                  printScannerTable(lineno,column,"mayorEql",">=");
                                  return (mayorEql);
                                }
"="                              {column = column + yyleng;
                                  printScannerTable(lineno,column,"eql","=");
                                  return (eql);
                                }								
"=="                              {column = column + yyleng;
                                  printScannerTable(lineno,column,"eqlEql","==");
                                  return (eqlEql);
                                }
"!="                              {column = column + yyleng;
                                  printScannerTable(lineno,column,"nEql","!=");
                                  return (nEql);
                                }
								
						
"&&"                            {column = column + yyleng;
                                  printScannerTable(lineno,column,"token_and","&&");
                                  return (token_and);
                                }
"||"                            {column = column + yyleng;
                                  printScannerTable(lineno,column,"token_or","||");
                                  return (token_or);
                                }
								
 /*Parentesis*/
 
"("                              {column = column + yyleng;printScannerTable(lineno,column,"opar","(");
                                  return (opar);
                                }
")"                              {column = column + yyleng;printScannerTable(lineno,column,"cpar",")");
                                  return (cpar);
                                }
"{"                              {column = column + yyleng;printScannerTable(lineno,column,"ocur","{");
                                  return (ocur);
                                }
"}"                              {column = column + yyleng;printScannerTable(lineno,column,"ccur","}");
                                  return (ccur);
                                }								
"["                              {column = column + yyleng;
                                  printScannerTable(lineno,column,"osqu","[");
                                  return (osqu);
                                }
"]"                              {column = column + yyleng;
                                  printScannerTable(lineno,column,"csqu","]");
                                  return (csqu);
                                }

 /*Palabras Reservadas*/
void							{column = column + yyleng;printScannerTable(lineno,column,"void","");return (token_void); }

int								{column = column + yyleng;printScannerTable(lineno,column,"Type_int","");return (Type_int); }

double							{column = column + yyleng;printScannerTable(lineno,column,"Type_double",""); return (Type_double); }

bool							{column = column + yyleng;printScannerTable(lineno,column,"Type_bool",""); return (Type_bool); }

string                          {column = column + yyleng;printScannerTable(lineno,column,"Type_string",""); return (Type_string); }

class                         	{column = column + yyleng;printScannerTable(lineno,column,"token_class",""); return (token_class); }

interface                       {column = column + yyleng;printScannerTable(lineno,column,"token_interface",""); return (token_interface); }

null                         	{column = column + yyleng;printScannerTable(lineno,column,"null",""); return (null); }

this                         	{column = column + yyleng;printScannerTable(lineno,column,"token_this",""); return (token_this); }

extends                         {column = column + yyleng;printScannerTable(lineno,column,"token_extends",""); return (token_extends); }		

implements                         	{column = column + yyleng;printScannerTable(lineno,column,"token_implements",""); return (token_implements); }	

for                         	{column = column + yyleng;printScannerTable(lineno,column,"token_for",""); return (token_for); }	

while                         	{column = column + yyleng;printScannerTable(lineno,column,"token_while",""); return (token_while); }

if                         		{column = column + yyleng;printScannerTable(lineno,column,"token_if",""); return (token_if); }		

else                         		{column = column + yyleng;printScannerTable(lineno,column,"token_else",""); return (token_else); }	

return                         		{column = column + yyleng;printScannerTable(lineno,column,"token_return",""); return (token_return); }	

break                         		{column = column + yyleng;printScannerTable(lineno,column,"token_break",""); return (token_break); }	

New                         		{column = column + yyleng;printScannerTable(lineno,column,"token_new",""); return (token_new); }	

NewArray						{column = column + yyleng;printScannerTable(lineno,column,"token_newArray",""); return (token_newArray); }	

Print							{column = column + yyleng;printScannerTable(lineno,column,"print","");return (print); }	

ReadInteger							{column = column + yyleng;printScannerTable(lineno,column,"readInteger",""); return (readInteger); }

ReadLine							{column = column + yyleng;printScannerTable(lineno,column,"readLine",""); return (readLine); }

true                            {column = column + yyleng;printScannerTable(lineno,column,"boolConstant","true");  return (boolConstant); }
false                           {column = column + yyleng;printScannerTable(lineno,column,"boolConstant","false");  return (boolConstant); }


	/* Variables */
	

0x[0-9a-fA-F][0-9a-fA-F]*       { column = column + yyleng;
                                    printScannerTable(lineno,column,"hex",yytext);

                                    return (intConstant); }
[0-9]+                          { column = column + yyleng;printScannerTable(lineno,column,"decimal",yytext);
                                    yylval.ival = atoi(yytext); return (intConstant); }
\"{CHAR}*\"                     {column = column + yyleng; printScannerTable(lineno,column,"string",yytext);
                                  yylval.sval = translateString(yytext + 1, strlen(yytext) - 2); return (stringConstant);}
[a-zA-Z_][a-zA-Z0-9_]*          {  column = column + yyleng;printScannerTable(lineno,column,"id\t",yytext);
								   yylval.sval = strdup(yytext);
								  return (ident); }

  /* Caracteres especiales */
!                               {column = column + yyleng;printScannerTable(lineno,column,"token_not","!"); return (token_not); }
;                               {column = column + yyleng;printScannerTable(lineno,column,"scolon",";");   return (scolon); }
,                               {column = column + yyleng;printScannerTable(lineno,column,"comma",",");  return (comma); }
\t
\n                              {lineno++; column = 0;}
" "
\"{CHAR}* 						{printf("Error in line %d and column %d unclose string",lineno,column);exit(1);}
.				                {printf("Caracter ilegal <%s> en línea %d y columna %d\n",yytext,lineno,column);exit(1);}







					
	
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
                        
                        break;
                    case 'x':
                        
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

void printScannerTable(int line,int column,const char* tkn, const char* value){
  printf("Line: %d    Column: %d    Token: %s \t Value: %s\n", line,column,tkn,value);
}