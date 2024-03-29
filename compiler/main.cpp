#include <iostream>
#include <stdio.h>
#include "objetos.h"
extern int yyparse();
extern ast_Programa * getArbol();
/*
 * Declarations for a calculator fb3-1
 */
/* interface to the lexer */
extern int yylineno; /* from lexer */
void yyerror(char *s, ...);
/* nodes in the abstract syntax tree */
struct ast {
 int nodetype;
 struct ast *l;
 struct ast *r;
};
struct numval {
 int nodetype; /* type K for constant */
 double number;
};
/* build an AST */
struct ast *newast(int nodetype, struct ast *l, struct ast *r);
struct ast *newnum(double d);
/* evaluate an AST */
double eval(struct ast *);
/* delete and free an AST */
void treefree(struct ast *);




int main(){
	int result = yyparse();
	if(result == 0){
		std::cout << "Exito"<< std::endl;
		ast_Programa * arbol = getArbol();
		ScopeProgram * scopePadre = new ScopeProgram(arbol);
		

		bool resultado = (*scopePadre).analizarArbol();
	
		
		if(!resultado){
			cout<<"\n\nImprimiendo errores"<<endl;
       		for(int i = 0; i < scopePadre->getErrores()->size();i++){
            cout<<scopePadre->getErrores()->at(i)<<endl;
       		}
		}
		else{
			cout<<"No se ha detectado ningun error"<<endl;
		}
		}
	else
		std::cout << "Error"<< std::endl;

	
	return result;

}