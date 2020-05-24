#include utils.hpp
std::vector<Scope> scopes;
std::vector<int> offsets;
void createScope(bool is_function){
    scopes.push_Back(Scope());
    if(!is_function){
        offsets.pushback(offsets[offsets.size()-1]);
    } else {
        offsets.pushback(-1);
    }
}
void endScope(){
    output::endScope();
    for(auto& scope : scopes){
        for(auto& item: scope){
             printID(item.first,item.second.offset , item.second.type);
        }
    }
}
const string& getType(const string& identifier){
    for(auto& it=scopes.rbegin();it<scopes.rend();it++){
        if(it.find(identifier)!=it.end()){
            return it[identifier];
        }
    }
    // some error
}
void insertToScope(const string& identifier,const string& type){
    if(false){}
    auto& last = *(scopes.end()-1);
    auto offset = *(offsets.end()-1);
    last[identifier]={type,offset};
    if(offset<0){
        offsets.push_back(offset-1);
    } else {
        offsets.push_back(offset+1);
    }
}