#include "ast.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

clase::clase(string id, vector<field_decl *> * fdl, vector<method_decl *> * mdl){
    this->id = id;
    this->mdl = mdl;
    this->fdl = fdl;
}

string clase::getId()
{
    return this->id;
}

vector<method_decl *> * clase::getMdl()
{
    return this->mdl;
}

vector<field_decl *> * clase::getFdl()
{
   return this->fdl;
}


field_decl::field_decl(vector<id *> * id_list, TipoDatos type)
{
  this->tipo = type;
  this->listaId = id_list;
}

vector<id *> * field_decl::getListaId()
{
    return this->listaId;
}

TipoDatos field_decl::getTipo()
{
    return this->tipo;
}

var_decl::var_decl(vector<id *> * id_list, TipoDatos type)
{
    this->tipo = type;
    this->listaId = id_list;
}

TipoDatos var_decl::getTipo()
{
    return this->tipo;
}

vector<id *> * var_decl::getListaId()
{
  return this->listaId;
}


id::id(string _Identity, int size)
{
    if (size <= 0) {
        cerr << "Tamaño invalido" << endl;
        exit(-1);
    }

    this->identity = _Identity;
    this->tamanno = size;
}

id::id(string id)
{
    this->identity = id;
    this->tamanno = 0;
}

string id::getId()
{
    return this->identity;
}

int id::getSize()
{
    return this->tamanno;
}



type_identifier::type_identifier(string id, TipoDatos tipo)
{
    this->id = id;
    this->tipo = tipo;
}

string type_identifier::get_id()
{
    return this->id;
}

TipoDatos type_identifier::getTipo()
{
    return this->tipo;
}



string_callout_arg::string_callout_arg(string argument)
{
    this->args = argument;
}

string string_callout_arg::getArgs()
{
    return this->args;
}

expression_callout_arg::expression_callout_arg(expresion * argument)
{
    this->argument = argument;
}
expresion * expression_callout_arg::getArgs()
{
    return this->argument;
}


var_location::var_location(string id)
{
    this->id = id;
}
string var_location::getId()
{
    return this->id;
}


array_location::array_location(string id, expresion * index)
{
    this->id = id;
    this->index = index;
}
string array_location::getId()
{
    return this->id;
}
expresion * array_location::getIndex()
{
    return this->index;
}

constanteInt::constanteInt(int valor)
{
    this->valor = valor;
}
int constanteInt::get_valor()
{
    return this->valor;
}

constanteDouble::constanteDouble(double valor)
{
    this->valor = valor;
}
double constanteDouble::get_valor()
{
    return this->valor;
}

constanteNull::constanteNull(){
    
}


constanteString::constanteString(string valor)
{
    this->valor = valor;
}
string constanteString::get_valor()
{
    return this->valor;
}

expresionOpBin::expresionOpBin(expresion * izq, expresion * der, bin_op op)
{
    this->izq = izq;
    this->der = der;
    this->op = op;
}
expresion * expresionOpBin::getIzq()
{
    return this->izq;
}
expresion * expresionOpBin::getDer()
{
    return this->der;
}
bin_op expresionOpBin::getOp()
{
    return this->op;
}

expresionOpUn::expresionOpUn(expresion * expr, un_op op)
{
    this->expr = expr;
    this->op = op;
}
expresion * expresionOpUn::getExpr()
{
    return this->expr;
}
un_op expresionOpUn::getOp ()
{
    return this->op;
}