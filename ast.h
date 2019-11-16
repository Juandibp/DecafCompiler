#ifndef _H
#define _H

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


class clase;
class field_decl;
class var_decl;
class id;
class method_decl;
class type_identifier;
class statement;
class expresion;
class block_statement;
class assignment_statement;
class method_call;
class normal_method;
class callout_method;
class callout_arg;
class string_callout_arg;
class expression_callout_arg;
class if_statement;
class for_statement;
class return_statement;
class continue_statement;
class break_statement;
class location;
class var_location;
class array_location;
class constante;
class constanteInt;
class constanteString;
class constanteBool;
class constanteDouble;
class expresionOpBin;
class expresionOpUn;

enum class opAsign {
    mas_igual,
    menos_igual,
    equal
};

enum class bin_op {
    opSuma,
    opResta,
    opMul,
    opDiv,
    opMod,
    opMenor,
    opMayor,
    opMenorIgual,
    opMayorIguak,
    opDiferente	,
    opIgualIgual,
    opAnd,
    opOr
};

enum class TipoDatos {
    tipoInt,
    tipoVoid,
    tipoBool,
	tipoDouble,
	tipoString
};

enum class un_op {
    opNeg,
    opNot
};

class nodo{
	public:
		nodo(){};
};

union node{
  opAsign op;
  block_statement * block;
  callout_arg * calloutArg;
  expresion * expr;
  field_decl * fieldDecl;
  id * var_or_array_identifier;
  constante * literal;
  location * location;
  method_call * methodCall;
  method_decl * methodDecl;
  clase * program;
  statement * stmt;
  type_identifier * typeIdentifier;
  var_decl * varDecl;
  string sval;
  TipoDatos type;
  int ival;
  double dval;
  bool bval;
  std::vector<callout_arg *> * callout_arg_list;
  std::vector<expresion *> * expr_list;
  std::vector<field_decl *> * field_decl_list;
  std::vector<id *> * identifier_list;
  std::vector<id *> * var_or_array_identifier_list;
  std::vector<method_decl *> * method_decl_list;
  std::vector<statement *> * statement_list;
  std::vector<type_identifier *> * type_identifier_list;
  std::vector<var_decl *> * var_decl_list;
  
};
typedef union node YYSTYPE;
#define YYSTYPE_IS_DECLARED 1

class clase : public nodo {
	string id;
    vector<field_decl *> * fdl;
    vector<method_decl *> * mdl;
	public:
		clase(string,vector<field_decl *> *,vector<method_decl *> *);
		string getId();
		vector<field_decl *> *getFdl();
    	vector<method_decl *> *getMdl();
		~clase(){}

	
};

class field_decl : public nodo{
	TipoDatos tipo;
	vector<id*> *listaId;
	public:
		field_decl(vector<id*> *,TipoDatos);
		vector<id*> *getListaId();
		TipoDatos getTipo();
		~field_decl(){}
};

class var_decl : public nodo{
	TipoDatos tipo;
	vector<id*> *listaId;
	public:
		var_decl(vector<id*> *,TipoDatos);
		vector<id*> *getListaId();
		TipoDatos getTipo();
		~var_decl(){}
};

class id {
	string identity;
	int tamanno;
	public:
		id(string,int);
		id(string id);
		string getId();
		int getSize();
		~id(){}

};

class method_decl : public nodo{
	string id;
	TipoDatos tipo;
	vector<type_identifier*>* args;
	block_statement* bloque;
	public:
		method_decl(string id,TipoDatos,vector<type_identifier*>*,block_statement);
		string getId();
		TipoDatos getTipo();
		vector<type_identifier*>* getArgs();
		block_statement* getBloque();
		~method_decl(){}
};

class type_identifier : public nodo
{
    string id;
    TipoDatos tipo;
	public:
		type_identifier(string, TipoDatos);
		~type_identifier() {}
		string get_id();
		TipoDatos getTipo();
};

class statement : public nodo
{
public:
    statement() {}
    virtual ~statement() {}
};

class block_statement : public statement
{
    vector<var_decl *> * listaId;
    vector<statement *> * listaStmt;
	public:
		block_statement(vector<statement *> * , vector<var_decl *> * );
		vector<var_decl *> * getListaId();
		vector<statement *> * getListaStmt();
		~block_statement() {}
};


class assignment_statement : public statement
{
    opAsign op;
    location * locat;
    expresion * expr;
	public:
		assignment_statement(opAsign, location *, expresion *);
		opAsign getOp();
		location * getLocation();
		expresion * getExpr();
		~assignment_statement() {}
};


class expresion: public nodo {
	public:
		expresion(){};
		virtual ~expresion(){};

};

class method_call : public statement, public expresion
{
public:
    method_call() { }
    virtual ~method_call() {}
};

class normal_method : public method_call
{
    string id;
    vector<expresion *> * args;
	public:
		normal_method(string, vector<expresion *> * );
		string getId();
		vector<expresion *> * getArgs();
		~normal_method() {}
};


class callout_method : public method_call{
    string nombre;
    vector<callout_arg *> * args;
public:
    callout_method(string , vector<callout_arg *> * );
    string getNombre();
    vector<callout_arg *> * getArgs();
    ~callout_method() {}
};

class callout_arg : public expresion{
	public:
		callout_arg() {}
		virtual ~callout_arg() {}
};

class string_callout_arg : public callout_arg
{
    string args;
public:
    string_callout_arg(string);
    string getArgs();
    ~string_callout_arg() {}
};

class expression_callout_arg : public callout_arg
{
    expresion * argument;
public:
    expression_callout_arg(expresion *);
    expresion * getArgs();
    ~expression_callout_arg() {}
};

class if_statement : public statement
{
    expresion * condicion;
    block_statement * bloqueIf;
    block_statement * bloqueElse;
	public:
		if_statement(expresion *, block_statement *, block_statement *);
		expresion * getCondicion();
		block_statement * getBlockIf();
		block_statement * getBloqueElse();
		~if_statement() {}
};

class for_statement : public statement
{
    string id;
    expresion * condicionIni;
    expresion * condicionFin;
    block_statement * bloque;
	public:
		for_statement(expresion *, expresion *, block_statement *, string);
		string get_id();
		expresion * getCondicionIni();
		expresion * getCondicionFin();
		block_statement * getBloque();
		~for_statement() {}
};

class return_statement : public statement{
    expresion * expr;
	public:
		return_statement(expresion *);
		expresion * getExpr();
		~return_statement() {}
};

class continue_statement : public statement {
	public:
		continue_statement() {}
		~continue_statement() {}
};

class break_statement : public statement {
	public:
		break_statement() {}
		~break_statement() {}
};

class location : public expresion{
	public:
		location() {}
		virtual ~location() {}
};

class var_location : public location
{
    string id;
	public:
		var_location(string);
		string getId();
		~var_location() {}
};

class array_location : public location
{
    string id;
    expresion * index;
	public:
		array_location(string, expresion * );
		string getId();
		expresion * getIndex();
		~array_location(){}
};




class constante: public expresion {
	public:
		constante() {}
		~constante(){}
		
};

class constanteInt : public constante {
	int valor;
	
	public:
		constanteInt(int){}
		int get_valor(){
			return valor;
		}
		~constanteInt(){}
	
};

class constanteDouble : public constante {
	double valor;
	
	public:
		constanteDouble(double){}
		double get_valor(){
			return valor;
		}
		~constanteDouble(){}
	
};
class constanteBool : public constante {
	bool valor;
	
	public:
		constanteBool(bool){}
		bool get_valor(){
			return valor;
		}
		~constanteBool(){}
	
};

class constanteString : public constante {
	string valor;
	
	public:
		constanteString(string){}
		string get_valor(){
			return valor;
		}
		~constanteString(){}
	
};


class constanteNull : public constante {
	
	public:
		constanteNull(){}
		~constanteNull(){}
};

class expresionOpBin : public expresion{
	expresion *izq;
	expresion *der;
	bin_op op;

	public:
		expresionOpBin(expresion*,expresion*,bin_op);
		expresion * getIzq();
		expresion * getDer();
		bin_op	getOp();
		~expresionOpBin(){};

};

class expresionOpUn : public expresion{
	expresion *expr;
	un_op op;

	public:
		expresionOpUn(expresion*,un_op);
		expresion * getExpr();
		un_op	getOp();
		~expresionOpUn(){};

};



#endif
	