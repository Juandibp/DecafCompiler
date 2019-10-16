%option noyywrap
%option yylineno
%{
	
	#include "parser.tab.h"
	#include <string.h>
	#include <stdlib.h>
  #define YY_USER_ACTION yyset_column(yyget_column(yyscanner) + yyget_leng(yyscanner), yyscanner);
	int lineno = 0;
	char * translateString(char *, int);
%}


CHAR (\.|[^\"])

espacio [ \r\t\v\f]
saltoLinea \n


%%
	/* Operadores  */
"+"                              {
                                  printScannerTable("plus",yyget_column(yyscanner),"+");
                                  return (plus);
                                }
"-"                              {
                                  printScannerTable("minus",yyget_column(yyscanner),"-");
                                  return (minus);
                                }
"*"                              {
                                  printScannerTable("mult",yyget_column(yyscanner),"*");
                                  return (mult);
                                }
"/"                            {
                                  printScannerTable("token_div",yyget_column(yyscanner),"/");
                                  return (token_div);
                                }
"%"                              {
                                  printScannerTable("mod",yyget_column(yyscanner),"%");
                                  return (mod);
                                }

"<"                              {
                                  printScannerTable("menor",yyget_column(yyscanner),"<");
                                  return (menor);
                                }
"<="                              {
                                  printScannerTable("menorEql",yyget_column(yyscanner),"<=");
                                  return (menorEql);
                                }
">"                              {
                                  printScannerTable("mayor",yyget_column(yyscanner),">");
                                  return (mayor);
                                }
">="                              {
                                  printScannerTable("mayorEql",yyget_column(yyscanner),">=");
                                  return (mayorEql);
                                }
"="                              {
                                  printScannerTable("eql",yyget_column(yyscanner),"=");
                                  return (eql);
                                }								
"=="                              {
                                  printScannerTable("eqlEql",yyget_column(yyscanner),"==");
                                  return (eqlEql);
                                }
"!="                              {
                                  printScannerTable("nEql",yyget_column(yyscanner),"!=");
                                  return (nEql);
                                }
								
								
 /* conditional operators  */
"&&"                            {
                                  printScannerTable("token_and",yyget_column(yyscanner),"&&");
                                  return (token_and);
                                }
"||"                            {
                                  printScannerTable("token_or",yyget_column(yyscanner),"||");
                                  return (token_or);
                                }
								
 /*Parentesis*/
 
"("                              {printScannerTable("opar",yyget_column(yyscanner),"(");
                                  return (opar);
                                }
")"                              {printScannerTable("cpar",yyget_column(yyscanner),")");
                                  return (cpar);
                                }
"{"                              {printScannerTable("ocur",yyget_column(yyscanner),"{");
                                  return (ocur);
                                }
"}"                              {printScannerTable("ccur",yyget_column(yyscanner),"}");
                                  return (ccur);
                                }								
"["                              {
                                  printScannerTable("osqu",yyget_column(yyscanner),"[");
                                  return (osqu);
                                }
"]"                              {
                                  printScannerTable("csqu",yyget_column(yyscanner),"]");
                                  return (csqu);
                                }

 /*Palabras Reservadas*/
void							{printScannerTable("void",yyget_column(yyscanner),"");return (token_void); }

int								{printScannerTable("Type_int",yyget_column(yyscanner),"");return (Type_int); }

double							{printScannerTable("Type_double",yyget_column(yyscanner),""); return (Type_double); }

bool							{printScannerTable("Type_bool",yyget_column(yyscanner),""); return (Type_bool); }

string                          {printScannerTable("Type_string",yyget_column(yyscanner),""); return (Type_string); }

class                         	{printScannerTable("token_class",yyget_column(yyscanner),""); return (token_class); }

interface                       {printScannerTable("token_interface",yyget_column(yyscanner),""); return (token_interface); }

null                         	{printScannerTable("null",yyget_column(yyscanner),""); return (null); }

this                         	{printScannerTable("token_this",yyget_column(yyscanner),""); return (token_this); }

extends                         {printScannerTable("token_extends",yyget_column(yyscanner),""); return (token_extends); }		

implements                         	{printScannerTable("token_implements",yyget_column(yyscanner),""); return (token_implements); }	

for                         	{printScannerTable("token_for",yyget_column(yyscanner),""); return (token_for); }	

while                         	{printScannerTable("token_while",yyget_column(yyscanner),""); return (token_while); }

if                         		{printScannerTable("token_if",yyget_column(yyscanner),""); return (token_if); }		

else                         		{printScannerTable("token_else",yyget_column(yyscanner),""); return (token_else); }	

return                         		{printScannerTable("token_return",yyget_column(yyscanner),""); return (token_return); }	

break                         		{printScannerTable("token_break",yyget_column(yyscanner),""); return (token_break); }	

New                         		{printScannerTable("token_new",yyget_column(yyscanner),""); return (token_new); }	

NewArray						{printScannerTable("token_newArray",yyget_column(yyscanner),""); return (token_newArray); }	

Print							{printScannerTable("print",yyget_column(yyscanner),"");return (print); }	

ReadInteger							{printScannerTable("readInteger",yyget_column(yyscanner),""); return (readInteger); }

ReadLine							{printScannerTable("readLine",yyget_column(yyscanner),""); return (readLine); }

true                            {printScannerTable("boolConstant",yyget_column(yyscanner),"true");  return (boolConstant); }
false                           {printScannerTable("boolConstant",yyget_column(yyscanner),"false");  return (boolConstant); }


	/* Numbers, Strings and Others */
	

0x[0-9a-fA-F][0-9a-fA-F]*       { 
                                    printScannerTable("hex",yyget_column(yyscanner),yytext);

                                    return (intConstant); }
[0-9]+                          { printScannerTable("decimal",yyget_column(yyscanner),yytext);
                                    yylval.ival = atoi(yytext); return (intConstant); }
\"{CHAR}*\"                     { printScannerTable("string",yyget_column(yyscanner),yytext);
                                  yylval.sval = translateString(yytext + 1, strlen(yytext) - 2); return (stringConstant);}
[a-zA-Z_][a-zA-Z0-9_]*          {  printScannerTable("id",yyget_column(yyscanner),yytext);
								   yylval.sval = strdup(yytext);
								  return (ident); }

  /* Special Characters */
!                               {printScannerTable("token_not",yyget_column(yyscanner),"!"); return (token_not); }
;                               {printScannerTable("scolon",yyget_column(yyscanner),";");   return (scolon); }
,                               {printScannerTable("comma",yyget_column(yyscanner),",");  return (comma); }
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

int printScannerTable(string tkn,int colno, string value){
  printf("Line: %s \t, Column: %d \t, Token: %s \t Value: %s\n", lineno,colno,tkn,value);
  return 0;
}