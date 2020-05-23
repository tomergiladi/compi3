#ifndef __utils_H
#define __utils_H
struct Expression{
    string type;
};
struct Function{
    string retType;
    std::vector<string> atguments;
};

struct Token {
    string lexeme;
};
typedef union {
    Token token;
    Expression expression;
};
#define YYSTYPE STYPE	// Tell Bison to use STYPE as the stack type
#endif