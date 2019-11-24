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

%type <programa> Program
%type <declaracion> Decl
%type <variableDecl> VariableDecl
%type <variable> Variable
%type <type> Type
%type <functionDecl> FunctionDecl
%type <formals> Formals
%type <classDecl> ClassDecl
%type <field> Field	 
%type <interfaceDecl> InterfaceDecl	 
%type <prototype> Prototype			               
%type <stmtBlock> StmtBlock		           
%type <stmt> Stmt
%type <ifStmt> IfStmt
%type <whileStmt> WhileStmt
%type <forStmt> ForStmt
%type <returnStmt> ReturnStmt
%type <breakStmt> BreakStmt
%type <printStmt> PrintStmt
%type <expr> Expr
%type <expr> ExprBinaria
%type <lvalue> LValue
%type <call> Call
%type <actuals> Actuals
%type <constant> Constant
%type <listaExpr> Expresion
%type <listaExpr> Multi_Expresion
%type <listaStmtOrVarDecl> Multi_StmtBlockContent
%type <listaPrototype> MultiBinary_Prototype
%type <listaIdent> Identificador
%type <listaIdent> Multi_Identificador
%type <listaIdent> Implements
%type <elseStmt> ElseStmt
%type <sval> Extends
%type <listaField> MultiBinary_Field
%type <type> TypeSimple
%type <listaVariables> Multi_Variable
%type <listaDecl> Multi_Decl


%token <sval> stringConstant
%token <ival> intConstant
%token <sval> ident
%token <dval> doubleConstant
%token <bval> token_true
%token <bval> token_false



%start Program

%%
Program : Decl Multi_Decl {
	$2-> push_back($1);
	$$ = new ast_Programa($2);
}


Multi_Decl: Decl Multi_Decl {
			$2-> push_back($1);
			$$ = $2;
		}
	|	{
			$$ = new std::vector<ast_Declaracion *>();
		} 

Decl : VariableDecl {
			$$=$1;
		} 
	| FunctionDecl {
			$$=$1;
		} 
	| ClassDecl	{
 			$$=$1;
		} 
	| InterfaceDecl	{
			$$=$1;
	}

VariableDecl : Variable scolon {
		$$ = new ast_VariableDecl(lineno,column,1,$1);
	}

Variable : Type ident {
		$$ =  new ast_Variable($1,$2);
	}

Type : TypeSimple {
			$$ = $1;
		} 
	| TypeSimple osqu csqu {
			$1->setIsArray(true);
			$$ = $1;
		}

TypeSimple : Type_int {
			$$ = new ast_Type(1,false);
		} 
	| Type_double {
			$$ = new ast_Type(2,false);
		} 
	| Type_bool {
			$$ = new ast_Type(3,false);
		} 
	| Type_string {
			$$ = new ast_Type(4,false);
		} 
	| ident{
			$$ = new ast_Type(1,false,$1);
		} 

FunctionDecl : Type ident opar Formals cpar StmtBlock {
			$$ = new ast_FunctionDecl(lineno,column,2,$1,$2,$4,$6);
		} 
	| token_void ident opar Formals cpar StmtBlock {
			$$ = new ast_FunctionDecl(lineno,column,2,new ast_Type(2,false),$2,$4,$6);
		}

Formals : Variable Multi_Variable {
			$2-> push_back($1);
			$$ = new ast_Formals($2);
			} 
		|	{
			$$ = new ast_Formals(new std::vector<ast_Variable *>());
			} 

Multi_Variable : comma Variable Multi_Variable {
			$$ = $3;
			$$-> push_back($2);
		}
	|	{
			$$ = new std::vector<ast_Variable *>();
		} 



ClassDecl : token_class ident Extends Implements ocur MultiBinary_Field  ccur {
		$$ =  new ast_ClassDecl(lineno,column,3,$2,$3,$4,$6);
	}

MultiBinary_Field : Field MultiBinary_Field {
			$$ = $2;
			$$-> push_back($1);
		} 
	|	{
			$$ = new std::vector<ast_Field *>();
		}

Extends: token_extends ident {
			$$ = $2;
		}
	| 	{
			$$ = "";
		}

Implements: token_implements Identificador {
			$$ = $2;
		} 
	|	{
			$$ = new std::vector<string>();
		}

Identificador : ident  Multi_Identificador {
		$$ = $2;
		$$-> push_back($1);
	}

Multi_Identificador : comma ident Multi_Identificador {
			$$ = $3;
			$$-> push_back($2);
		} 
	| 	{
			$$ = new std::vector<string>();
		}

Field : VariableDecl {
			$$ = new ast_Field($1);
		} 
	| FunctionDecl {
			$$ = new ast_Field($1);
		}

InterfaceDecl: token_interface ident ocur MultiBinary_Prototype  ccur {
		$$ = new ast_InterfaceDecl(lineno,column,4,$2,$4);
		//Falta print
	}

MultiBinary_Prototype: Prototype MultiBinary_Prototype {
			$$ = $2;
			$$-> push_back($1);
		}
	| {
		$$ = new std::vector<ast_Prototype *>();
	}

Prototype : Type ident opar Formals cpar scolon {
			$$ = new ast_Prototype($1,$2,$4);
			printf("Prototype-> ident: %s",$2);
		}
	| token_void ident opar Formals cpar scolon  {
			$$ = new ast_Prototype(new ast_Type(2,false),$2,$4);
			printf("Prototype-> ident: %s",$2);
		}

StmtBlock : ocur Multi_StmtBlockContent  ccur {
		$$ = new ast_StmtBlock(lineno,column,$2);
		printf("StmtBlock->linea: %d, columna: %d\n",lineno,column);

	}


Multi_StmtBlockContent : Stmt Multi_StmtBlockContent {
			$$ = $2;
			$$-> push_back(new ast_StmtOrVariableDecl($1)); 
		} 
	| VariableDecl Multi_StmtBlockContent {
			$$ = $2;
			$$-> push_back(new ast_StmtOrVariableDecl($1)); 
		}
	| {
		$$ = new std::vector<ast_StmtOrVariableDecl *>();
	}



Stmt :  ExprBinaria scolon {
			$$ = new ast_StmtBase(lineno,column,$1);
			printf("StmtBase->linea: %d, columna: %d\n",lineno,column);
		}  
	| IfStmt {
			$$ = $1;
		} 
	| WhileStmt {
			$$ = $1;
		}
	| ForStmt {
			$$ = $1;
		} 
	| BreakStmt {
			$$ = $1;
		} 
	|ReturnStmt {
			$$ = $1;
		} 
	| PrintStmt {
			$$ = $1;
		} 
	| StmtBlock {
			$$ = $1;
		}


ExprBinaria : Expr {
			$$ = $1;
		} 
	| {
		$$ = new ast_Expr();
	}

IfStmt : token_if opar Expr cpar Stmt ElseStmt {
		$$ = new ast_IfStmt(lineno,column,$3,$5,$6);
		printf("IfStmt->linea: %d, columna: %d\n",lineno,column);
	}

ElseStmt : token_else Stmt {
			$$ = new ast_ElseStmt(lineno,column,$2);
			printf("ElseStmt->linea: %d, columna: %d\n",lineno,column); 
		} 
	|	{
			$$ = new ast_ElseStmt(lineno,column);
			printf("ElseStmt-> No existe"); 
		} 

WhileStmt : token_while opar Expr cpar Stmt {
		$$ = new ast_WhileStmt(lineno,column,$3,$5);
		printf("WhileStmt->linea: %d, columna: %d\n",lineno,column);
	}

ForStmt : token_for opar ExprBinaria scolon ExprBinaria scolon ExprBinaria cpar Stmt {
		$$ = new ast_ForStmt(lineno,column,$3,$5,$7,$9);
		printf("ForStmt->linea: %d, columna: %d\n",lineno,column);
	}

ReturnStmt : token_return ExprBinaria scolon {
		$$ = new ast_ReturnStmt(lineno,column,$2);
		printf("ReturnStmt->linea: %d, columna: %d \n",lineno,column);
	}


BreakStmt : token_break scolon {
		$$ = new ast_BreakStmt(lineno,column);
		printf("BreakStmt->linea: %d, columna: %d\n",lineno,column);
	}

PrintStmt : print opar Expresion cpar scolon {
		$$ = new ast_PrintStmt(lineno,column,$3);
		printf("PrintStmt->linea: %d, columna: %d\n",lineno,column);
	}

Expresion: Expr Multi_Expresion {
		$$ = $2;
		$$->push_back($1);
	}

Multi_Expresion : comma Expr Multi_Expresion {
			$$ = $3;
			$$->push_back($2);
		} 
	|	{
		$$ = new std::vector<ast_Expr *>(); 
	}

Expr : LValue eql Expr {
			$$ = new ast_ExprBinary(lineno,column,$1,$3,1);
			printf("ExprBinary->linea: %d, columna: %d, tipoOp: eql",lineno,column);
		}
	 | Constant {
		 	$$ = $1;
		 }
	 | LValue{
		 	$$ = $1;
		 } 
	 | token_this {
		 	//Falta
	 	} 
	 | Call {
		 	$$ = $1;
	 	} 
	 | opar Expr cpar {
			$$ = $2;
	 	} 
	 |Expr token_plus Expr {
		 	$$ = new ast_ExprBinary(lineno,column,$1,$3,2);
			 printf("ExprBinary->linea: %d, columna: %d, tipoOp: plus\n",lineno,column);
	 	} 
	 | Expr token_minus Expr {
		 	$$ = new ast_ExprBinary(lineno,column,$1,$3,3);
			 printf("ExprBinary->linea: %d, columna: %d, tipoOp: minus\n",lineno,column);
	 	}
	 | Expr mult Expr {
		 	$$ = new ast_ExprBinary(lineno,column,$1,$3,4);
			 printf("ExprBinary->linea: %d, columna: %d, tipoOp: mult\n",lineno,column);
	 	} 
	 | Expr token_div Expr{
		 	$$ = new ast_ExprBinary(lineno,column,$1,$3,5);
			 printf("ExprBinary->linea: %d, columna: %d, tipoOp: div\n",lineno,column);
	 	} 
	 |Expr mod Expr {
		 	$$ = new ast_ExprBinary(lineno,column,$1,$3,6);
			 printf("ExprBinary->linea: %d, columna: %d, tipoOp: mod\n",lineno,column);
	 	} 
	 | token_minus Expr {
		 	$$ = new ast_ExprUnary(lineno,column,$2,3);
			 printf("ExprUnary->linea: %d, columna: %d, tipoOp: minus\n",lineno,column);
	 	} 
	 | Expr menor Expr {
		 	$$ = new ast_ExprBinary(lineno,column,$1,$3,7);
			printf("ExprBinary->linea: %d, columna: %d, tipoOp: menor\n",lineno,column);
	 	} 
	 | Expr menorEql Expr {
		 	$$ = new ast_ExprBinary(lineno,column,$1,$3,8);
			 printf("ExprBinary->linea: %d, columna: %d, tipoOp: menorEql\n",lineno,column);
	 	} 
	 |Expr mayor Expr {
		 	$$ = new ast_ExprBinary(lineno,column,$1,$3,9);
			 printf("ExprBinary->linea: %d, columna: %d, tipoOp: mayor\n",lineno,column);
	 	} 
	| Expr mayorEql Expr {
			$$ = new ast_ExprBinary(lineno,column,$1,$3,10);
			printf("ExprBinary->linea: %d, columna: %d, tipoOp: mayorEql\n",lineno,column);
		} 
	| Expr eqlEql Expr {
			$$ = new ast_ExprBinary(lineno,column,$1,$3,11);
			printf("ExprBinary->linea: %d, columna: %d, tipoOp: eqlEql\n",lineno,column);	
		} 
	| Expr nEql Expr {
			$$ = new ast_ExprBinary(lineno,column,$1,$3,12);
			printf("ExprBinary->linea: %d, columna: %d, tipoOp: nEql\n",lineno,column);
		} 
	|Expr token_and Expr {
			$$ = new ast_ExprBinary(lineno,column,$1,$3,13);
			printf("ExprBinary->linea: %d, columna: %d, tipoOp: and\n",lineno,column);
		} 
	| Expr token_or Expr {
			$$ = new ast_ExprBinary(lineno,column,$1,$3,14);
			printf("ExprBinary->linea: %d, columna: %d, tipoOp: or\n",lineno,column);
		} 
	|  token_not Expr {
			$$ = new ast_ExprUnary(lineno,column,$2,15);
			printf("ExprUnary->linea: %d, columna: %d, tipoOp: not\n",lineno,column);
		} 
	| readInteger opar cpar {
			$$ = new ast_ExprRead(lineno,column,2);
			printf("ExprRead->linea: %d, columna: %d, tipoRead: Integer\n",lineno,column);
		} 
	|readLine opar cpar {
			$$ = new ast_ExprRead(lineno,column,1);
			printf("ExprRead->linea: %d, columna: %d, tipoRead: Line\n",lineno,column);
		} 
	| token_new opar ident cpar {
			$$ = new ast_ExprNew(lineno,column,$3);
			printf("ExprNew->linea: %d, columna: %d, ident: %s\n",lineno,column,$3);
		} 
	| token_newArray opar Expr comma Type cpar {
			$$ = new ast_ExprNewArray(lineno,column,$3,$5);
			printf("ExprNewArray->linea: %d, columna: %d\n",lineno,column);
		}

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
				printf("LvalueArray->linea: %d, columna: %d\n",lineno,column);
			}

Call : ident opar Actuals cpar {
			$$ = new ast_CallSimple(lineno,column,$1,$3);
			printf("CallSimple-> linea: %d, columna: %d, ident: %s\n",lineno,column,$1);
			
		} 
	| Expr punto ident opar Actuals cpar {
			$$ = new ast_CallExpr(lineno,column,$1,$3,$5);
			printf("CallExpr-> linea: %d, columna: %d, ident: %s\n",lineno,column,$3);
		}


Actuals : Expresion {
				$$ = new ast_Actuals($1);
				printf("Actuals-> una expr o +\n");
			} 
		| {
			$$ = new ast_Actuals(new std::vector<ast_Expr *>());
			printf("Actuals-> vacio\n");
		}

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