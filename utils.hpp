#ifndef __utils_H
#include <string>
#include <vector>
#include <map>
#include <string>
#include "hw3_output.hpp"
using std::string;
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
    Token(string &s) : lexeme(s)
    {
    }
};

#define YYSTYPE Node * // Tell Bison to use STYPE as the stack type
struct SymbolRow
{
    string type;
    int offset;
};
typedef std::map<string, SymbolRow> Scope;
void createScope(bool is_function = false);
void endScope();
void insertToScope(const string &identifier, const string &type);
#endif