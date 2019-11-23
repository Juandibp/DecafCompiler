#include "objetos.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

//PROGRAMA

Programa::Programa(vector<Declaracion *> * Declaraciones){
    this->declaraciones=Declaraciones;
}

vector<Declaracion *> * Programa::getDeclaraciones()
{
    return this->declaraciones;
}

//DECLARACIOn

Declaracion::Declaracion(int linea, int columna, int tipo){
    this->linea=linea;
    this->columna=columna;
    this->tipoDeclaracion=tipo;
}

int Declaracion::getLinea(){
    return this->linea;
}

int Declaracion::getColumna(){
    return this->columna;
}

int Declaracion::getTipo(){
    return this->tipoDeclaracion;
}

//VARIABLES

VariableDecl::VariableDecl(int linea, int columna, int tipo,Variable* var): Declaracion(linea,columna,tipo){
    this->linea=linea;
    this->columna=columna;
    this->tipoDeclaracion=tipo;
    this ->var=var;
}

Variable * VariableDecl::getVar(){
    return this->var;
}

Variable::Variable(Type* tipo, string ident){
    this->tipo=tipo;
    this->ident=ident;
}

Type * Variable::getTipo(){
    return this->tipo;
}

string Variable::getString(){
    return this->ident;
}

//TYPES
Type::Type(TipoDatos tipo ,bool array){
    this->tipo=tipo;
    this->isArray=array;
}
Type::Type(TipoDatos tipo,bool array,string ident){
    this->tipo=tipo;
    this->isArray=array;
    this->ident=ident;
}

TipoDatos Type::getTipo(){
    return this->tipo;
}

bool Type::getIsArray(){
    return this->isArray;
}

string Type::getIdent(){
    return this->ident;
}

//FunctionDecl

FunctionDecl::FunctionDecl(int linea,int columna,int tipoDecl,Type * tipoFunc, string ident, Formals * formals, StmtBlock * stmtBlock): Declaracion(linea,columna,tipoDecl){
    this->linea=linea;
    this->columna=columna;
    this->tipoDeclaracion=tipoDecl;
    this->tipoFunc = tipoFunc; 
    this->ident = ident; 
    this->formals = formals;
    this->stmtBlock = stmtBlock;  
}

Type * FunctionDecl::getTipoFuncion(){
    return this->tipoFunc;
}

string FunctionDecl::getIdent(){
    return this->ident;
}

Formals * FunctionDecl::getFormals(){
    return this->formals;
}

StmtBlock * FunctionDecl::getStmtBlock(){
    return this->stmtBlock;
}

//Formals

Formals::Formals(vector<Variable *> * variables){
    this->variables = variables;
}

vector<Variable *> * Formals::getVariables(){
    return this->variables;
}

//ClassDecl

ClassDecl::ClassDecl(int linea,int columna,int tipoDecl,string ident,vector<string> * extends, vector<string> * implements, vector<Field *> * fields):Declaracion(linea,columna,tipoDecl){
    this->linea=linea;
    this->columna=columna;
    this->tipoDeclaracion=tipoDecl;
    this->ident = ident; 
    this->extends = extends;
    this->implements = implements;
    this->fields = fields; 
}

string ClassDecl::getIdent(){
    return this-> ident;
}

vector<string> * ClassDecl::getExtenteds(){
    return this-> extends;
}

vector<string> * ClassDecl::getImplements(){
    return this-> implements;
}

vector<Field *> * ClassDecl::getFields(){
    return this-> fields;
}

//Field

Field::Field(VariableDecl* varDecl){
    this->tipoDeclracion = 1;
    this->variableDecl = varDecl;
}

Field::Field(FunctionDecl* funDecl){
    this->tipoDeclracion = 2;
    this->functionDecl = funDecl;
}

int Field::getTipoDecl(){
    return this->tipoDeclracion;
}

VariableDecl * Field::getVariableDecl(){
    return this->variableDecl;
}

FunctionDecl * Field::getFunctionDecl(){
    return this->functionDecl;
}

//InterfaceDecl

InterfaceDecl::InterfaceDecl(int linea,int columna,int tipoDecl, string ident, vector<Prototype *> * prototypes): Declaracion(linea,columna,tipoDecl){
    this->linea=linea;
    this->columna=columna;
    this->tipoDeclaracion=tipoDecl;
    this->ident = ident;
    this->prototypes = prototypes;    
}

string InterfaceDecl::getIdent(){
    return this->ident;
}

vector<Prototype *> * InterfaceDecl::getPrototype(){
  return this->prototypes;  
}

//Prototype

Prototype::Prototype(Type * tipo, string ident,Formals * formals){
    this->tipo = tipo;
    this->ident = ident;
    this->formals = formals;
}

Type * Prototype::getTipo(){
    return this->tipo;
}

string Prototype::getIdent(){
    return this->ident;
}

Formals * Prototype::getFormals(){
    return this->formals;
}

//Stmt

Stmt::Stmt(int linea, int columna, int tipo){
    this->linea = linea;
    this->columna = columna;
    this->tipoStmt = linea;
}

int Stmt::getLinea(){
    return this->linea;
}

int Stmt::getColumna(){
    return this->columna;
}

int Stmt::getTipoStmt(){
    return this->tipoStmt;
}

//StmtBase

StmtBase::StmtBase(int linea,int columna,Expr * expresion):Stmt(linea,columna,1){
    this->expresion = expresion;
}

Expr * StmtBase::getExpresion(){
    return this->expresion;
}

//IfStmt

IfStmt::IfStmt(int linea,int columna,Expr * expresion,Stmt * stmt, Stmt * elseStmt):Stmt(linea,columna,2){
    this->expresion = expresion;
    this->stmt = stmt;
    this->haveElse = true;
    this->elseStmt =elseStmt;

}

IfStmt::IfStmt(int linea,int columna,Expr * expresion,Stmt * stmt):Stmt(linea,columna,2){
    this->expresion = expresion;
    this->stmt = stmt;
    this->haveElse = false;

}

Expr * IfStmt::getExpresion(){
    return this->expresion;
}


Stmt * IfStmt ::getStmt(){
    return this->stmt;
}

bool IfStmt ::getHaveElse(){
    return this->haveElse;
}

Stmt * IfStmt ::getElseStmt(){
    return this->elseStmt;
}

//WhileStmt

WhileStmt::WhileStmt(int linea, int columna,Expr * expresion, Stmt* stmt):Stmt(linea,columna,3){
    this->expresion = expresion;
    this->stmt = stmt;
}

Expr * WhileStmt::getExpresion(){
    return this->expresion;
}

Stmt * WhileStmt::getStmt(){
    return this->stmt;
}

//ForStmt

ForStmt::ForStmt(int linea, int columna, Expr * firstExpr, Expr * secondExpr,Expr * thirdExpresion,Stmt * stmt): Stmt(linea,columna,4){
    this->firstExpr = firstExpr;
    this->haveFirstExpr = true;

    this->secondExpr = secondExpr;
    this->haveSecondExpr = true;

    this->thirdExpr = thirdExpr;
    this->haveThirdExpr = true;

    this->stmt = stmt;

}

ForStmt::ForStmt(int linea, int columna, Expr * firstExpr, Expr * secondExpr,Stmt * stmt): Stmt(linea,columna,4){
    this->firstExpr = firstExpr;
    this->haveFirstExpr = true;

    this->secondExpr = secondExpr;
    this->haveSecondExpr = true;

    this->haveThirdExpr = false;

    this->stmt = stmt;

}

ForStmt::ForStmt(int linea, int columna, Expr * firstExpr,Stmt * stmt): Stmt(linea,columna,4){
    this->firstExpr = firstExpr;
    this->haveFirstExpr = true;

    this->haveSecondExpr = false;

    this->haveThirdExpr = false;

    this->stmt = stmt;

}

ForStmt::ForStmt(int linea, int columna,Stmt * stmt): Stmt(linea,columna,4){
    this->haveFirstExpr = false;

    this->haveSecondExpr = false;

    this->haveThirdExpr = false;

    this->stmt = stmt;

}

Expr * ForStmt::getFirstExpr(){
    return this->firstExpr;
}

Expr * ForStmt::getSecondExpr(){
    return this->secondExpr;
}

Expr * ForStmt::getThirdExpr(){
    return this->thirdExpr;
}

bool ForStmt::getHaveFirstExpr(){
    return this->haveFirstExpr;
}

bool ForStmt::getHaveSecondExpr(){
    return this->getHaveSecondExpr;
}

bool ForStmt::getHaveThirdExpr(){
    return this->getHaveThirdExpr;
}

Stmt * ForStmt::getStmt(){
    return this->stmt;
}


//ReturnStmt

ReturnStmt::ReturnStmt(int linea, int columna, Expr * expresion): Stmt(linea,columna,5){
    this->expresion = expresion;
    this->haveExpr = true;
}

ReturnStmt::ReturnStmt(int linea, int columna): Stmt(linea,columna,5){
    this->haveExpr = false;
}


Expr * ReturnStmt::getExpresion(){
    return this->expresion;
}

bool ReturnStmt::getHaveExpr(){
    return this->haveExpr;
}

//BreakStmt

BreakStmt::BreakStmt(int linea, int columna):Stmt(linea,columna,6){

}

//PrintStmt

PrintStmt::PrintStmt(int linea,int columna,vector<Expr *> * expresiones):Stmt(linea,columna,7){
    this->expresiones = expresiones;
}

vector<Expr *> * PrintStmt::getExpresiones(){
    return this->expresiones;
}

//StmtBlock

StmtBlock:: StmtBlock(int linea, int columna,vector<VariableDecl *> * variableDecls,vector<Stmt *> * stmts):Stmt(linea,columna,8){
    this->variableDecls = variableDecls;
    this->stmts = stmts; 
}

vector<VariableDecl *> * StmtBlock::getVariableDecls(){
    return this-> variableDecls;
}

vector<Stmt *> * StmtBlock::getStmts(){
    return this->stmts;
}

//Expr

Expr::Expr(int linea,int columna, int tipo){
    this-> linea = linea;
    this-> columna = columna;
    this-> tipoExpr = tipo;
}

int Expr::getLinea(){
    return this->linea;
}

int Expr::getColumna(){
    return this->columna;
}

int Expr::getTipoExpr(){
    return this->tipoExpr;
}

//ExprBinary

ExprBinary::ExprBinary(int linea,int columna,Expr * exprIzq, Expr * exprDer, TipoOperacion tipoOp):Expr(linea,columna,1){
    this->exprIzq = exprIzq;
    this->exprDer = exprDer;
    this->tipoOp = tipoOp;
}

Expr * ExprBinary::getExprIzq(){
    return this->exprIzq;
}

Expr * ExprBinary::getExprDer(){
    return this->exprDer;
}

TipoOperacion ExprBinary::getTipoOp(){
    return this->tipoOp;
}

//ExprUnary

ExprUnary::ExprUnary(int linea, int columna, Expr * expresion,TipoOperacion tipoOp):Expr(linea,columna,2){
    this->expresion = expresion;
    this->tipoOp= tipoOp;
}

Expr * ExprUnary::getExpresion(){
    return this->expresion;
}

TipoOperacion ExprUnary::getTipoOp(){
    return this->tipoOp;
}

//ExprRead

ExprRead::ExprRead(int linea,int columna,int tipoRead):Expr(linea,columna,3){
    this->tipoRead = tipoRead;
}

int ExprRead::getTipoRead(){
    return tipoRead;
}

//ExprNew

ExprNew::ExprNew(int linea,int columna,string ident):Expr(linea,columna,4){
    this->ident = ident;
}

string ExprNew::getIdent(){
    return this->ident;
}

//ExprNewArrray

ExprNewArray::ExprNewArray(int linea, int columna, Expr * expresion, TipoDatos tipoDato):Expr(linea,columna,5){
    this->expresion = expresion;
    this->tipoDato = tipoDato;
}

Expr * ExprNewArray::getExpresion(){
    return this->expresion;
}

TipoDatos ExprNewArray::getTipoDatos(){
    return this->tipoDato;
}

//Lvalue

LValue::LValue(int linea, int columna, int tipoLValue):Expr(linea,columna,6){
    this->tipoLvalue = tipoLValue;
}

int LValue::getTipoLvalue(){
    return this->tipoLvalue;
}

//LValueSimple

LValueSimple::LValueSimple(int linea,int columna, string ident):LValue(linea,columna,1){
    this->ident = ident;

}

string LValueSimple::getIdent(){
    return this->ident;
}

//LvalueExpr

LvalueExpr::LvalueExpr(int linea, int columna, Expr * expresion, string ident):LValue(linea,columna,2){
    this->expresion = expresion;
    this->ident = ident;
}

Expr * LvalueExpr:: getExpr(){
    return this-> expresion;
}

string LvalueExpr::getIdent(){
    return this->ident;
}

//LvalueArray

LvalueArray::LvalueArray(int linea, int columna,Expr * firstEXpr, Expr* secondExpr):LValue(linea,columna,3){
    this->firstExpr = firstEXpr;
    this->secondExpr = secondExpr;
}

Expr * LvalueArray :: getFirstExpr(){
    return this->firstExpr;
}

Expr * LvalueArray::getSecondExpr(){
    return this->secondExpr;
}


//Call

Call::Call(int linea, int columna, int tipoCall):Expr(linea,columna,7){
    this->tipoCall = tipoCall;
}

int Call::getTipoCall(){
    return this->tipoCall;
}


//CallSimple

CallSimple::CallSimple(int linea,int columna, string ident, Actuals * actuals): Call(linea,columna,1){
    this->ident = ident;
    this->actuals = actuals;
}

string CallSimple::getIdent(){
    return this->ident;
}

Actuals * CallSimple::getActuals(){
    return this->actuals;
}

//CallExpr

CallExpr::CallExpr(int linea,int columna,Expr * expresion, string ident, Actuals * actuals): Call(linea,columna,2){
    this->expr = expresion;
    this->ident = ident;
    this->actuals = actuals;
}

Expr * CallExpr::getExpr(){
    return this->expr;
}

string CallExpr::getIdent(){
    return this->ident;
}

Actuals * CallExpr::getActuals(){
    return this->actuals;
}


//Actuals

Actuals::Actuals(vector<Expr *> * expresiones){
    this->expresiones = expresiones;
}

vector<Expr *> * Actuals::getExpresiones(){
    return this->expresiones;
}

//Constant

Constant::Constant(int linea, int columna,int tipoConst):Expr(linea,columna,8){
    this->tipoConst = tipoConst;
}

int Constant::getTipoConst(){
    return tipoConst;
}


//IntConstant

IntConstant::IntConstant(int linea, int columna, int valor): Constant(linea,columna,1){
    this->valor = valor;
}

int IntConstant::getValor(){
    return this->valor;
}

//DoubleConstant

DoubleConstant::DoubleConstant(int linea, int columna, double valor): Constant(linea,columna,2){
    this->valor = valor;
}

double DoubleConstant::getValor(){
    return this->valor;
}


//BoolConstant

BoolConstant::BoolConstant(int linea, int columna, bool valor): Constant(linea,columna,3){
    this->valor = valor;
}

bool BoolConstant::getValor(){
    return this->valor;
}

//StringConstant

StringConstant::StringConstant(int linea, int columna, string valor): Constant(linea,columna,4){
    this->valor = valor;
}

string StringConstant::getValor(){
    return this->valor;
}


//NullConstant

NullConstant::NullConstant(int linea, int columna): Constant(linea,columna,5){
}


















