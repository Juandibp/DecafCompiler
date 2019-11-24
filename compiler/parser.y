%{
 #include "compiler/objetos.h"
 #include <math.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <iostream>
 #include <string>
 #include <vector>
 int yylex (void);
 extern int lineno;
 extern int column;
 extern union node yylval;
 void yyerror (char const *); 
%}



%union {
  int ival;
  double dval;
  char *sval ;
  
}


 
%token /*Constantes */      
		/*Operadores*/	token_plus token_minus mult	token_div mod  menor menorEql mayor mayorEql eql eqlEql nEql 
					    token_and token_or token_not scolon comma punto 
		/*Parentesis*/  /*[ ]*/osqu csqu /*( ) */ opar cpar /*{}*/ ocur ccur
		/*Palabras Reservadas*/ token_void Type_int Type_double Type_bool Type_string token_class token_interface null
								token_this token_extends token_implements token_for token_while token_if token_else
								token_return token_break token_new token_newArray print readInteger readLine
		 
	               
		           
%type <stmt> Stmt
%type <ifStmt> IfStmt
%type <whileStmt> WhileStmt
%type <forStmt> ForStmt
%type <returnStmt> ReturnStmt
%type <breakStmt> BreakStmt
%type <printStmt> PrintStmt
%type <expr> Expr
%type <lvalue> LValue
%type <call> Call
%type <actuals> Actuals
%type <constant> Constant


%token <sval> stringConstant
%token <ival> intConstant
%token <sval> ident
%token <dval> doubleConstant
%token <bval> token_true
%token <bval> token_false



%start Program

%%
Program : Decl Multi_Decl 


Multi_Decl: Decl Multi_Decl | 

Decl : VariableDecl | FunctionDecl | ClassDecl | InterfaceDecl;

VariableDecl : Variable scolon

Variable : Type ident

Type : Type_int | Type_double | Type_bool | Type_string | ident | Type osqu csqu

FunctionDecl : Type ident opar Formals cpar StmtBlock | 
				token_void ident opar Formals cpar StmtBlock

Formals : Variable Multi_Variable | 

Multi_Variable : comma Variable Multi_Variable | 



ClassDecl : token_class ident Extends Implements ocur MultiBinary_Field  ccur

MultiBinary_Field : Field MultiBinary_Field |

Extends: token_extends ident | 

Implements: token_implements Identificador |

Identificador : ident  Multi_Identificador

Multi_Identificador : comma ident Multi_Identificador |

Field : VariableDecl | FunctionDecl

InterfaceDecl: token_interface ident ocur Prototype  ccur

MultiBinary_Prototype: Prototype MultiBinary_Prototype |

Prototype : Type ident opar Formals cpar scolon | token_void ident opar Formals cpar scolon

StmtBlock : ocur MultiBinary_VariableDecl  Stmt  ccur

MultiBinary_VariableDecl : VariableDecl MultiBinary_VariableDecl |

MultiBinary_Stmt : Stmt MultiBinary_Stmt |


Stmt :  MultiBinary_Expr   | IfStmt | WhileStmt | ForStmt | BreakStmt |
		ReturnStmt | PrintStmt | StmtBlock

MultiBinary_Expr: Expr scolon MultiBinary_Expr	|

ExprBinaria : Expr | 

IfStmt : token_if opar Expr cpar Stmt ElseStmt

ElseStmt : token_else Stmt |

WhileStmt : token_while opar Expr cpar Stmt

ForStmt : token_for opar ExprBinaria scolon ExprBinaria scolon ExprBinaria cpar Stmt

ReturnStmt : token_return ExprBinaria scolon


BreakStmt : token_break scolon

PrintStmt : print opar Expresion cpar scolon

Expresion: Expr Multi_Expresion

Multi_Expresion : comma Expr Multi_Expresion |

Expr : LValue eql Expr {
			$$ = new ast_ExprBinary(lineno,column,$1,$3,$2);
			printf("ast_ExprBinary-> Lvalue eq Expr");
		}
	 | Constant | LValue | token_this | Call | opar Expr cpar |
	   Expr token_plus Expr | Expr token_minus Expr | Expr mult Expr | Expr token_div Expr |
	   Expr mod Expr | token_minus Expr | Expr menor Expr | Expr menorEql Expr |
	   Expr mayor Expr | Expr mayorEql Expr | Expr eqlEql Expr | Expr nEql Expr |
	   Expr token_and Expr | Expr token_or Expr |  token_not Expr | readInteger opar cpar  |
	   readLine opar cpar | token_new opar ident cpar | token_newArray opar Expr comma Type cpar

LValue : ident {
				$$ = new ast_LValueSimple(lineno,column,$1);
				printf("LValueSimple->linea: %d, columna: %d, ident: %s\n",lineno,column,$1);
			}
		| Expr punto ident{
				$$ = new ast_LvalueExpr(lineno,column,$1,$3);
				printf("LvalueExpr->linea: %d, columna: %d, ident: %s\n",lineno,column,$3);
			} 
		| Expr osqu Expr csqu {
				$$ = new ast_LvalueArray(lineno,column,$1,$3);
				printf("LvalueArray->linea: %d, columna: %d",lineno,column);
			}

Call : ident opar Actuals cpar | Expr punto ident opar Actuals cpar


Actuals : Expresion | 

Constant : intConstant {
	$$ = new ast_IntConstant(lineno,column,$1);
	printf("intContant-> linea: %d, columna: %d, valor: %d\n",lineno,column,$1);
	}
	| doubleConstant {
		$$ = new ast_DoubleConstant(lineno,column,$1);
	printf("doubleConstant-> linea: %d, columna: %d, valor: %f\n",lineno,column,$1);
	}
	| token_true {
		$$ = new ast_BoolConstant(lineno,column,true);
	printf("boolConstant-> linea: %d, columna: %d, valor: true\n",lineno,column);
	}
	| token_false {
		$$ = new ast_BoolConstant(lineno,column,false);
	printf("boolConstant-> linea: %d, columna: %d, valor: false\n",lineno,column);
	}
	| stringConstant {
		$$ = new ast_StringConstant(lineno,column,$1);
	printf("stringConstant-> linea: %d, columna: %d, valor: %s\n",lineno,column,$1);
	}
	| null {
		$$ = new ast_NullConstant(lineno,column);
	printf("null-> linea: %d, columna: %d\n",lineno,column);
	}

%%

void yyerror(char const *x){
	 
	printf("\nError de parsing en linea %d,columna %d",lineno,column);
	exit(1);
}