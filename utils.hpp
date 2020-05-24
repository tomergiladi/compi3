#ifndef __utils_H
#include "string"
#include "vector"
#include "map"
#include "string"
#include "hw3_output.hpp"
using std::string;
#define __utils_H
struct Expression{
    string type;
};
struct ExpressionList{
    std::vector<string> types;
};

struct Token {
    string lexeme;
};
typedef union {
    Token token;
    Expression exp;
    ExpressionList expList; 
} STYPE;
#define YYSTYPE STYPE	// Tell Bison to use STYPE as the stack type
struct SymbolRow{
    string type;
    int offset;
};
typedef std::map<string,SymbolRow> Scope;
void createScope(bool is_function=false);
void endScope();
void insertToScope(const string& identifier,const string& type);
#endif