#ifndef _H
#define _H

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Programa;
class Declaracion;
class VariableDecl;
class Variable;
class Type;
class FunctionDecl;
class Formals;
class ClassDecl;
class Field;
class InterfaceDecl;
class Prototype;
class Stmt;
class StmtBlock;
class StmtBase;
class IfStmt;
class WhileStmt;
class ForStmt;
class ReturnStmt;
class BreakStmt;
class PrintStmt;
class Expr;
class ExprBinary;
class ExprUnary;
class ExprRead;
class ExprNew;
class ExprNewArray;
class LValue;
class LValueSimple;
class LvalueExpr;
class LvalueArray;
class Call;
class CallSimple;
class CallExpr;
class Actuals;
class Constant;
class IntConstant;
class DoubleConstant;
class BoolConstant;
class StringConstant;
class NullConstant;
class Nodo;




enum class TipoDatos {
    tipoInt,
    tipoVoid,
    tipoBool,
	tipoDouble,
	tipoString,
    tipoIdent
};

enum class TipoStmt {
    tipoBase,
    tipoIf,
    tipoWhile,
    tipoFor,
    tipoBreak,
    tipoReturn,
    tipoPrint,
    tipoBlock
};

enum class TipoOperacion {
    eql,
    plus,
    minus,
    mult,
    token_div,
    mod,
    menor,
    menorEql,
    mayor,
    mayorEql,
    eqlEql,
    nEql,
    token_and,
    token_or,
    token_not


};

union node{
  int ival;
  double dval;
  bool bval;
  TipoDatos tipoDatos;
  Programa * programa;
  Declaracion * declaracion;
  VariableDecl * variableDecl;
  Variable * variable;
  Type * type;
  FunctionDecl * functionDecl;
  Formals * formals;
  ClassDecl * classDecl;
  Field * field;
  InterfaceDecl * interfaceDecl;
  Prototype * prototype;
  StmtBlock * stmtBlock;
  Stmt * stmt;
  IfStmt * ifStmt;
  WhileStmt * whileStmt;
  ForStmt * forStmt;
  ReturnStmt * returnStmt;
  BreakStmt * breakStmt;
  PrintStmt * printStmt;
  Expr * expr;
  LValue * lvalue;
  Call * call;
  Actuals * actuals;
  Constant * constant;
  std::vector<Declaracion *> * listaDecl;
  
};
typedef union node YYSTYPE;
#define YYSTYPE_IS_DECLARED 1


class Programa{
   vector<Declaracion*> *declaraciones;
   public:
        Programa(vector<Declaracion *> *);
        vector<Declaracion*>* getDeclaraciones();
        ~Programa(){};
};


class Declaracion {
    
    public:
        Declaracion(int,int,int);//linea,columna,tipoDeclaracion
        int getLinea();
        int getColumna();
        int getTipo();
        ~Declaracion(){};
    protected:
        int linea;
        int columna;
        int tipoDeclaracion;

};

class VariableDecl : public Declaracion{
    Variable * var;

    public:
        VariableDecl(int,int,int,Variable *);//linea,columna,tipoDeclaracion
        Variable * getVar();
        ~VariableDecl(){};


};

class Variable {
    Type * tipo;
    string ident; 

    public:
        Variable();
        Variable(Type *,string);
        Type * getTipo();
        string getString();
        ~Variable(){};
       
};

class Type {
    TipoDatos tipo;
    bool isArray;
    string ident;

    public:
        Type(TipoDatos,bool);
        Type(TipoDatos,bool,string);
        TipoDatos getTipo();
        bool getIsArray();
        string getIdent();
        ~Type(){};
};

class FunctionDecl : public Declaracion {
    Type * tipoFunc;
    string ident; 
    Formals * formals;
    StmtBlock * stmtBlock;

    public:
        FunctionDecl(int,int,int,Type *,string,Formals *,StmtBlock *); //linea,columna,tipoDeclaracion
        Type * getTipoFuncion();
        string getIdent();
        Formals * getFormals();
        StmtBlock * getStmtBlock();
        ~FunctionDecl(){};
};

class Formals {
    vector<Variable *> * variables;

    public:
        Formals(vector<Variable *>*);
        vector<Variable *> * getVariables();
        ~Formals(){};
};

class ClassDecl : public Declaracion{
    string ident;
    vector<string> * extends;
    vector<string> * implements;
    vector<Field *> * fields;

    public:
        ClassDecl(int,int,int,string,vector<string> *,vector<string> *,vector<Field *> *);
        string getIdent();
        vector<string> * getExtenteds();
        vector<string> * getImplements();
        vector<Field *> * getFields();
        ~ClassDecl(){};

};

class Field {
    int tipoDeclracion; // VariableDecl = 1 , FunctionDecl = 2
    VariableDecl * variableDecl;
    FunctionDecl * functionDecl;

    public:
        Field(VariableDecl *);
        Field(FunctionDecl *);
        int getTipoDecl();
        VariableDecl * getVariableDecl();
        FunctionDecl * getFunctionDecl();
        ~Field(){};
};


class InterfaceDecl : public Declaracion{
    string ident;
    vector<Prototype* > * prototypes;

    public:
        InterfaceDecl(int,int,int,string,vector<Prototype * > *);
        string getIdent();
        vector<Prototype* > * getPrototype();
        ~InterfaceDecl(){};
};

class Prototype {
    Type * tipo;
    string ident;
    Formals * formals;

    public:
        Prototype(Type *,string,Formals * );
        Type * getTipo();
        string getIdent();
        Formals * getFormals();

};



class Stmt {
    
    public:
        Stmt(int,int,int);//linea,columna,tipo
        int getLinea();
        int getColumna();
        int getTipoStmt();
        ~Stmt();

    protected:
        int linea;
        int columna;
        int tipoStmt; // Base = 1, If = 2, while = 3, For = 4, return = 5, break = 6, print = 7, block = 8
};




class StmtBase : public Stmt {
    Expr *  expresion;

    public:
        StmtBase(int,int,Expr *);
        Expr * getExpresion();
        ~StmtBase();
};

class IfStmt : public Stmt {
    Expr * expresion;
    Stmt * stmt;
    bool haveElse;
    Stmt * elseStmt;

    public:
        IfStmt(int,int,Expr *,Stmt *,Stmt *);
        IfStmt(int,int,Expr *,Stmt *);
        Expr * getExpresion();
        Stmt * getStmt();
        bool getHaveElse();
        Stmt * getElseStmt();
        ~IfStmt(){};
};

class WhileStmt : public Stmt {
    Expr * expresion;
    Stmt * stmt;

    public:
        WhileStmt(int,int,Expr *,Stmt *);
        Expr * getExpresion();
        Stmt * getStmt();
        ~WhileStmt();
    
};

class ForStmt : public Stmt {
    Expr * firstExpr;
    Expr * secondExpr;
    Expr * thirdExpr;

    bool haveFirstExpr;
    bool haveSecondExpr; 
    bool haveThirdExpr;

    Stmt * stmt;  

    public:
        ForStmt(int,int,Expr *,Expr*,Expr*,Stmt *);
        ForStmt(int,int,Expr *,Expr*,Stmt *);
        ForStmt(int,int,Expr *,Stmt *);
        ForStmt(int,int,Stmt *);
        Expr * getFirstExpr();
        Expr * getSecondExpr();
        Expr * getThirdExpr();
        bool getHaveFirstExpr();
        bool getHaveSecondExpr(); 
        bool getHaveThirdExpr();
        Stmt * getStmt();
        ~ForStmt(){};

};

class ReturnStmt : public Stmt {
    Expr * expresion;
    bool haveExpr;

    public:
        ReturnStmt(int,int,Expr*);
        ReturnStmt(int,int);
        Expr * getExpresion();
        bool getHaveExpr();
        ~ReturnStmt(){};
};

class BreakStmt : public Stmt {

    public:
        BreakStmt(int,int);
        ~BreakStmt(){};
};

class PrintStmt : public Stmt{
    vector<Expr *> * expresiones;

    public:
        PrintStmt(int,int,vector<Expr *> *);
        vector<Expr *> * getExpresiones();
        ~PrintStmt();
};

class StmtBlock : public Stmt {
    vector<VariableDecl *> * variableDecls;
    vector<Stmt *> * stmts;

    public:
        StmtBlock(int,int,vector<VariableDecl *> * ,vector<Stmt *> * );
        vector<VariableDecl *> * getVariableDecls();
        vector<Stmt *> * getStmts();
        ~StmtBlock(){};
};

class Expr {
    public:
        Expr(int,int,int);//linea,columna,tipo
        int getLinea();
        int getColumna();
        int getTipoExpr();
        ~Expr();

    protected:
        int linea;
        int columna;
        int tipoExpr; // Binary = 1, Unary = 2, Read = 3, New = 4, NewArray = 5, Lvalue = 6, Call = 7 , Constant = 8
};

class ExprBinary : public Expr {
    Expr * exprIzq;
    Expr * exprDer;
    TipoOperacion tipoOp;

    
    public:
        ExprBinary(int,int,Expr *,Expr *, TipoOperacion);
        Expr * getExprIzq();
        Expr * getExprDer();
        TipoOperacion getTipoOp();
        ~ExprBinary(){};


};

class ExprUnary : public Expr {
    Expr * expresion;
    TipoOperacion tipoOp;

    public:
        ExprUnary(int,int,Expr *, TipoOperacion);
        Expr * getExpresion();
        TipoOperacion getTipoOp();
        ~ExprUnary(){};
};

class ExprRead : public Expr {
    int tipoRead; // ReadLine = 1 , ReadInteger = 2

    public:
        ExprRead(int,int,int); // linea, columna , tipoRead
        int getTipoRead();
        ~ExprRead(){};
};

class ExprNew : public Expr {
    string ident;

    public:
        ExprNew(int,int,string);
        string getIdent();
        ~ExprNew(){};

};


class ExprNewArray : public Expr {
    Expr * expresion;
    TipoDatos tipoDato;

    public:
        ExprNewArray(int,int,Expr *,TipoDatos);
        Expr * getExpresion();
        TipoDatos getTipoDatos();
        ~ExprNewArray(){};
};


class LValue: public Expr {
    int tipoLvalue; // Simple = 1, Expr = 2 , Array = 3

    public:
        LValue(int,int,int); // linea, columna , tipoLvalue
        int getTipoLvalue();
        ~LValue(){};
     
};

class LValueSimple : public LValue {
    string ident;


    public:
        LValueSimple(int,int,string); // linea, columna
        string getIdent();
        ~LValueSimple();
};

class LvalueExpr : public LValue {
    Expr * expresion;
    string ident;

    public : 
        LvalueExpr(int,int,Expr *, string); // linea, columna
        Expr * getExpr();
        string getIdent();
        ~LvalueExpr(){};

};


class LvalueArray : public LValue {
    Expr * firstExpr;
    Expr * secondExpr;

    public : 
        LvalueArray(int,int,Expr *, Expr *); // linea, columna
        Expr * getFirstExpr();
        Expr * getSecondExpr();
        ~LvalueArray(){};

};


class Call: public Expr {
    int tipoCall; // Simple = 1, Expr = 2 

    public:
        Call(int,int,int); // linea, columna , tipoCall
        int getTipoCall();
        ~Call(){};
     
};



class CallSimple : public Call {
    string ident;
    Actuals * actuals;

    public:
        CallSimple(int,int,string,Actuals *); // linea, columna
        string getIdent();
        Actuals * getActuals();
        ~CallSimple(){};
};

class CallExpr : public Call {
    Expr * expr;
    string ident;
    Actuals * actuals;

    public:
        CallExpr(int,int,Expr *,string,Actuals *); // linea, columna
        Expr * getExpr();
        string getIdent();
        Actuals * getActuals();
        ~CallExpr(){};
};

class Actuals {
    vector<Expr *> * expresiones;

    public:
        Actuals(vector<Expr *> *);
        vector<Expr *> * getExpresiones();
        ~Actuals(){};
};


class Constant: public Expr {
    int tipoConst; // Int = 1, Double = 2, Bool = 3, String = 4, Null = 5 

    public:
        Constant(int,int,int); // linea, columna, tipoConst
        int getTipoConst();
        ~Constant(){};
		
};




class IntConstant : public Constant {
	int valor;
	
	public:
		IntConstant(int,int,int); // linea, columna
        int getValor();
        ~IntConstant(){};
	
};



class DoubleConstant : public Constant {
	double valor;
	
	public:
		DoubleConstant(int,int,double); // linea, columna
        double getValor();
        ~DoubleConstant(){};
	
};



class BoolConstant : public Constant {
	bool valor;
	
	public:
		BoolConstant(int,int,bool); // linea, columna
        bool getValor();
        ~BoolConstant(){};
	
};


class StringConstant : public Constant {
	string valor;
	
	public:
		StringConstant(int,int,string); // linea, columna
        string getValor();
        ~StringConstant(){};
	
};


class NullConstant : public Constant {
	
	public:
		NullConstant(int,int); // linea, columna
        ~NullConstant(){};
};














#endif