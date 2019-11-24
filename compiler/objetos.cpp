#include "objetos.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

//PROGRAMA

ast_Programa::ast_Programa(vector<ast_Declaracion *> * Declaraciones){
    this->declaraciones=Declaraciones;
}

vector<ast_Declaracion *> * ast_Programa::getDeclaraciones()
{
    return this->declaraciones;
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

//TYPES
ast_Type::ast_Type(int numTipoDato ,bool array){
    this->tipoDato=numTipoDato;
    this->isArray=array;
}
ast_Type::ast_Type(int numTipoDato,bool array,string ident){
    this->tipoDato=numTipoDato;
    this->isArray=array;
    this->ident=ident;
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
    this->tipoStmt = linea;
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

//ast_StmtBase

ast_StmtBase::ast_StmtBase(int linea,int columna,ast_Expr * expresion):ast_Stmt(linea,columna,1){
    this->expresion = expresion;
}

ast_Expr * ast_StmtBase::getExpresion(){
    return this->expresion;
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

//ast_BreakStmt

ast_BreakStmt::ast_BreakStmt(int linea, int columna):ast_Stmt(linea,columna,6){

}

//ast_PrintStmt

ast_PrintStmt::ast_PrintStmt(int linea,int columna,vector<ast_Expr *> * expresiones):ast_Stmt(linea,columna,7){
    this->expresiones = expresiones;
}

vector<ast_Expr *> * ast_PrintStmt::getExpresiones(){
    return this->expresiones;
}

//ast_StmtBlock

ast_StmtBlock:: ast_StmtBlock(int linea, int columna,vector<ast_StmtOrVariableDecl *> * content):ast_Stmt(linea,columna,8){
    this->content = content;
 
}

vector<ast_StmtOrVariableDecl *> * ast_StmtBlock::getContent(){
    return this-> content;
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




//ast_Expr

ast_Expr::ast_Expr(int linea,int columna, int tipo){
    this-> linea = linea;
    this-> columna = columna;
    this-> tipoExpr = tipo;
    this-> isNullExpr = false;
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

//ast_ExprRead

ast_ExprRead::ast_ExprRead(int linea,int columna,int tipoRead):ast_Expr(linea,columna,3){
    this->tipoRead = tipoRead;
}

int ast_ExprRead::getTipoRead(){
    return tipoRead;
}

//ast_ExprNew

ast_ExprNew::ast_ExprNew(int linea,int columna,string ident):ast_Expr(linea,columna,4){
    this->ident = ident;
}

string ast_ExprNew::getIdent(){
    return this->ident;
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

//Lvalue

ast_LValue::ast_LValue(int linea, int columna, int tipoLValue):ast_Expr(linea,columna,6){
    this->tipoLvalue = tipoLValue;
}

int ast_LValue::getTipoLvalue(){
    return this->tipoLvalue;
}

//ast_LValueSimple

ast_LValueSimple::ast_LValueSimple(int linea,int columna, string ident):ast_LValue(linea,columna,1){
    this->ident = ident;

}

string ast_LValueSimple::getIdent(){
    return this->ident;
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


//ast_Actuals

ast_Actuals::ast_Actuals(vector<ast_Expr *> * expresiones){
    this->expresiones = expresiones;
}

vector<ast_Expr *> * ast_Actuals::getExpresiones(){
    return this->expresiones;
}

//ast_Constant

ast_Constant::ast_Constant(int linea, int columna,int tipoConst):ast_Expr(linea,columna,8){
    this->tipoConst = tipoConst;
}

int ast_Constant::getTipoConst(){
    return tipoConst;
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


















