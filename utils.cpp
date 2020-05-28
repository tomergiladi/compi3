#include "utils.hpp"
std::vector<Scope> scopes;
std::vector<vector<string>> scopes_variables;
std::vector<int> offsets;
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
    output::endScope();
    auto& scope = scopes.back();   
    auto& variables = scopes_variables.back();
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
const string& getType(const string& identifier){
    //cout << "getType" << identifier << endl;
    for(auto it=scopes.rbegin();it<scopes.rend();it++){
        auto& scope = *it;
        if(scope.find(identifier)!=scope.end()){
            return scope[identifier].type;
        }
    }
    return temp;
    // some error
}
void addArguments(const string& identifier){
    //cout << "addArguments" << identifier << endl;
    auto& x=scopes[0][identifier];
    auto& current_scope = scopes.back();
    for(auto& it : current_scope){
        x.arguments.push_back(it.second.type);
    }
    *(offsets.end()-1)=0;
}
void insertToScope(const string& identifier,const string& type){
    // cout << "insertToScope" << identifier << endl;
    if(false){}
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
    }
}