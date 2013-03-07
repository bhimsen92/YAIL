#include<iostream>
#include<cstdlib>
#include<vector>
#include<string>
#include<cstring>
#include<map>
#include "bnKapi.h"
#include "node.h"
#include "tokens.h"
#include "context.h"
#include "object.h"
using namespace std;
using namespace bnk_astNodes;
//using namespace bnk_builtins;

#ifndef __INTERP
#define __INTERP
class Interpreter{
    private:
            map<string, BuiltInFunction> builtins;
    public:
        Interpreter(){
            this->loadBuiltIns();
        }
        bnk_types::Object* evaluate( Node* astNode, Context* execContext, int dataTypeInfo );
        Object* execOperation( int opType, Operator* opNode, Context* execContext );        
        Object* add( Object *a, Object *b );
        Object* sub( Object *a, Object *b );
        Object* mul( Object *a, Object *b );
        Object* div( Object *a, Object *b );
        bool isCompatible( int opType, Object *a, Object *b );
        bool isBuiltInFunction( Identifier *functName );
        bool isUserDefinedFunction( Identifier *functName );
        Object* evaluateBuiltInFunction( Identifier *functName, list<Node*> *operands, Context *execContext );
        Object* evaluateUserDefinedFunction( Identifier *functName, list<Node*> *operands, Context *execContext );
        void loadBuiltIns(void);
        BuiltInFunction getBuiltInFunction( Identifier *functName );
        void errorMessage( const char* message );
};
#endif
