#ifndef __utils_H
#include <string>
#include <vector>
#include <map>
#include <string>
#include "hw3_output.hpp"
#include <iostream>
using std::string;
using std::cout;
using std::endl;

#define __utils_H
struct Node
{
};
struct Expression : public Node
{
    string type;
};
struct ExpressionList : public Node
{
    std::vector<string> types;
};

struct Token : public Node
{
    string lexeme;
    Token(string s) : lexeme(s)
    {
    }
};
typedef union {
    Expression* exp;
    ExpressionList* expList;
    Token* token;
} STYPE;
#define YYSTYPE STYPE // Tell Bison to use STYPE as the stack type
#define YYINITDEPTH 5000
struct SymbolRow
{
    string type;
    vector<string> arguments;
    int offset;
};
typedef std::map<string, SymbolRow> Scope;
void createScope(bool is_function = false);
void endScope();
void insertToScope(const string &identifier, const string &type);
void addArguments(const string &identifier);
const string& getType(const string& identifier,bool is_function=false);
void init();
void checkCall(Token*,ExpressionList*);
void checkExpressionType(const string& type1,const string& type2,bool symetric=false);
void checkReturn(Expression* exp=NULL);
void checkByteRange(Token*);
string checkArithmetic(Expression*,Expression*);
void checkBreak();
void checkContinue();
void lowerWhileCounter();
void raiseWhileCounter();
#endif