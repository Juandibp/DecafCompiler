#include "objetos.h"

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <sstream>

//PROGRAMA

ast_Programa::ast_Programa(vector<ast_Declaracion *> * Declaraciones){
    this->declaraciones=Declaraciones;
}

vector<ast_Declaracion *> * ast_Programa::getDeclaraciones()
{
    return this->declaraciones;
}
void ast_Programa::printTree(){
    printf("Programa\n");
    for (int i=0; i<(*this->declaraciones).size();i++){
        ast_Declaracion * declaracion = (*this->declaraciones).at(i);
    
        
        cout<<"\t|-";
        (*declaracion).toString(2);
    }
}

//DECLARACIOn

ast_Declaracion::ast_Declaracion(int linea, int columna, int tipo){
    this->linea=linea;
    this->columna=columna;
    this->tipoDeclaracion=tipo;
}

int ast_Declaracion::getLinea(){
    return this->linea;
}

int ast_Declaracion::getColumna(){
    return this->columna;
}

int ast_Declaracion::getTipo(){
    return this->tipoDeclaracion;
}

//VARIABLES

ast_VariableDecl::ast_VariableDecl(int linea, int columna, int tipo,ast_Variable* var): ast_Declaracion(linea,columna,tipo){
    this->linea=linea;
    this->columna=columna;
    this->tipoDeclaracion=tipo;
    this ->var=var;
}

ast_Variable * ast_VariableDecl::getVar(){
    return this->var;
}
void ast_VariableDecl::toString(int cantidadTabs){
    string tabs(cantidadTabs,'\t');
    string ident = (this->getVar()->getString());
    string tipo;
    std::stringstream linea;
    linea << this->getLinea();
    std::stringstream columna;
    columna <<  this->getColumna();
     switch(this->getVar()->getTipo()->getTipo()){
            case 1: 
                tipo = "int";
                break;
            case 2: 
                tipo = "void";
                break;
            case 3: 
                tipo = "bool";
                break;
            case 4: 
                tipo = "double";
                break;
            case 5: 
                tipo = "string";
                break;
            case 6: 
                tipo = this->getVar()->getTipo()->getIdent();
                break;
        }
    cout<<"Variable: nombre->  "+ ident + " tipo-> "+tipo + " linea-> "+ linea.str() + " columna-> " + columna.str()<<endl;  
}
ast_Variable::ast_Variable(ast_Type* tipo, string ident){
    this->tipo=tipo;
    this->ident=ident;
}

ast_Type * ast_Variable::getTipo(){
    return this->tipo;
}

string ast_Variable::getString(){
    return this->ident;
}

void ast_Variable::toString(int cantidadTabs){
    string tabs(cantidadTabs,'\t');
    string tipo;
    switch(this->getTipo()->getTipo()){
            case 1: 
                tipo = "int";
                break;
            case 2: 
                tipo = "void";
                break;
            case 3: 
                tipo = "bool";
                break;
            case 4: 
                tipo = "double";
                break;
            case 5: 
                tipo = "string";
                break;
            case 6: 
                tipo = this->getTipo()->getIdent();
                break;
        }
    cout<<tabs + "|- "+ tipo + " "+ this->ident<<endl; 
}

int ast_Variable::analizarVariable(vector<string> * listaParametros, Scope * scope ){
    ScopeClass * tipoVariable;
    std::stringstream linea;
    linea << (this->getTipo()->getLinea());
    std::stringstream columna;
    columna << (this->getTipo()->getColumna());

     for(int i = 0; i < (listaParametros->size()); i++){
        if(listaParametros->at(i) == this->ident){
            error = "Error: declaracion previa de " +this->ident + " en " + linea.str() + ":"+columna.str() ;
            return 1;
        }
    }

    if(this->getTipo()->getTipo() == 6){
        tipoVariable = scope->obtenerClase(this->getTipo()->getIdent());

        if(tipoVariable == NULL){
            error = "Error: el tipo "+ this->getTipo()->getIdent() + " no existe en " + linea.str() + ":"+columna.str() ;
            return 2;
        }
    }

   

    error = "";
    return 0;
}

string ast_Variable:: getError(){
    return error;
}
//TYPES
ast_Type::ast_Type(int linea,int columna,int numTipoDato ,bool array){
    this->tipoDato=numTipoDato;
    this->isArray=array;
    this->linea = linea;
    this->columna = columna;
}
ast_Type::ast_Type(int linea,int columna,int numTipoDato,bool array,string ident){
    this->tipoDato=numTipoDato;
    this->isArray=array;
    this->ident=ident;
     this->linea = linea;
    this->columna = columna;
}

int ast_Type::getTipo(){
    return this->tipoDato;
}

bool ast_Type::getIsArray(){
    return this->isArray;
}

string ast_Type::getIdent(){
    return this->ident;
}

void ast_Type::setIsArray(bool b){
    this->isArray = b;
}

int ast_Type::getLinea(){
    return linea;
}

int ast_Type::getColumna(){
    return columna;
}

//ast_FunctionDecl

ast_FunctionDecl::ast_FunctionDecl(int linea,int columna,int tipoDecl,ast_Type * tipoFunc, string ident, ast_Formals * formals, ast_StmtBlock * stmtBlock): ast_Declaracion(linea,columna,tipoDecl){
    this->linea=linea;
    this->columna=columna;
    this->tipoDeclaracion=tipoDecl;
    this->tipoFunc = tipoFunc; 
    this->ident = ident; 
    this->formals = formals;
    this->stmtBlock = stmtBlock;  
}

ast_Type * ast_FunctionDecl::getTipoFuncion(){
    return this->tipoFunc;
}

string ast_FunctionDecl::getIdent(){
    return this->ident;
}

ast_Formals * ast_FunctionDecl::getFormals(){
    return this->formals;
}

ast_StmtBlock * ast_FunctionDecl::getStmtBlock(){
    return this->stmtBlock;
}

void ast_FunctionDecl::toString(int cantidadTabs){
    string tabs(cantidadTabs,'\t');
    string ident = this->ident;
    string tipo;
    std::stringstream linea;
    linea << this->getLinea();
    std::stringstream columna;
    columna <<  this->getColumna();
     switch(this->getTipoFuncion()->getTipo()){
            case 1: 
                tipo = "int";
                break;
            case 2: 
                tipo = "void";
                break;
            case 3: 
                tipo = "bool";
                break;
            case 4: 
                tipo = "double";
                break;
            case 5: 
                tipo = "string";
                break;
            case 6: 
                tipo = this->getTipoFuncion()->getIdent();
                break;
        }
    cout<<"Funcion: nombre->  "+ ident + " return-> "+tipo + " linea-> "+ linea.str() + " columna-> " + columna.str()<<endl; 

    if(this->getFormals()->getVariables()->size() != 0){
        cout<<tabs + "|-Parametos " <<endl ;
        for(int i = 0; i < this->getFormals()->getVariables()->size() ; i++){
            (*this->getFormals()->getVariables()->at(i)).toString(cantidadTabs + 1);
        }
    }

    if(this->getStmtBlock()->getContent()->size() != 0){
        for(int i = 0; i < this->getStmtBlock()->getContent()->size();i++){
            (*this->getStmtBlock()->getContent()->at(i)).toString(cantidadTabs+1);
        }
    }
}

//ast_Formals

ast_Formals::ast_Formals(vector<ast_Variable *> * variables){
    this->variables = variables;
}

vector<ast_Variable *> * ast_Formals::getVariables(){
    return this->variables;
}

//ast_ClassDecl

ast_ClassDecl::ast_ClassDecl(int linea,int columna,int tipoDecl,string ident,string extends, vector<string> * implements, vector<ast_Field *> * fields):ast_Declaracion(linea,columna,tipoDecl){
    this->linea=linea;
    this->columna=columna;
    this->tipoDeclaracion=tipoDecl;
    this->ident = ident; 
    this->extends = extends;
    this->implements = implements;
    this->fields = fields; 
}

string ast_ClassDecl::getIdent(){
    return this-> ident;
}

string  ast_ClassDecl::getExtenteds(){
    return this-> extends;
}

vector<string> * ast_ClassDecl::getImplements(){
    return this-> implements; 
}

vector<ast_Field *> * ast_ClassDecl::getFields(){
    return this-> fields;
}

void ast_ClassDecl::toString(int cantidadTabs){
    string ident = this->ident;
    string extends = "";
    std::stringstream linea;
    linea << this->getLinea();
    std::stringstream columna;
    columna <<  this->getColumna();

    if(this->getExtenteds() != ""){
        extends = " clasePadre-> "+this->getExtenteds();
    }
    cout<<"Clase: nombre->  "+ ident + extends + + " linea-> "+ linea.str() + " columna-> " + columna.str()<<endl; 
}

//ast_TokenClass

ast_TokenClass::ast_TokenClass(int linea,int columna){
     this->linea = linea;
    this->columna = columna;
}

int ast_TokenClass::getLinea(){
    return linea;
}

int ast_TokenClass::getColumna(){
    return columna;
}

//ast_Field

ast_Field::ast_Field(ast_VariableDecl* varDecl){
    this->tipoDeclracion = 1;
    this->variableDecl = varDecl;
}

ast_Field::ast_Field(ast_FunctionDecl* funDecl){
    this->tipoDeclracion = 2;
    this->functionDecl = funDecl;
}

int ast_Field::getTipoDecl(){
    return this->tipoDeclracion;
}

ast_VariableDecl * ast_Field::getVariableDecl(){
    return this->variableDecl;
}

ast_FunctionDecl * ast_Field::getFunctionDecl(){
    return this->functionDecl;
}

//ast_InterfaceDecl

ast_InterfaceDecl::ast_InterfaceDecl(int linea,int columna,int tipoDecl, string ident, vector<ast_Prototype *> * prototypes): ast_Declaracion(linea,columna,tipoDecl){
    this->linea=linea;
    this->columna=columna;
    this->tipoDeclaracion=tipoDecl;
    this->ident = ident;
    this->prototypes = prototypes;    
}

string ast_InterfaceDecl::getIdent(){
    return this->ident;
}

vector<ast_Prototype *> * ast_InterfaceDecl::getPrototype(){
  return this->prototypes;  
}

void ast_InterfaceDecl::toString(int cantidadTabs){
    string tabs(cantidadTabs,'\t');
}

//ast_Prototype

ast_Prototype::ast_Prototype(ast_Type * tipo, string ident,ast_Formals * formals){
    this->tipo = tipo;
    this->ident = ident;
    this->formals = formals;
}

ast_Type * ast_Prototype::getTipo(){
    return this->tipo;
}

string ast_Prototype::getIdent(){
    return this->ident;
}

ast_Formals * ast_Prototype::getFormals(){
    return this->formals;
}

//ast_Stmt

ast_Stmt::ast_Stmt(int linea, int columna, int tipo){
    this->linea = linea;
    this->columna = columna;
    this->tipoStmt = tipo;
    this->errores = new vector<string>();
}

int ast_Stmt::getLinea(){
    return this->linea;
}

int ast_Stmt::getColumna(){
    return this->columna;
}

int ast_Stmt::getTipoStmt(){
    return this->tipoStmt;
}

vector<string> * ast_Stmt::getErrores(){
    return errores;
}

//ast_StmtBase

ast_StmtBase::ast_StmtBase(int linea,int columna,ast_Expr * expresion):ast_Stmt(linea,columna,1){
    this->expresion = expresion;
}

ast_Expr * ast_StmtBase::getExpresion(){
    return this->expresion;
}

bool ast_StmtBase::analizarStmt(Scope * scope){
    if(!expresion->isNull()){
        bool resultado = expresion->analizarExpr(scope);
        if(!resultado){
            this->errores = unirErrores(errores,expresion->getErrores());
            return false;
        }
        if(expresion->getTipoExpr() == 8){
            
        }
    }
    return true;
}
//ast_IfStmt

ast_IfStmt::ast_IfStmt(int linea,int columna,ast_Expr * expresion,ast_Stmt * stmt, ast_ElseStmt * elseStmt):ast_Stmt(linea,columna,2){
    this->expresion = expresion;
    this->stmt = stmt;
    this->elseStmt =elseStmt;

}


ast_Expr * ast_IfStmt::getExpresion(){
    return this->expresion;
}


ast_Stmt * ast_IfStmt ::getStmt(){
    return this->stmt;
}



ast_ElseStmt * ast_IfStmt ::getElseStmt(){
    return this->elseStmt;
}

bool ast_IfStmt::analizarStmt(Scope * scope){
    std::stringstream linea;
    linea << (this->linea);
    std::stringstream columna;
    columna << (this->columna);
    if(expresion->isNull()){
        this->errores->push_back("Error: expresion invalida en " + linea.str() + ":"+columna.str()) ;
    }

    if(!(stmt->analizarStmt(scope))){
        errores = unirErrores(errores,stmt->getErrores());
        return false;
    }

    if(!(elseStmt->analizarStmt(scope))){
        errores = unirErrores(errores,elseStmt->getErrores());
        return false;
    }

    return true;
}

//ast_ElseStmt 

ast_ElseStmt::ast_ElseStmt(int linea,int columna,ast_Stmt * stmt):ast_Stmt(linea,columna,9){
    this->stmt = stmt;
    this->isElseNull = false;
}

ast_ElseStmt::ast_ElseStmt(int linea,int columna):ast_Stmt(linea,columna,9){
    this->isElseNull = true;
}

ast_Stmt * ast_ElseStmt ::getStmt(){
    return this->stmt;
}

bool ast_ElseStmt ::isNull(){
    return this->isElseNull;
}

bool ast_ElseStmt ::analizarStmt(Scope * scope){
    if(!isElseNull){
        if(!stmt->analizarStmt(scope)){
            errores = unirErrores(errores,stmt->getErrores());
            return false;
        }
    }

    return true;
}



//ast_WhileStmt

ast_WhileStmt::ast_WhileStmt(int linea, int columna,ast_Expr * expresion, ast_Stmt* stmt):ast_Stmt(linea,columna,3){
    this->expresion = expresion;
    this->stmt = stmt;
}

ast_Expr * ast_WhileStmt::getExpresion(){
    return this->expresion;
}

ast_Stmt * ast_WhileStmt::getStmt(){
    return this->stmt;
}

bool ast_WhileStmt::analizarStmt(Scope * scope){
    bool resultado = true;

    if(!expresion->analizarExpr(scope)){
        resultado =false;
        errores = unirErrores(errores,expresion->getErrores());
    }
    if(!stmt->analizarStmt(scope)){
        resultado =false;
        errores = unirErrores(errores,stmt->getErrores());
    }

    return resultado;
}

//ast_ForStmt

ast_ForStmt::ast_ForStmt(int linea, int columna, ast_Expr * firstExpr, ast_Expr * secondExpr,ast_Expr * thirdExpresion,ast_Stmt * stmt): ast_Stmt(linea,columna,4){
    this->firstExpr = firstExpr;

    this->secondExpr = secondExpr;


    this->thirdExpr = thirdExpr;

    this->stmt = stmt;

}

ast_Expr * ast_ForStmt::getFirstExpr(){
    return this->firstExpr;
}

ast_Expr * ast_ForStmt::getSecondExpr(){
    return this->secondExpr;
}

ast_Expr * ast_ForStmt::getThirdExpr(){
    return this->thirdExpr;
}


ast_Stmt * ast_ForStmt::getStmt(){
    return this->stmt;
}

bool ast_ForStmt ::analizarStmt(Scope * scope){
    bool resultado = true;
    if(!firstExpr->analizarExpr(scope)){
        errores = unirErrores(errores,firstExpr->getErrores());
        resultado = false;
    }

    if(!secondExpr->analizarExpr(scope)){
        errores = unirErrores(errores,secondExpr->getErrores());
        resultado = false;
    }

    if(!thirdExpr->analizarExpr(scope)){
        errores = unirErrores(errores,thirdExpr->getErrores());
        resultado = false;
    }

    if(!stmt->analizarStmt(scope)){
        errores = unirErrores(errores,stmt->getErrores());
        resultado = false;
    }



    return resultado;
}


//ast_ReturnStmt

ast_ReturnStmt::ast_ReturnStmt(int linea, int columna, ast_Expr * expresion): ast_Stmt(linea,columna,5){
    this->expresion = expresion;
    this->haveExpr = true;
}

ast_ReturnStmt::ast_ReturnStmt(int linea, int columna): ast_Stmt(linea,columna,5){
    this->haveExpr = false;
}


ast_Expr * ast_ReturnStmt::getExpresion(){
    return this->expresion;
}

bool ast_ReturnStmt::getHaveExpr(){
    return this->haveExpr;
}

bool  ast_ReturnStmt ::analizarStmt(Scope * scope){
    if(haveExpr){
        if(expresion->analizarExpr(scope)){
            tipoRetorno = expresion->obtenerTipoExpr(scope);
            return true;
        }
        else{
            errores = unirErrores(errores,expresion->getErrores());
            return false;
        }
    }
    else{
        //Falta agregar tipo de clase void
    }

    return true;
}

ScopeClass * ast_ReturnStmt::getTipoRetorno(){
    return tipoRetorno;
}

//ast_BreakStmt

ast_BreakStmt::ast_BreakStmt(int linea, int columna):ast_Stmt(linea,columna,6){

}

bool ast_BreakStmt::analizarStmt(Scope * scope){
    return true;
}

//ast_PrintStmt

ast_PrintStmt::ast_PrintStmt(int linea,int columna,vector<ast_Expr *> * expresiones):ast_Stmt(linea,columna,7){
    this->expresiones = expresiones;
}

vector<ast_Expr *> * ast_PrintStmt::getExpresiones(){
    return this->expresiones;
}

bool ast_PrintStmt::analizarStmt(Scope * scope){
    bool resultado = true;
    for(int i = 0; i < expresiones->size();i++){
        ast_Expr * expresion = expresiones->at(i);

        if(expresion->analizarExpr(scope)){
            //Falta implementar string
        }
        else{
            errores = unirErrores(errores,expresion->getErrores());
            resultado = false;
        }
    }
    return resultado;
}

//ast_StmtBlock

ast_StmtBlock:: ast_StmtBlock(int linea, int columna,vector<ast_StmtOrVariableDecl *> * content):ast_Stmt(linea,columna,8){
    this->content = content;
 
}

vector<ast_StmtOrVariableDecl *> * ast_StmtBlock::getContent(){
    return this-> content;
}

bool ast_StmtBlock::analizarStmt(Scope * scope){

    bool resultado = true;
    for(int i = 0; i < content->size();i++){
        ast_StmtOrVariableDecl * eso = content->at(i);

        if(eso->getTipo() == 1){
            ast_Stmt * stmt =  eso->getStmt();
            if(!stmt->analizarStmt(scope)){
                errores = unirErrores(errores,stmt->getErrores());
                resultado = false;
            }
        }
       
    }

    return resultado;
}


//ast_StmtOrVariableDecl 

ast_StmtOrVariableDecl::ast_StmtOrVariableDecl(ast_Stmt * stmt){
    this->stmt = stmt;
    this->tipo = 1;    
}

ast_StmtOrVariableDecl::ast_StmtOrVariableDecl(ast_VariableDecl * varDecl){
    this->variableDecl = varDecl;
    this->tipo = 2;    
}

int ast_StmtOrVariableDecl::getTipo(){
    return this->tipo;    
}

ast_Stmt* ast_StmtOrVariableDecl::getStmt(){
    return this->stmt;    
}

ast_VariableDecl * ast_StmtOrVariableDecl::getVariableDecl(){
    return this->variableDecl;    
}

void ast_StmtOrVariableDecl::toString(int cantidadTabs){
    string tabs(cantidadTabs,'\t');
    if(this->tipo == 2){
        (*this->getVariableDecl()).toString(cantidadTabs+1);
    }
}



//ast_Expr

ast_Expr::ast_Expr(int linea,int columna, int tipo){
    this-> linea = linea;
    this-> columna = columna;
    this-> tipoExpr = tipo;
    this-> isNullExpr = false;
    this->errores = new vector<string>();
}

ast_Expr::ast_Expr(){
    this->isNullExpr = true;
}

bool ast_Expr::isNull(){
    return this->isNullExpr;
}

int ast_Expr::getLinea(){
    return this->linea;
}

int ast_Expr::getColumna(){
    return this->columna;
}

int ast_Expr::getTipoExpr(){
    return this->tipoExpr;
}

vector<string> * ast_Expr::getErrores(){
    return errores;
}

//ast_ExprSimple

ast_ExprSimple ::ast_ExprSimple():ast_Expr(){
    
}
ScopeClass * ast_ExprSimple::obtenerTipoExpr(Scope * scope){
    return new ScopeClass(scope,new ast_ClassDecl(1,1,1,"","",new vector<string>(),new vector<ast_Field * >()));
}
bool ast_ExprSimple::analizarExpr(Scope * scope){
    return true;
}

//ast_ExprBinary

ast_ExprBinary::ast_ExprBinary(int linea,int columna,ast_Expr * exprIzq, ast_Expr * exprDer, int numTipoOp):ast_Expr(linea,columna,1){

    this->exprIzq = exprIzq;
    this->exprDer = exprDer;
    this->tipoOp = numTipoOp;
}

ast_Expr * ast_ExprBinary::getExprIzq(){
    return this->exprIzq;
}

ast_Expr * ast_ExprBinary::getExprDer(){
    return this->exprDer;
}

int ast_ExprBinary::getTipoOp(){
    return this->tipoOp;
}

bool ast_ExprBinary::analizarExpr(Scope * scope){
    if(!exprIzq->analizarExpr(scope)){
       this->errores =  unirErrores(this->errores,exprIzq->getErrores());
        return false;
    }
     if(!exprDer->analizarExpr(scope)){
       this->errores =  unirErrores(this->errores,exprDer->getErrores());
        return false;
    }
    return true;

}

ScopeClass * ast_ExprBinary::obtenerTipoExpr(Scope * scope){
    return new ScopeClass(scope,new ast_ClassDecl(1,1,1,"","",new vector<string>(),new vector<ast_Field * >()));
}

//ast_ExprUnary

ast_ExprUnary::ast_ExprUnary(int linea, int columna, ast_Expr * expresion,int numTipoOp):ast_Expr(linea,columna,2){
    

    this->expresion = expresion;
    this->tipoOp= numTipoOp;
}

ast_Expr * ast_ExprUnary::getExpresion(){
    return this->expresion;
}

int ast_ExprUnary::getTipoOp(){
    return this->tipoOp;
}

bool ast_ExprUnary::analizarExpr(Scope * scope){
     if(!expresion->analizarExpr(scope)){
       this->errores =  unirErrores(this->errores,expresion->getErrores());
        return false;
    }

    return true;
}

ScopeClass * ast_ExprUnary::obtenerTipoExpr(Scope * scope){
    return new ScopeClass(scope,new ast_ClassDecl(1,1,1,"","",new vector<string>(),new vector<ast_Field * >()));
}

//ast_ExprRead

ast_ExprRead::ast_ExprRead(int linea,int columna,int tipoRead):ast_Expr(linea,columna,3){
    this->tipoRead = tipoRead;
}

int ast_ExprRead::getTipoRead(){
    return tipoRead;
}

bool ast_ExprRead::analizarExpr(Scope * scope){
    return true;
}

ScopeClass * ast_ExprRead::obtenerTipoExpr(Scope * scope){
    return new ScopeClass(scope,new ast_ClassDecl(1,1,1,"","",new vector<string>(),new vector<ast_Field * >()));
}

//ast_ExprNew

ast_ExprNew::ast_ExprNew(int linea,int columna,string ident):ast_Expr(linea,columna,4){
    this->ident = ident;
}

string ast_ExprNew::getIdent(){
    return this->ident;
}

bool ast_ExprNew::analizarExpr(Scope * scope){
   ScopeClass * tipoNew = scope->obtenerClase(this->ident);
    std::stringstream linea;
    linea << (this->linea);
    std::stringstream columna;
    columna << (this->columna);
   if(tipoNew == NULL){
       this->errores->push_back("Error: el tipo "+ this->ident + " no existe en " + linea.str() + ":"+columna.str()) ;
       return false;
   }
   return true;

}

ScopeClass * ast_ExprNew::obtenerTipoExpr(Scope * scope){
    return new ScopeClass(scope,new ast_ClassDecl(1,1,1,"","",new vector<string>(),new vector<ast_Field * >()));
}

//ExprNewArrray

ast_ExprNewArray::ast_ExprNewArray(int linea, int columna, ast_Expr * expresion, ast_Type * tipoDato):ast_Expr(linea,columna,5){
    this->expresion = expresion;
    this->tipoDato = tipoDato;
}

ast_Expr * ast_ExprNewArray::getExpresion(){
    return this->expresion;
}

ast_Type * ast_ExprNewArray::getTipoDatos(){
    return this->tipoDato;
}

bool ast_ExprNewArray::analizarExpr(Scope * scope){
    std::stringstream linea;
    linea << (this->linea);
    std::stringstream columna;
    columna << (this->columna);
    if(this->tipoDato->getTipo() == 6){
         ScopeClass * tipoNew = scope->obtenerClase(this->tipoDato->getIdent());

        if(tipoNew == NULL){
        this->errores->push_back("Error: el tipo "+ this->tipoDato->getIdent() + " no existe en " + linea.str() + ":"+columna.str()) ;
        return false;
         }
   

    }

    bool resultado = expresion->analizarExpr(scope);
    if(!resultado){
        errores = unirErrores(errores,expresion->getErrores());
        return false;
    }

    return true;
}

ScopeClass * ast_ExprNewArray::obtenerTipoExpr(Scope * scope){
    return new ScopeClass(scope,new ast_ClassDecl(1,1,1,"","",new vector<string>(),new vector<ast_Field * >()));
}

//Lvalue

ast_LValue::ast_LValue(int linea, int columna, int tipoLValue):ast_Expr(linea,columna,6){
    this->tipoLvalue = tipoLValue;
}

int ast_LValue::getTipoLvalue(){
    return this->tipoLvalue;
}

ScopeClass * ast_LValue::obtenerTipoExpr(Scope * scope){
    return new ScopeClass(scope,new ast_ClassDecl(1,1,1,"","",new vector<string>(),new vector<ast_Field * >()));
}

//ast_LValueSimple

ast_LValueSimple::ast_LValueSimple(int linea,int columna, string ident):ast_LValue(linea,columna,1){
    this->ident = ident;

}

string ast_LValueSimple::getIdent(){
    return this->ident;
}

bool ast_LValueSimple :: analizarExpr(Scope * scope){
    bool resultado = exiteIdent(scope,this->ident);
    std::stringstream linea;
    linea << (this->linea);
    std::stringstream columna;
    columna << (this->columna);
    if(!resultado){
        this->errores->push_back("Error: el identificador "+ ident +" no esta definido en " + linea.str() + ":"+columna.str()) ;
        return false;
    }
    return true;
}

ScopeClass * ast_LValueSimple::obtenerTipoExpr(Scope * scope){
    return new ScopeClass(scope,new ast_ClassDecl(1,1,1,"","",new vector<string>(),new vector<ast_Field * >()));
}

//ast_LvalueExpr

ast_LvalueExpr::ast_LvalueExpr(int linea, int columna, ast_Expr * expresion, string ident):ast_LValue(linea,columna,2){
    this->expresion = expresion;
    this->ident = ident;
}

ast_Expr * ast_LvalueExpr:: getExpr(){
    return this-> expresion;
}

string ast_LvalueExpr::getIdent(){
    return this->ident;
}

bool ast_LvalueExpr::analizarExpr(Scope * scope){
    bool resultado =  expresion->analizarExpr(scope);
    std::stringstream linea;
    linea << (this->linea);
    std::stringstream columna;
    columna << (this->columna);
    if(!resultado){
        errores = unirErrores(errores,expresion->getErrores());
        return false;
    }
    ScopeClass * clase = expresion->obtenerTipoExpr(scope);
   
    if(!clase->isTipoPrimitivo() &&!clase->existeVariable(this->ident)){
            this->errores->push_back("Error: la clase "+ clase->getClase()->getIdent() + "no tiene un atributo "+this->ident+" en " + linea.str() + ":"+columna.str()) ;
            return false;
    }
    

    return true;

}

ScopeClass * ast_LvalueExpr::obtenerTipoExpr(Scope * scope){
    return new ScopeClass(scope,new ast_ClassDecl(1,1,1,"","",new vector<string>(),new vector<ast_Field * >()));
}
//ast_LvalueArray

ast_LvalueArray::ast_LvalueArray(int linea, int columna,ast_Expr * firstEXpr, ast_Expr* secondExpr):ast_LValue(linea,columna,3){
    this->firstExpr = firstEXpr;
    this->secondExpr = secondExpr;
}

ast_Expr * ast_LvalueArray :: getFirstExpr(){
    return this->firstExpr;
}

ast_Expr * ast_LvalueArray::getSecondExpr(){
    return this->secondExpr;
}

bool ast_LvalueArray::analizarExpr(Scope * scope){
    return true;
}


ScopeClass * ast_LvalueArray::obtenerTipoExpr(Scope * scope){
    return new ScopeClass(scope,new ast_ClassDecl(1,1,1,"","",new vector<string>(),new vector<ast_Field * >()));
}

//ast_Call

ast_Call::ast_Call(int linea, int columna, int tipoCall):ast_Expr(linea,columna,7){
    this->tipoCall = tipoCall;
}

int ast_Call::getTipoCall(){
    return this->tipoCall;
}







//ast_CallSimple

ast_CallSimple::ast_CallSimple(int linea,int columna, string ident, ast_Actuals * actuals): ast_Call(linea,columna,1){
    this->ident = ident;
    this->actuals = actuals;
}

string ast_CallSimple::getIdent(){
    return this->ident;
}

ast_Actuals * ast_CallSimple::getActuals(){
    return this->actuals;
}

bool ast_CallSimple::analizarExpr(Scope * scope){
    
    ScopeFunc * funcion = scope->obtenerFunc(ident);
    if(funcion == NULL){
        return false;
    }
    bool resultado = this->actuals->analizarActuals(scope,funcion,linea,columna);
    if(!resultado){
        errores = unirErrores(errores,actuals->getErrores());
        return false;
    }

    return true;
}

ScopeClass * ast_CallSimple::obtenerTipoExpr(Scope * scope){
    return new ScopeClass(scope,new ast_ClassDecl(1,1,1,"","",new vector<string>(),new vector<ast_Field * >()));
}


//ast_CallExpr

ast_CallExpr::ast_CallExpr(int linea,int columna,ast_Expr * expresion, string ident, ast_Actuals * actuals): ast_Call(linea,columna,2){
    this->expr = expresion;
    this->ident = ident;
    this->actuals = actuals;
}

ast_Expr * ast_CallExpr::getExpr(){
    return this->expr;
}

string ast_CallExpr::getIdent(){
    return this->ident;
}

ast_Actuals * ast_CallExpr::getActuals(){
    return this->actuals;
}

bool ast_CallExpr::analizarExpr(Scope * scope){
    ScopeClass * tipoExpresion = this->expr->obtenerTipoExpr(scope);
    std::stringstream linea;
    linea << (this->linea);
    std::stringstream columna;
    columna << (this->columna);
    if(!tipoExpresion->existeMetodo(this->ident)){
         this->errores->push_back("Error: la clase "+tipoExpresion->getClase()->getIdent() + "no tiene un metodo"+ this->ident+" en " + linea.str() + ":"+columna.str()) ;
         return false;
    }
    ScopeFunc * funcion = tipoExpresion->obtenerFunc(ident);
    bool resultado = this->actuals->analizarActuals(scope,funcion,this->linea,this->columna);
    if(!resultado){
        errores = unirErrores(errores,actuals->getErrores());
        return false;
    }
    return true;

} 

ScopeClass * ast_CallExpr::obtenerTipoExpr(Scope * scope){
    return new ScopeClass(scope,new ast_ClassDecl(1,1,1,"","",new vector<string>(),new vector<ast_Field * >()));
}

//ast_Actuals

ast_Actuals::ast_Actuals(vector<ast_Expr *> * expresiones){
    this->expresiones = expresiones;
}

vector<ast_Expr *> * ast_Actuals::getExpresiones(){
    return this->expresiones;
}

bool ast_Actuals::analizarActuals(Scope * scope, ScopeFunc * funcion,int numLinea,int numColumna){
    std::stringstream linea;
    linea << (numLinea);
    std::stringstream columna;
    columna << (numColumna);
    if(expresiones->size() == funcion->getFuncion()->getFormals()->getVariables()->size()){
        bool parametrosCorrectos = true;
        for(int i = 0; i < expresiones->size();i++){
            ast_Expr * expresion = expresiones->at(i);
            ScopeClass * tipoExpresion = (expresion->obtenerTipoExpr(scope));

            ast_Variable * variable = funcion->getFuncion()->getFormals()->getVariables()->at(i);

            string tipoVariable = variable->getTipo()->getIdent(); 

            if(!(tipoExpresion->getClase()->getIdent() == tipoVariable)){
                ScopeClass * claseParametro = scope->obtenerClase(tipoVariable);

               if(!claseParametro->isClaseHija(tipoExpresion)){
                   this->errores->push_back("Error: El parametro recibido no coincide con el tipo de "+ variable->getString()+ " en " + linea.str() + ":"+columna.str()) ;
               }
            }


        }
        if(!parametrosCorrectos){
            return false;
        }
    }
    else{
        this->errores->push_back("Error:El numero de parametros no coincide con la funcion "+funcion->getFuncion()->getIdent()+" en " + linea.str() + ":"+columna.str()) ;
        return false;
    }

    return true;
}

vector<string> * ast_Actuals::getErrores(){
    return errores;
}

//ast_Constant

ast_Constant::ast_Constant(int linea, int columna,int tipoConst):ast_Expr(linea,columna,8){
    this->tipoConst = tipoConst;
}

int ast_Constant::getTipoConst(){
    return tipoConst;
}

bool ast_Constant::analizarExpr(Scope *){
    return true;
}

ScopeClass * ast_Constant::obtenerTipoExpr(Scope * scope){
    return new ScopeClass(scope,new ast_ClassDecl(1,1,1,"","",new vector<string>(),new vector<ast_Field * >()));
}

//ast_IntConstant

ast_IntConstant::ast_IntConstant(int linea, int columna, int valor): ast_Constant(linea,columna,1){
    this->valor = valor;
}

int ast_IntConstant::getValor(){
    return this->valor;
}

//ast_DoubleConstant

ast_DoubleConstant::ast_DoubleConstant(int linea, int columna, double valor): ast_Constant(linea,columna,2){
    this->valor = valor;
}

double ast_DoubleConstant::getValor(){
    return this->valor;
}


//ast_BoolConstant

ast_BoolConstant::ast_BoolConstant(int linea, int columna, bool valor): ast_Constant(linea,columna,3){
    this->valor = valor;
}

bool ast_BoolConstant::getValor(){
    return this->valor;
}

//ast_StringConstant

ast_StringConstant::ast_StringConstant(int linea, int columna, string valor): ast_Constant(linea,columna,4){
    this->valor = valor;
}

string ast_StringConstant::getValor(){
    return this->valor;
}


//ast_NullConstant

ast_NullConstant::ast_NullConstant(int linea, int columna): ast_Constant(linea,columna,5){
}


//Scope

Scope::Scope(int tipoScope,Scope * padre){
    this->tipoScope = tipoScope;
    this->padre = padre;
    this->scopeValido = true;
    this->scopesHijos =  new std::vector<Scope *>();
    this->errores = new std::vector<string>();
}

int Scope::getTipoScope(){
    return this->tipoScope;
}


Scope * Scope::getPadre(){
    return this->padre;
}

vector<Scope *> * Scope::getHijos(){
    return this->scopesHijos;
}

bool Scope::isScopeValido(){
    return this->scopeValido;
}

vector<string> * Scope::getErrores(){
    return errores;
}

void Scope::setScopeValido(bool b){
    this->scopeValido = b;
}

//ScopeProgram

ScopeProgram::ScopeProgram(ast_Programa * programa):Scope(1,NULL){
    this->errores =  new std::vector<string>();
    this->variables = new std::vector<ScopeVar *>();
    this->funciones = new std::vector<ScopeFunc *>();
    this->clases = new std::vector<ScopeClass *>();
    this->programa = programa;
}

ast_Programa * ScopeProgram::getPrograma(){
    return this->programa;
}


vector<ScopeVar * >* ScopeProgram::getVariables(){
    return this->variables;
}

vector<ScopeFunc *> * ScopeProgram::getFunciones(){
    return this->funciones;
}

vector<ScopeClass *> * ScopeProgram::getClases(){
    return this->clases;
}

bool ScopeProgram::analizarArbol(){
    std::vector<ast_Declaracion *>  declaraciones = (*this->programa->getDeclaraciones());
    scopeValido = true;
    for(int i = 0; i < declaraciones.size();i++){
        ast_Declaracion * declaracion = declaraciones.at(i);

        ast_VariableDecl * newVarDecl;
        ScopeVar * newVariable;
        ast_FunctionDecl * newFunDecl;
        ScopeFunc * newFunc;
        ast_ClassDecl * newClassDecl;
        ScopeClass * newClass;
        switch (declaracion->getTipo())
        {
        case 1:
            newVarDecl = (ast_VariableDecl *) declaracion;
            newVariable = new ScopeVar(this,newVarDecl);
            (*this->variables).insert((*this->variables).begin(),newVariable);
            break;
        case 2:
            newFunDecl = (ast_FunctionDecl *) declaracion;
            
            newFunc = new ScopeFunc(this,newFunDecl);
             (*this->funciones).insert((*this->funciones).begin(),newFunc);
            break;
        case 3:
            newClassDecl = (ast_ClassDecl *) declaracion;
            newClass = new ScopeClass(this,newClassDecl);
             (*this->clases).push_back(newClass);
        
        default:
            
            break;
        }
       



       
    }

     cout<<"Analizando clases "<<endl;
        for(int j = 0; j < (*this->clases).size();j++){
            ScopeClass * clase = clases->at(j);
            cout<<"Analizando clase "<<clase->getClase()->getIdent()<<endl;
            if(clase->analizarClase()){
                cout<<"Formato de clase correcto"<<endl;
            }
            else{
                cout<<"Formato de clase inccorrecto"<<endl;
                this->errores = unirErrores(errores,clase->getErrores());
                scopeValido = false;
            }
        }
        cout<<"Analizando funciones "<<endl;
        
        for(int m = 0; m < (*this->funciones).size();m++){
            ScopeFunc * funcion = funciones->at(m);
            cout<<"Analizando funcion "<<funcion->getFuncion()->getIdent()<<endl;
             if(funcion->analizarFunc()){
                cout<<"Formato de funcion correcto"<<endl;
            }
            else{
                cout<<"Formato de funcion inccorrecto"<<endl;
                this->errores = unirErrores(errores,funcion->getErrores());
                scopeValido = false;
            }
            
        }
        cout<<"Analizando variables "<<endl;
        for(int n = 0; n < (*this->variables).size();n++){
            ScopeVar * variable = variables->at(n);
            cout<<"Analizando variable "<<variables->at(n)->getVariable()->getVar()->getString()<<endl;
             if(variable->analizarVar()){
                cout<<"Formato de variable correcto"<<endl;
            }
            else{
                cout<<"Formato de variable inccorrecto"<<endl;
                this->errores = unirErrores(errores,variable->getErrores());
                scopeValido = false;
            }

        }
        
    return scopeValido;
}

bool ScopeProgram::identRepetido(string ident){
    int contador = 0;
    for(int i = 0; i< this->variables->size();i++){
        ScopeVar * variable = this->variables->at(i);
          
    
        if(variable->getVariable()->getVar()->getString() == ident){
            contador++;
        }
    }
    for(int i = 0; i< this->clases->size();i++){
      
        ScopeClass * clase = clases->at(i);
        if(clase->getClase()->getIdent() == ident){
             contador++;
        }
    }
    for(int i = 0; i< (*this->funciones).size();i++){
        ScopeFunc * funcion = funciones->at(i);
        if(funcion->getFuncion()->getIdent() == ident){
             contador++;
        }
    }

    
    if(contador > 1){
        return true;
    }
    return false;
}

bool ScopeProgram::existeIdent(string ident){
    for(int i = 0; i< this->variables->size();i++){
        ScopeVar * variable = this->variables->at(i);
          
    
        if(variable->getVariable()->getVar()->getString() == ident){
            return true;
        }
    }
    for(int i = 0; i< this->clases->size();i++){
      
        ScopeClass * clase = clases->at(i);
        if(clase->getClase()->getIdent() == ident){
              return true;
        }
    }
    for(int i = 0; i< (*this->funciones).size();i++){
        ScopeFunc * funcion = funciones->at(i);
        if(funcion->getFuncion()->getIdent() == ident){
              return true;
        }
    }

    
    return false;
}

ScopeClass * ScopeProgram::obtenerClase(string identClase){
    for(int i = 0; i < (*this->clases).size();i++){
        if((this->clases->at(i)->getClase()->getIdent()) == identClase){
            return (this->clases->at(i));
        }
    }
    return NULL;
}

ScopeFunc * ScopeProgram::obtenerFunc(string identFunc){
     for(int i = 0; i < (*this->funciones).size();i++){
        if((this->funciones->at(i)->getFuncion()->getIdent()) == identFunc){
            return (this->funciones->at(i));
        }
    }
    return NULL;
}

//ScopeFunc

ScopeFunc::ScopeFunc(Scope * padre, ast_FunctionDecl * funcion):Scope(2,padre){
    
    this->funcion = funcion;
   
    this->variables = new std::vector<ScopeVar *>();
    this->tipoExistente = true;
}

ast_FunctionDecl * ScopeFunc::getFuncion(){
    return this->funcion;
}

vector<ScopeVar *> * ScopeFunc::getVariables(){
    return this->variables;
}

bool ScopeFunc::isTipoExistente(){
    return tipoExistente;
}

bool ScopeFunc::analizarFunc(){
    ast_Type * tipo = this->getFuncion()->getTipoFuncion();
    string ident = this->getFuncion()->getIdent();
    std::stringstream linea;
        linea << (this->getFuncion()->getLinea());
        std::stringstream columna;
        columna << (this->getFuncion()->getColumna());
    //Verificar tipo exitente
    if(tipo->getTipo() == 6){
        this->tipoRetorno = this->padre->obtenerClase(tipo->getIdent());

        if(tipoRetorno == NULL){
            (*this->errores).push_back("Error : el tipo " + tipo->getIdent() + " no existe en " + linea.str() + ":" + columna.str());
           scopeValido = false;
        }
        
    }
    //Verificar nombre repetido
    if((*this->padre).identRepetido(ident)){
        
        (*this->errores).push_back("Error : declaracion previa de " + ident + " en " + linea.str() + ":" + columna.str());
        scopeValido = false;
    }

    //Analizar parametros
    listaParametros = new std::vector<string>();
    for(int i = 0; i < this->getFuncion()->getFormals()->getVariables()->size() ;i++){
        
        ast_Variable * parametro = this->getFuncion()->getFormals()->getVariables()->at(i);
        int resultado = parametro->analizarVariable(listaParametros,this);

        if(resultado != 0){
            this->errores->push_back(parametro->getError());
            scopeValido = false;
        }
    
        listaParametros->push_back(parametro->getString());
    
    }


    //Pasar ast_VarDecl a ScopeVar

    for(int i = 0; i < this->funcion->getStmtBlock()->getContent()->size();i++ ){
        ast_StmtOrVariableDecl * stmtOrDecl = this->funcion->getStmtBlock()->getContent()->at(i);
        if (stmtOrDecl->getTipo() == 2){
            variables->push_back(new ScopeVar(this,stmtOrDecl->getVariableDecl()));
        }

    }

    //Analizar variables
    for(int i = 0; i < this->variables->size();i++){
        ScopeVar * variable =  this->variables->at(i);
        bool resultado = variable->analizarVar();
        if(!resultado){
            errores = unirErrores(errores,variable->getErrores());
            this->scopeValido = false;
        }

        for(int i = 0; i < listaParametros->size(); i++){
            if(listaParametros->at(i) == variable->getVariable()->getVar()->getString()){
                this->scopeValido = false;
                  (*this->errores).push_back("Error : declaracion previa de " + listaParametros->at(i) + " en " + linea.str() + ":" + columna.str());
            }
        }
    }

    //Falta analizar Stmts
    for(int i = 0; i < this->funcion->getStmtBlock()->getContent()->size();i++ ){
        
        ast_StmtOrVariableDecl * stmtOrDecl = this->funcion->getStmtBlock()->getContent()->at(i);
        if (stmtOrDecl->getTipo() == 1){
            cout<<"Entre analizar stmt"<<endl;
            ast_Stmt * stmt =  stmtOrDecl->getStmt();
            cout<<"Tengo el stmt"<<endl;
            if(!stmt->analizarStmt(this)){
                cout<<"Logre analizarlo"<<endl;
                scopeValido = false;
                errores = unirErrores(errores,stmt->getErrores());
                cout<<"Erores reportados"<<endl;
            }
           
        }

    }
    return this->scopeValido;
}

bool ScopeFunc::identRepetido(string ident){
    int cantidad = 0;
    for(int i = 0; i< (*this->variables).size();i++){
        if((*(*this->variables).at(i)).identRepetido(ident)){
            cantidad++;
        }
    }
    if(cantidad >1 ){
        return true;
    }
    return false;
}

bool ScopeFunc::existeIdent(string ident){
    for(int i = 0; i< (*this->variables).size();i++){
        if((*(*this->variables).at(i)).identRepetido(ident)){
            return true;
        }
    }
    return false;
}

ScopeClass * ScopeFunc::getTipoRetorno(){
    return this->tipoRetorno;
}

ScopeClass * ScopeFunc::obtenerClase(string identClase){
    return this->padre->obtenerClase(identClase);
}

ScopeFunc * ScopeFunc::obtenerFunc(string identFunc){
    if(this->getFuncion()->getIdent() == identFunc){
        return this;
    }
    return this->padre->obtenerFunc(identFunc);
}

vector<string> * ScopeFunc::getListaParametros(){
    return this->listaParametros;
}


//ScopeClass 

ScopeClass::ScopeClass(Scope * padre,ast_ClassDecl * clase): Scope(3,padre){
    this-> clase = clase;
    this-> variables = new std::vector<ScopeVar *>();
    this->funciones = new std::vector<ScopeFunc *>();
}

ast_ClassDecl * ScopeClass::getClase(){
    return clase;
}

vector<ScopeVar *> * ScopeClass::getVariables(){
    return variables;
}

vector<ScopeFunc *> * ScopeClass::getFunciones(){
    return funciones;
}

ScopeClass * ScopeClass :: getClasePadre(){
    return clasePadre;
}

bool ScopeClass::analizarClase(){
    std::stringstream linea;
    linea << (this->getClase()->getLinea());
    std::stringstream columna;
    columna << (this->getClase()->getColumna());
    ast_ClassDecl * clase  = (*this).getClase();
    string ident = (*clase).getIdent();
    scopeValido = true;
    if(this->padre->identRepetido(ident)){
        (*this->errores).push_back("Error : declaracion previa de " + ident + " en " + linea.str() + ":" +columna.str());

        scopeValido = false;
    }


    string nombreClasePadre = (*clase).getExtenteds();
   
    if(nombreClasePadre != ""){
        if (ident != nombreClasePadre){
            ScopeProgram * scopePadre = (ScopeProgram *) (this->padre);
            ScopeClass * clasePadre = (*scopePadre).obtenerClase(nombreClasePadre);
            if (clasePadre != NULL){
                this->clasePadre = clasePadre;
            }
            else{
                (*this->errores).push_back("Error : la clase " + nombreClasePadre + " no existe " + " en " + linea.str() + ":" +columna.str());
                scopeValido = false;
            }
        }
        else {
            (*this->errores).push_back("Error : la clase " + ident + " no puede heredar de si misma " + " en " + linea.str() + ":" +columna.str() );
            scopeValido = false;
        }
    }


    //Transformar classDecl a ScopeClass

    for(int i = 0; i < clase->getFields()->size(); i++){
        ast_Field * field = clase->getFields()->at(i);

        if(field->getTipoDecl() == 1){
            this->variables->push_back(new ScopeVar(this,field->getVariableDecl()));
        }
        else{
            this->funciones->push_back(new ScopeFunc(this,field->getFunctionDecl()));
        }
    }
    //Verificar variables correctas
    for(int i = 0; i < this->getVariables()->size() ; i++){
        ScopeVar * variable = variables->at(i);
        bool resultado = variable->analizarVar();
        if(!resultado){
            errores = unirErrores(errores,variable->getErrores());
            this->scopeValido = false;
        }
    }


    //Verificar funciones correctas
    for(int i = 0; i < this->getFunciones()->size() ; i++){
        ScopeFunc * funcion = funciones->at(i);
       bool resultado = funcion->analizarFunc();
       if(!resultado){
           errores = unirErrores(errores,funcion->getErrores());
           this->scopeValido = false;
       }
    }

    

    
    if(!scopeValido){
        this->padre->setScopeValido(false);
    }

    return scopeValido;
}


bool ScopeClass::identRepetido(string ident){
    int cantidad = 0;
    for(int i = 0; i< (*this->variables).size();i++){
        if((*(*this->variables).at(i)).identRepetido(ident)){
            cantidad++;
        }
    }
    for(int i = 0; i< (*this->funciones).size();i++){
        if((*(*this->funciones).at(i)).identRepetido(ident)){
            cantidad++;
        }
    }

    if(cantidad > 1){
        return true;
    }
    return false;
}

bool ScopeClass::existeIdent(string ident){
    for(int i = 0; i< (*this->variables).size();i++){
        if((*(*this->variables).at(i)).identRepetido(ident)){
           return true;
        }
    }
    for(int i = 0; i< (*this->funciones).size();i++){
        if((*(*this->funciones).at(i)).identRepetido(ident)){
            return true;
        }
    }

    return false;
}


ScopeClass * ScopeClass::obtenerClase(string identClase){
    if(clase->getIdent() == identClase){
        return this;
    }
    return this->padre->obtenerClase(identClase);
}

bool ScopeClass::isClaseHija(ScopeClass* posibleParametro){
     for(int i = 0; i < this->getClasesHijas()->size();i++){
        ScopeClass * claseHija = this->getClasesHijas()->at(i);
        if(posibleParametro->getClase()->getIdent() == claseHija->getClase()->getIdent()){
            return true;
        }
        else{
            claseHija->isClaseHija(posibleParametro);
        }

        }
    return false;
}

ScopeFunc * ScopeClass::obtenerFunc(string identFunc){
    if(this->existeMetodo(identFunc)){
        for(int i = 0;i < funciones->size() ;i++){
            ScopeFunc * funcion = funciones->at(i);

            if(funcion->getFuncion()->getIdent() == identFunc){
                return funcion;
            } 
        }
    }
    return padre->obtenerFunc(identFunc);
}

bool ScopeClass::isTipoPrimitivo(){
    return tipoPrimitivo;
}

bool ScopeClass::existeVariable(string identVar){
    for(int i = 0 ; i < variables->size(); i++){
        ScopeVar * variable = variables->at(i);
        if(variable->getVariable()->getVar()->getString() == identVar){
            return true;
        }
    }

    return false;
}

bool ScopeClass::existeMetodo(string identMetodo){
    for(int i = 0 ; i < funciones->size(); i++){
        ScopeFunc * funcion = funciones->at(i);
        if(funcion->getFuncion()->getIdent( ) == identMetodo){
            return true;
        }
    }

    return false;
}

vector<ScopeClass * > * ScopeClass::getClasesHijas(){
    return clasesHijas;
}




//ScopeVar

ScopeVar::ScopeVar(Scope * padre, ast_VariableDecl * variable):Scope(4,padre){
    this->variable = variable;

}

ast_VariableDecl * ScopeVar::getVariable(){
    return this->variable;
}

bool ScopeVar::isTipoExistente(){
    return this->tipoExistente;
}

bool ScopeVar::analizarVar(){
    ast_Variable* variable = this->getVariable()->getVar();
    scopeValido = true;
    std::stringstream linea;
    linea << (this->getVariable()->getLinea());
    std::stringstream columna;
    columna << (this->getVariable()->getColumna());
    //Declaracion previa
    if(this->padre->identRepetido(variable->getString())){
        (*this->errores).push_back("Error : declaracion previa de " + variable->getString() + " en " + linea.str() + ":" +columna.str());
        scopeValido = false;
    }

    //Tipo existente
    int resultado = variable->analizarVariable(new vector<string>(),this);
    if(resultado != 0){
            this->errores->push_back(variable->getError());
            scopeValido = false;
    }
    

    return scopeValido;
}



       

bool ScopeVar::identRepetido(string ident){
    if(this->variable->getVar()->getString() == ident ){
      return true;  
    }
    return false;
}

bool ScopeVar::existeIdent(string ident){
    if(this->variable->getVar()->getString() == ident ){
      return true;  
    }
    return false;
}

ScopeClass * ScopeVar::obtenerClase(string identClase){
    return this->padre->obtenerClase(identClase);
}

ScopeFunc * ScopeVar::obtenerFunc(string identFunc){
    return this->padre->obtenerFunc(identFunc);
}

vector<string> * unirErrores(vector<string> * primeraLista,vector<string> * segundaLista){

    for(int i = 0; i < segundaLista->size();i++){
        primeraLista->push_back(segundaLista->at(i));
    }

    return primeraLista;
}

bool exiteIdent(Scope * scope, string ident){
    if(scope->existeIdent(ident)){
        return true;
    }
    if(scope->getPadre() != NULL){
        return exiteIdent(scope->getPadre(),ident);
    }
    return false;

}
