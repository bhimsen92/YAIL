#include<iostream>
#include<cstdlib>
#include<vector>
#include "nodes/node.h"
#include "nodes/tokens.h"
#include "context.h"
#include "types/object.h"
#include "types/string.h"
#include "types/number.h"

using namespace std;

#ifndef __INTERP
#define __INTERP

class Interpreter{
    private:
        Context* execContext;
    public:
        Interpreter( Context* ctx ){
            execContext = ctx;
        }
        Object* evaluate( Node* astNode ){
            int opType = astNode->getType();
            switch( opType ){
                case __ident:
                             break;
                case __string:
                              String *string = CAST_TO( String, astNode );
                              if( string != NULL ){
                                return string->getValue();
                              }
                              break;
                case __funct_call:
                                  Operator *functCall = CAST_TO( Operator, astNode );
                                  list<Node*> operands;
                                  vector<Object*> arguments;
                                  if( functCall != NULL ){
                                    operands = functCall->getOperands();
                                    list<Node*>::iterator it = operands.begin();
                                    Identifier *functName = CAST_TO( Identifier, *it );
                                    ++it;
                                    ParameterList *plist = CAST_TO( ParameterList, *it );
                                    if( plist != NULL ){
                                        int len = plist->getLength();
                                        for( int i = 0; i < len; i++ ){
                                            arguments.push_back( evaluate( plist->pop() ) );
                                        }
                                        FunctPTR fun = getFunction();
                                        fun(arguments);
                                    }
                                  }
                                  break;
            }
        }
};
#endif
