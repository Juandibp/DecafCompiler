%{
 #include <math.h>
 #include <stdio.h>
 #include <stdlib.h>
 int yylex (void);
 void yyerror (char const *);
 

%}

%union {
  int ival;
  double dval;
  char *sval ;
}


 
%token /*Constantes */ intConstant doubleConstant boolConstant stringConstant  
		/*Operadores*/	plus minus mult	token_div mod  menor menorEql mayor mayorEql eql eqlEql nEql 
					    token_and token_or token_not scolon comma punto 
		/*Parentesis*/  /*[ ]*/osqu csqu /*( ) */ opar cpar /*{}*/ ocur ccur
		/*Palabras Reservadas*/ token_void Type_int Type_double Type_bool Type_string token_class token_interface null
								token_this token_extends token_implements token_for token_while token_if token_else
								token_return token_break token_new token_newArray print readInteger readLine
		 
	    ident           
		           
		      
		     
		   
		

%start Program

%%
Program : Decl Multi_Decl 

Multi_Decl: Decl Multi_Decl | 

Decl : VariableDecl | FunctionDecl | ClassDecl | InterfaceDecl

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


Stmt :  ExprBinaria  scolon | IfStmt | WhileStmt | ForStmt | BreakStmt |
		ReturnStmt | PrintStmt | StmtBlock

ExprBinaria : Expr | 

IfStmt : token_if opar Expr cpar Stmt ElseStmt

ElseStmt : token_else Stmt |

WhileStmt : token_while opar Expr cpar Stmt

ForStmt : token_for opar ExprBinaria scolon ExprBinaria scolon ExprBinaria cpar Stmt

ReturnStmt : token_return ExprBinaria scolon


BreakStmt : token_break ;

PrintStmt : print opar Expresion cpar scolon

Expresion: Expr Multi_Expresion

Multi_Expresion : comma Expr Multi_Expresion |

Expr : LValue eql Expr | Constant | LValue | token_this | Call | opar Expr cpar |
	   Expr plus Expr | Expr minus Expr | Expr mult Expr | Expr token_div Expr |
	   Expr mod Expr | minus Expr | Expr menor Expr | Expr menorEql Expr |
	   Expr mayor Expr | Expr mayorEql Expr | Expr eqlEql Expr | Expr nEql Expr |
	   Expr token_and Expr | Expr token_or Expr |  token_not Expr | readInteger opar cpar  |
	   readLine opar cpar | token_new opar ident cpar | token_newArray opar Expr comma Type cpar

LValue : ident | Expr punto ident | Expr osqu Expr csqu

Call : ident opar Actuals cpar | Expr punto ident opar Actuals cpar


Actuals : Expresion | 

Constant : intConstant | doubleConstant | boolConstant |
			 stringConstant | null
%%

void yyerror(char const *x){

	printf("Error %s  \n",x);
	exit(1);
}