#include "utils.hpp"
extern int yylineno;
std::vector<Scope> scopes;
std::vector<vector<string>> scopes_variables;
std::vector<int> offsets;
int whileCounter=0;
string temp="Fsfsa";
void init(){
//    cout << "init" << endl;
    scopes.push_back(Scope());
    scopes_variables.push_back(vector<string>());
    offsets.push_back(0);
    insertToScope("print","VOID");
    insertToScope("printi","VOID");
    scopes[0]["print"].arguments.push_back("STRING");
    scopes[0]["printi"].arguments.push_back("INT");
}
void createScope(bool is_function){
    //cout << "createScope" << is_function << endl;
    scopes.push_back(Scope());
    scopes_variables.push_back(vector<string>());
    if(!is_function){
        offsets.push_back(offsets[offsets.size()-1]);
    } else {
        //cout << "fsdfsdafA" << endl;
        offsets.push_back(-1);
    }
}
void endScope(){
    //cout << "endScope" << endl;
    
    auto& scope = scopes.back();   
    auto& variables = scopes_variables.back();
    if(scopes.size()==1){
        if(scope.find("main")==scope.end() || scope["main"].type!="VOID" || scope["main"].arguments.size()!=0){
            output::errorMainMissing();
            exit(0);
        }
    }
    output::endScope();
    for(auto& variable: variables){
            if(scopes.size()>1){
                output::printID(variable,scope[variable].offset ,scope[variable].type);
            } else {
                output::printID(variable,scope[variable].offset ,output::makeFunctionType(scope[variable].type,scope[variable].arguments));
            }
    }
    scopes_variables.pop_back();
    scopes.pop_back();
    offsets.pop_back();
}
const string& getType(const string& identifier,bool is_function){
    //cout << "getType" << identifier << endl;
    if(is_function){
        if(scopes[0].find(identifier)!=scopes[0].end()){
            return scopes[0][identifier].type;
        }
        output::errorUndefFunc(yylineno,identifier);
        exit(0);
    } 
    for(auto it=scopes.rbegin();it<scopes.rend()-1;it++){
        auto& scope = *it;
        if(scope.find(identifier)!=scope.end()){
            return scope[identifier].type;
        }
    }
    output::errorUndef(yylineno,identifier);
    exit(0);
    
    // some error
}
void addArguments(const string& identifier){
    //cout << "addArguments" << identifier << endl;
    auto& x=scopes[0][identifier];
    auto& current_scope = scopes.back();
    auto& variables = scopes_variables.back();
    for(auto& variable: variables){
        x.arguments.push_back(current_scope[variable].type);
    }
    offsets.back()=0;
}
void insertToScope(const string& identifier,const string& type){
    // cout << "insertToScope" << identifier << endl;
    for(auto it=scopes.rbegin();it<scopes.rend();it++){
        auto& scope = *it;
        if(scope.find(identifier)!=scope.end()){
            output::errorDef(yylineno,identifier);
            exit(0);
        }
    }
    auto& last = scopes.back();
    int& offset = offsets.back();
    //cout << "insertToScope" << identifier << type << global<<offset<< endl;
    last[identifier]={type,vector<string>(),offset};
    scopes_variables.back().push_back(identifier);
    if(scopes.size()>1){
        if(offset<0){
            offset--;
        } else {
            offset++;
        }
    } /*else {
        if(identifier=="main" && type != "VOID"){
            output::errorMainMissing();
            exit(0);
        }
    }*/
}
bool validCast(const string& type1,const string& type2){
    if(type1==type2)
        return true;
    if(type1=="INT" && type2 == "BYTE")
        return true;
    return false;
    
}
void checkCall(Token* token,ExpressionList* list){
    if(scopes[0].find(token->lexeme)==scopes[0].end()){
        output::errorUndefFunc(yylineno,token->lexeme);
        exit(0);
    }
    auto& arguments=scopes[0][token->lexeme].arguments;
    int expectedSize=arguments.size();
    int gotSize = list ? list->types.size() : 0;
    if(expectedSize!=gotSize){
        output::errorPrototypeMismatch(yylineno,token->lexeme,arguments);
        exit(0);
    }
    for(int i=0;i<arguments.size();i++){
        if(!validCast(arguments[i],list->types[i])){
            output::errorPrototypeMismatch(yylineno,token->lexeme,arguments);
            exit(0);
        }
    }
}
void checkExpressionType(const string& type1,const string& type2,bool symetric){
    if(!validCast(type1,type2) && (!symetric || !validCast(type2,type1))){
        output::errorMismatch(yylineno);
        exit(0);
    }
}
void checkReturn(Expression* exp){
    auto& current_func = scopes[0][scopes_variables[0].back()];
    string type;
    if(!exp){
        type="VOID";
    } else {
        type=exp->type;
    }
    checkExpressionType(current_func.type,type);

}
void checkByteRange(Token* token){
    int num = stol(token->lexeme);
    if(num<0 || num >255){
        output::errorByteTooLarge(yylineno,token->lexeme);
        exit(0);
    }
}
string checkArithmetic(Expression* exp1,Expression* exp2){
    string type= "BYTE";
    if(exp1->type=="INT")
        type="INT";
    else if(exp1->type!="BYTE"){
        output::errorMismatch(yylineno);
        exit(0);
    }
    if(exp2->type=="INT")
        type="INT";
    else if(exp2->type!="BYTE"){
        output::errorMismatch(yylineno);
        exit(0);
    }
    return type;
}
void raiseWhileCounter(){
    whileCounter++;
}
void lowerWhileCounter(){
    whileCounter--;
}
void checkContinue(){
    if(whileCounter<=0){
        output::errorUnexpectedContinue(yylineno);
        exit(0);
    }
}
void checkBreak(){
    if(whileCounter<=0){
        output::errorUnexpectedBreak(yylineno);
        exit(0);
    }
}