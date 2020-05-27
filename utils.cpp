#include "utils.hpp"
std::vector<Scope> scopes;
std::vector<int> offsets;
string temp="Fsfsa";
void init(){
//    cout << "init" << endl;
    scopes.push_back(Scope());
    offsets.push_back(0);
}
void createScope(bool is_function){
    //cout << "createScope" << is_function << endl;
    scopes.push_back(Scope());
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
    for(auto& item: scope){
            output::printID(item.first,item.second.offset , item.second.type);
    }
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
    auto& current_scope = *(scopes.end()-1);
    for(auto& it : current_scope){
        x.arguments.push_back(it.second.type);
    }
    *(offsets.end()-1)=0;
    // some error
}
void insertToScope(const string& identifier,const string& type,bool global){
    // cout << "insertToScope" << identifier << endl;
    if(false){}
    auto& last = *(scopes.end()-1);
    int& offset = *(offsets.end()-1);
    //cout << "insertToScope" << identifier << type << global<<offset<< endl;
    last[identifier]={type,vector<string>(),offset};
    if(!global){
        if(offset<0){
            offset--;
        } else {
            offset++;
        }
    }
}