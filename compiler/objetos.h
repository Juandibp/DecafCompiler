#ifndef _H
#define _H

#include <cstdlib>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

class ast_Programa;
class ast_Declaracion;
class ast_VariableDecl;
class ast_Variable;
class ast_Type;
class ast_FunctionDecl;
class ast_Formals;
class ast_ClassDecl;
class ast_TokenClass;
class ast_Field;
class ast_InterfaceDecl;
class ast_Prototype;
class ast_Stmt;
class ast_StmtBlock;
class ast_StmtBase;
class ast_IfStmt;
class ast_ElseStmt;
class ast_WhileStmt;
class ast_ForStmt;
class ast_ReturnStmt;
class ast_BreakStmt;
class ast_PrintStmt;
class ast_Expr;
class ast_ExprSimple;
class ast_ExprBinary;
class ast_ExprUnary;
class ast_ExprRead;
class ast_ExprNew;
class ast_ExprNewArray;
class ast_LValue;
class ast_LValueSimple;
class ast_LvalueExpr;
class ast_LvalueArray;
class ast_Call;
class ast_CallSimple;
class ast_CallExpr;
class ast_Actuals;
class ast_Constant;
class ast_IntConstant;
class ast_DoubleConstant;
class ast_BoolConstant;
class ast_StringConstant;
class ast_NullConstant;
class ast_StmtOrVariableDecl;
class Nodo;
class Scope;
class ScopeProgram;
class ScopeFunc;
class ScopeClass;
class ScopeVar;
vector<string> * unirErrores(vector<string> *,vector<string> * );
bool exiteIdent(Scope *, string);






union node{
  int ival;
  double dval;
  bool bval;
  char *sval ;
  ast_Programa * programa;
  ast_Declaracion * declaracion;
  ast_VariableDecl * variableDecl;
  ast_Variable * variable;
  ast_Type * type;
  ast_FunctionDecl * functionDecl;
  ast_Formals * formals;
  ast_ClassDecl * classDecl;
  ast_TokenClass * tokenClass;
  ast_Field * field;
  ast_InterfaceDecl * interfaceDecl;
  ast_Prototype * prototype;
  ast_StmtBlock * stmtBlock;
  ast_Stmt * stmt;
  ast_IfStmt * ifStmt;
  ast_ElseStmt * elseStmt;
  ast_WhileStmt * whileStmt;
  ast_ForStmt * forStmt;
  ast_ReturnStmt * returnStmt;
  ast_BreakStmt * breakStmt;
  ast_PrintStmt * printStmt;
  ast_Expr * expr;
  ast_LValue * lvalue;
  ast_Call * call;
  ast_Actuals * actuals;
  ast_Constant * constant;
  std::vector<ast_Declaracion *> * listaDecl;
  std::vector<ast_Expr *> * listaExpr; 
  std::vector<ast_StmtOrVariableDecl *> * listaStmtOrVarDecl; 
  std::vector<ast_Prototype *> * listaPrototype; 
  std::vector<string> * listaIdent; 
  std::vector<ast_Field *> * listaField; 
  std::vector<ast_Variable *> * listaVariables;
  
  
};
typedef union node YYSTYPE;
#define YYSTYPE_IS_DECLARED 1


class ast_Programa{
   vector<ast_Declaracion*> * declaraciones;
   public:
        ast_Programa(vector<ast_Declaracion *> *);
        vector<ast_Declaracion*>* getDeclaraciones();
        void printTree();
        ~ast_Programa(){};
};


class ast_Declaracion {
    
    public:
        ast_Declaracion(int,int,int);//linea,columna,tipoast_Declaracion
        int getLinea();
        int getColumna();
        int getTipo();
        virtual void toString(int) = 0;
        ~ast_Declaracion(){};
    protected:
        int linea;
        int columna;
        int tipoDeclaracion; // var = 1, Func = 2 , Class = 3, Inter = 4

};

class ast_VariableDecl : public ast_Declaracion{
    ast_Variable * var;

    public:
        ast_VariableDecl(int,int,int,ast_Variable *);//linea,columna,tipoast_Declaracion
        ast_Variable * getVar();
        void toString(int);
        ~ast_VariableDecl(){};


};

class ast_Variable {
    ast_Type * tipo;
    string ident; 
    string error;
    public:
        ast_Variable();
        ast_Variable(ast_Type *,string);
        ast_Type * getTipo();
        string getString();
        void toString(int);
        int analizarVariable(vector<string> *,Scope *);
        string getError();
        ~ast_Variable(){};
       
};

class ast_Type {
    int tipoDato; /*
                    tipoInt = 1
                    tipoVoid = 2
                    tipoBool = 3
                    tipoDouble = 4
                    tipoString = 5
                    tipoIdent = 6
                */
    bool isArray;
    string ident;
    int linea;
    int columna;

    public:
        ast_Type(int,int,int,bool);
        ast_Type(int,int,int,bool,string);
        int getTipo();
        bool getIsArray();
        void setIsArray(bool);
        string getIdent();
        int getLinea();
        int getColumna();
        ~ast_Type(){};
};

class ast_FunctionDecl : public ast_Declaracion {
    ast_Type * tipoFunc;
    string ident; 
    ast_Formals * formals;
    ast_StmtBlock * stmtBlock;

    public:
        ast_FunctionDecl(int,int,int,ast_Type *,string,ast_Formals *,ast_StmtBlock *); //linea,columna,tipoast_Declaracion
        ast_Type * getTipoFuncion();
        string getIdent();
        ast_Formals * getFormals();
        ast_StmtBlock * getStmtBlock();
        void toString(int);
        ~ast_FunctionDecl(){};
};

class ast_Formals {
    vector<ast_Variable *> * variables;

    public:
        ast_Formals(vector<ast_Variable *>*);
        vector<ast_Variable *> * getVariables();
        ~ast_Formals(){};
};

class ast_ClassDecl : public ast_Declaracion{
    string ident;
    string extends;
    vector<string> * implements;
    vector<ast_Field *> * fields;

    public:
        ast_ClassDecl(int,int,int,string,string,vector<string> *,vector<ast_Field *> *);
        string getIdent();
        string getExtenteds();
        vector<string> * getImplements();
        vector<ast_Field *> * getFields();
        void toString(int);
        ~ast_ClassDecl(){};

};

class ast_TokenClass {
    int linea;
    int columna;

    public:
        ast_TokenClass(int,int);
        int getLinea();
        int getColumna();
        ~ast_TokenClass(){};
};

class ast_Field {
    int tipoDeclracion; // ast_VariableDecl = 1 , ast_FunctionDecl = 2
    ast_VariableDecl * variableDecl;
    ast_FunctionDecl * functionDecl;

    public:
        ast_Field(ast_VariableDecl *);
        ast_Field(ast_FunctionDecl *);
        int getTipoDecl();
        ast_VariableDecl * getVariableDecl();
        ast_FunctionDecl * getFunctionDecl();
        ~ast_Field(){};
};


class ast_InterfaceDecl : public ast_Declaracion{
    string ident;
    vector<ast_Prototype* > * prototypes;

    public:
        ast_InterfaceDecl(int,int,int,string,vector<ast_Prototype * > *);
        string getIdent();
        vector<ast_Prototype* > * getPrototype();
        void toString(int);
        ~ast_InterfaceDecl(){};
};

class ast_Prototype {
    ast_Type * tipo;
    string ident;
    ast_Formals * formals;

    public:
        ast_Prototype(ast_Type *,string,ast_Formals * );
        ast_Type * getTipo();
        string getIdent();
        ast_Formals * getFormals();

};



class ast_Stmt {
    
    public:
        ast_Stmt(int,int,int);//linea,columna,tipo
        int getLinea();
        int getColumna();
        int getTipoStmt();
        vector<string> * getErrores();
        virtual bool analizarStmt(Scope *) = 0;
        ~ast_Stmt();

    protected:
        int linea;
        int columna;
        vector<string> * errores;
        int tipoStmt; // Base = 1, If = 2, while = 3, For = 4, return = 5, break = 6, print = 7, block = 8, Else = 9
};




class ast_StmtBase : public ast_Stmt {
    ast_Expr *  expresion;

    public:
        ast_StmtBase(int,int,ast_Expr *);
        ast_Expr * getExpresion();
        bool analizarStmt(Scope *);
        ~ast_StmtBase();
};

class ast_IfStmt : public ast_Stmt {
    ast_Expr * expresion;
    ast_Stmt * stmt;
    ast_ElseStmt * elseStmt;

    public:
        ast_IfStmt(int,int,ast_Expr *,ast_Stmt *,ast_ElseStmt *);
        ast_Expr * getExpresion();
        ast_Stmt * getStmt();
        ast_ElseStmt * getElseStmt();
        bool analizarStmt(Scope *);
        ~ast_IfStmt(){};
};

class ast_ElseStmt : public ast_Stmt {
    bool isElseNull;
    ast_Stmt * stmt;

    public:
        ast_ElseStmt(int,int,ast_Stmt *);
        ast_ElseStmt(int,int);
        bool isNull();
        ast_Stmt * getStmt();
        bool analizarStmt(Scope *);
        ~ast_ElseStmt(){};
};

class ast_WhileStmt : public ast_Stmt {
    ast_Expr * expresion;
    ast_Stmt * stmt;

    public:
        ast_WhileStmt(int,int,ast_Expr *,ast_Stmt *);
        ast_Expr * getExpresion();
        ast_Stmt * getStmt();
        bool analizarStmt(Scope *);
        ~ast_WhileStmt();
    
};

class ast_ForStmt : public ast_Stmt {
    ast_Expr * firstExpr;
    ast_Expr * secondExpr;
    ast_Expr * thirdExpr;



    ast_Stmt * stmt;  

    public:
        ast_ForStmt(int,int,ast_Expr *,ast_Expr*,ast_Expr*,ast_Stmt *);
        ast_Expr * getFirstExpr();
        ast_Expr * getSecondExpr();
        ast_Expr * getThirdExpr();
        ast_Stmt * getStmt();
        bool analizarStmt(Scope *);
        ~ast_ForStmt(){};

};

class ast_ReturnStmt : public ast_Stmt {
    ast_Expr * expresion;
    bool haveExpr;
    ScopeClass * tipoRetorno;

    public:
        ast_ReturnStmt(int,int,ast_Expr*);
        ast_ReturnStmt(int,int);
        ast_Expr * getExpresion();
        bool getHaveExpr();
        bool analizarStmt(Scope *);
        ScopeClass * getTipoRetorno();
        ~ast_ReturnStmt(){};
};

class ast_BreakStmt : public ast_Stmt {

    public:
        ast_BreakStmt(int,int);
        bool analizarStmt(Scope *);
        ~ast_BreakStmt(){};
};

class ast_PrintStmt : public ast_Stmt{
    vector<ast_Expr *> * expresiones;

    public:
        ast_PrintStmt(int,int,vector<ast_Expr *> *);
        vector<ast_Expr *> * getExpresiones();
        bool analizarStmt(Scope *);
        ~ast_PrintStmt();
};

class ast_StmtBlock : public ast_Stmt {
    vector<ast_StmtOrVariableDecl *> * content;

    public:
        ast_StmtBlock(int,int,vector<ast_StmtOrVariableDecl *> * );
        vector<ast_StmtOrVariableDecl *> * getContent();
        bool analizarStmt(Scope *);
        ~ast_StmtBlock(){};
};

class ast_StmtOrVariableDecl{
    int tipo; // Stmt = 1, VariableDecl = 2
    ast_Stmt * stmt;
    ast_VariableDecl * variableDecl;

    public:
        ast_StmtOrVariableDecl(ast_Stmt *);
        ast_StmtOrVariableDecl(ast_VariableDecl *);
        int getTipo();
        ast_Stmt * getStmt();
        ast_VariableDecl * getVariableDecl();
        void toString(int);
        ~ast_StmtOrVariableDecl(){};
};

class ast_Expr {
    public:
        ast_Expr(int,int,int);//linea,columna,tipo
        ast_Expr(); 
        int getLinea();
        int getColumna();
        int getTipoExpr();
        bool isNull();
        vector<string> * getErrores();
        virtual bool analizarExpr(Scope *) = 0;
        virtual ScopeClass * obtenerTipoExpr(Scope *) = 0;
        ~ast_Expr(){};

    protected:
        bool isNullExpr;
        vector<string> * errores;
        int linea;
        int columna;
        int tipoExpr; // Binary = 1, Unary = 2, Read = 3, New = 4, NewArray = 5, Lvalue = 6, ast_Call = 7 , ast_Constant = 8
};

class ast_ExprSimple : ast_Expr{
    public:
        ast_ExprSimple();
        bool analizarExpr(Scope *);
        ScopeClass * obtenerTipoExpr(Scope *);
        ~ast_ExprSimple(){};
};

class ast_ExprBinary : public ast_Expr {
    ast_Expr * exprIzq;
    ast_Expr * exprDer;
    int tipoOp; /*
                tipoEql = 1
                tipoPlus = 2
                tipoMinus = 3
                tipoMult = 4
                tipoToken_div = 5
                tipoMod = 6
                tipoMenor = 7
                tipoMenorEql = 8
                tipoMayor = 9
                tipoMayorEql = 10
                tipoEqlEql = 11
                tipoNEql = 12
                tipoToken_and = 13
                tipoToken_or = 14
                tipoToken_not = 15
                */

    
    public:
        ast_ExprBinary(int,int,ast_Expr *,ast_Expr *, int);
        ast_Expr * getExprIzq();
        ast_Expr * getExprDer();
        int getTipoOp();
        bool analizarExpr(Scope *);
        ScopeClass * obtenerTipoExpr(Scope *);
        ~ast_ExprBinary(){};


};

class ast_ExprUnary : public ast_Expr {
    ast_Expr * expresion;
     int tipoOp; /*
                tipoEql = 1
                tipoPlus = 2
                tipoMinus = 3
                tipoMult = 4
                tipoToken_div = 5
                tipoMod = 6
                tipoMenor = 7
                tipoMenorEql = 8
                tipoMayor = 9
                tipoMayorEql = 10
                tipoEqlEql = 11
                tipoNEql = 12
                tipoToken_and = 13
                tipoToken_or = 14
                tipoToken_not = 15
                */

    public:
        ast_ExprUnary(int,int,ast_Expr *, int);
        ast_Expr * getExpresion();
        int getTipoOp();
        bool analizarExpr(Scope *);
        ScopeClass * obtenerTipoExpr(Scope *);
        ~ast_ExprUnary(){};
};

class ast_ExprRead : public ast_Expr {
    int tipoRead; // ReadLine = 1 , ReadInteger = 2

    public:
        ast_ExprRead(int,int,int); // linea, columna , tipoRead
        int getTipoRead();
        bool analizarExpr(Scope *);
        ScopeClass * obtenerTipoExpr(Scope *);
        ~ast_ExprRead(){};
};

class ast_ExprNew : public ast_Expr {
    string ident;

    public:
        ast_ExprNew(int,int,string);
        string getIdent();
        bool analizarExpr(Scope *);
        ScopeClass * obtenerTipoExpr(Scope *);
        ~ast_ExprNew(){};

};


class ast_ExprNewArray : public ast_Expr {
    ast_Expr * expresion;
    ast_Type * tipoDato; 

    public:
        ast_ExprNewArray(int,int,ast_Expr *,ast_Type *);
        ast_Expr * getExpresion();
        ast_Type * getTipoDatos();
        bool analizarExpr(Scope *);
        ScopeClass * obtenerTipoExpr(Scope *);
        ~ast_ExprNewArray(){};
};


class ast_LValue: public ast_Expr {
    int tipoLvalue; // Simple = 1, ast_Expr = 2 , Array = 3

    public:
        ast_LValue(int,int,int); // linea, columna , tipoLvalue
        int getTipoLvalue();
        virtual bool analizarExpr(Scope *) = 0;\
        virtual ScopeClass * obtenerTipoExpr(Scope *) = 0;
        ~ast_LValue(){};
     
};

class ast_LValueSimple : public ast_LValue {
    string ident;


    public:
        ast_LValueSimple(int,int,string); // linea, columna
        string getIdent();
        bool analizarExpr(Scope *);
        ScopeClass * obtenerTipoExpr(Scope *);
        ~ast_LValueSimple();
};

class ast_LvalueExpr : public ast_LValue {
    ast_Expr * expresion;
    string ident;

    public : 
        ast_LvalueExpr(int,int,ast_Expr *, string); // linea, columna
        ast_Expr * getExpr();
        string getIdent();
        bool analizarExpr(Scope *);
        ScopeClass * obtenerTipoExpr(Scope *);
        ~ast_LvalueExpr(){};

};


class ast_LvalueArray : public ast_LValue {
    ast_Expr * firstExpr;
    ast_Expr * secondExpr;

    public : 
        ast_LvalueArray(int,int,ast_Expr *, ast_Expr *); // linea, columna
        ast_Expr * getFirstExpr();
        ast_Expr * getSecondExpr();
        bool analizarExpr(Scope *);
        ScopeClass * obtenerTipoExpr(Scope *);
        ~ast_LvalueArray(){};

};



class ast_Call: public ast_Expr {
    int tipoCall; // Simple = 1, ast_Expr = 2 

    public:
        ast_Call(int,int,int); // linea, columna , tipoCall
        int getTipoCall();
        virtual bool analizarExpr(Scope *) = 0;
        virtual ScopeClass * obtenerTipoExpr(Scope *) = 0;
        ~ast_Call(){};

};



class ast_CallSimple : public ast_Call {
    string ident;
    ast_Actuals * actuals;

    public:
        ast_CallSimple(int,int,string,ast_Actuals *); // linea, columna
        string getIdent();
        ast_Actuals * getActuals();
        bool analizarExpr(Scope *);
        ScopeClass * obtenerTipoExpr(Scope *);
        ~ast_CallSimple(){};
};

class ast_CallExpr : public ast_Call {
    ast_Expr * expr;
    string ident;
    ast_Actuals * actuals;

    public:
        ast_CallExpr(int,int,ast_Expr *,string,ast_Actuals *); // linea, columna
        ast_Expr * getExpr();
        string getIdent();
        ast_Actuals * getActuals();
        bool analizarExpr(Scope *);
        ScopeClass * obtenerTipoExpr(Scope *);
        ~ast_CallExpr(){};
};

class ast_Actuals {
    vector<ast_Expr *> * expresiones;
    vector<string> * errores;
    public:
        ast_Actuals(vector<ast_Expr *> *);
        vector<ast_Expr *> * getExpresiones();
        bool analizarActuals(Scope *,ScopeFunc *,int,int);
        vector<string> * getErrores();
        ~ast_Actuals(){};
};


class ast_Constant: public ast_Expr {
    int tipoConst; // Int = 1, Double = 2, Bool = 3, String = 4, Null = 5 

    public:
        ast_Constant(int,int,int); // linea, columna, tipoConst
        int getTipoConst();
        bool analizarExpr(Scope *);
        ScopeClass * obtenerTipoExpr(Scope *);
        ~ast_Constant(){};
		
};




class ast_IntConstant : public ast_Constant {
	int valor;
	
	public:
		ast_IntConstant(int,int,int); // linea, columna
        int getValor();
        ~ast_IntConstant(){};
	
};



class ast_DoubleConstant : public ast_Constant {
	double valor;
	
	public:
		ast_DoubleConstant(int,int,double); // linea, columna
        double getValor();
        ~ast_DoubleConstant(){};
	
};



class ast_BoolConstant : public ast_Constant {
	bool valor;
	
	public:
		ast_BoolConstant(int,int,bool); // linea, columna
        bool getValor();
        ~ast_BoolConstant(){};
	
};


class ast_StringConstant : public ast_Constant {
	string valor;
	
	public:
		ast_StringConstant(int,int,string); // linea, columna
        string getValor();
        ~ast_StringConstant(){};
	
};


class ast_NullConstant : public ast_Constant {
	
	public:
		ast_NullConstant(int,int); // linea, columna
        ~ast_NullConstant(){};
};


class Scope {
    

    public:
        Scope(int,Scope *);
        int getTipoScope();
        Scope * getPadre();
        vector<Scope *> * getHijos();
        bool isScopeValido();
        vector<string> * getErrores();
        void setScopeValido(bool);
        virtual bool identRepetido(string) = 0;
        virtual ScopeClass * obtenerClase(string) = 0;
        virtual ScopeFunc * obtenerFunc(string) = 0;
        virtual bool existeIdent(string) = 0;
        ~Scope(){};

    protected:
        int tipoScope;
        Scope * padre;
        vector<Scope *> * scopesHijos;
        vector<string> * errores;
        bool scopeValido;
};

class ScopeProgram : public Scope {
    ast_Programa * programa;
    vector<ScopeVar *> * variables;
    vector<ScopeFunc *> * funciones;
    vector<ScopeClass *> * clases;

    public:
        ScopeProgram(ast_Programa *);
        ast_Programa * getPrograma();
        vector<ScopeVar *> * getVariables();
        vector<ScopeFunc *> * getFunciones();
        vector<ScopeClass *> * getClases();
        bool analizarArbol();
        bool identRepetido(string);
        ScopeClass * obtenerClase(string);
        ScopeFunc * obtenerFunc(string);
        bool existeIdent(string);
        ~ScopeProgram(){};

};

class ScopeFunc : public Scope {
    ast_FunctionDecl * funcion;
    vector<ScopeVar *> * variables;
    bool tipoExistente;
    ScopeClass * tipoRetorno;
    vector<string> * listaParametros;

    public:
        ScopeFunc(Scope *,ast_FunctionDecl *);
        ast_FunctionDecl * getFuncion();
        vector<ScopeVar *> * getVariables();
        bool isTipoExistente();
        bool analizarFunc();
        bool identRepetido(string);
        ScopeClass * getTipoRetorno();
        ScopeClass * obtenerClase(string);
        ScopeFunc * obtenerFunc(string);
        vector<string> * getListaParametros();
        bool existeIdent(string);
        ~ScopeFunc(){};

};

class ScopeClass : public Scope{
    ast_ClassDecl * clase;
    vector<ScopeVar *> * variables;
    vector<ScopeFunc *> * funciones;
    ScopeClass * clasePadre;
    vector<ScopeClass *> * clasesHijas; 
    bool tipoPrimitivo;
        public:
        ScopeClass(Scope *,ast_ClassDecl *);
        ast_ClassDecl * getClase();
        vector<ScopeVar *> * getVariables();
        vector<ScopeFunc *> * getFunciones();
        ScopeClass * getClasePadre();
        bool analizarClase();
        bool identRepetido(string);
        ScopeClass * obtenerClase(string);
        bool isTipoPrimitivo();
        bool existeMetodo(string);
        bool existeVariable(string);
        vector<ScopeClass *> * getClasesHijas();
        bool isClaseHija(ScopeClass *);
        ScopeFunc * obtenerFunc(string);
        bool existeIdent(string);
        ~ScopeClass(){};
};

class ScopeVar : public Scope{
    ast_VariableDecl * variable;
    bool tipoExistente;
    public:
        ScopeVar(Scope *,ast_VariableDecl *);
        ast_VariableDecl * getVariable();
        bool isTipoExistente();
        bool analizarVar();
        bool identRepetido(string);
        ScopeClass * obtenerClase(string);
        ScopeFunc * obtenerFunc(string);
        bool existeIdent(string);
        ~ScopeVar(){};
};

class ScopeClassInt : public ScopeClass {

};

class ScopeClassDouble : public ScopeClass {
    
};

class ScopeClassVoid : public ScopeClass {
    
};

class ScopeClassString : public ScopeClass {
    
};

class ScopeClassBool : public ScopeClass {
    
};

















#endif