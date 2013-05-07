/**
    The following code contains implementation of the interpreter for this language.
    It process the AST[Abstract Syntax Tree] built by the parser.
    Parser embeds enough information in the nodes so that interpreter knows what needs to be
    done with that node.
    For example: 
        Int a = 1 + 2;
        Parser builds following tree.
        var_def = {
                        var_list : [ 
                                        assignment_node : {
                                                             identifer : "a",
                                                             expression : {
                                                                                OperatorNode : {
                                                                                                    op : '+',
                                                                                                    op1 : 1,
                                                                                                    op2 : 2
                                                                                               }
                                                                         }
                                                          }
                                   ]
                  }
        Now the interpreter recursively traverses each node and on each node it fires an action which is specified 
        and identified by case blocks in the following code.
        So when it sees a var_def node, First it gets the var_list node from the current node, iterate through it, 
        executing each node in turn. When it sees an assignment node, Interpreter knows that it needs to create 
        a varible so it first fecthes the identifier from the current node and then evaluates the expression.
        Now the expression involves addition operation, the interpreter evaluates it, the sum is returned as an Integer
        object which is a subclass of Object. Now interpreter has the value, it checks whether the name "a" already
        exists in the context, if it does, it will through an error, otherwise it will insert that name and value into
        the hash table.

        Function Definition[funct_def case block]:
        The same process happens when Interpreter sees a function definition.
        For example.
        function add(Int a, Int b):Int{
            return a + b;
        }
        The parser builds the following subtree.
        funct_def : {
                        name : add,
                        formalparameterlist : [ identifier, identifier ], # arglist is made up of expressions
                        returnType : INTEGER_T, # instance of Type object
                        statementlist : [ statmements, statmenets, ... ]
                    }
        Now interpreter creates a UserDefinedFunctionObject object and stores the above information into it.
        If the function is inside a function, then a closure is formed, So the enclosing environment is also
        Stored in this UserDefinedFunctionObject. Unlike javascript, Here values will be copied and not the references.
        The statment list is not evaluated and are evaluated only when function is called.
        Interpreter inserts the name of the function and UserDefinedFunctionObject into the symbol table.
    
        Function Call[funct_call case block]:
        For example:
            add(1, 3);
            parser builds the following tree:
            funct_call : {
                            name : "add",
                            arglist : [ expression, expression, ... ]
                         }
            Interpreter evaluates all the expressions in the argument list and check their types against the one
            defined during the function definition of "add" function. If they do not match error is thrown, execution
            is halted. Otherwise execution proceeds and the statments inside the function are evaluated.
            The funct_call case block contains other more information regarding this.

    created by : Bhimsen S K.
        
*/
#include<iostream>
#include<cstdlib>
#include<vector>
#include<string>
#include<cstring>
#include<cstdarg>
#include<map>
#include "headers/object.h"
#include "headers/string.h"
#include "headers/number.h"
#include "headers/udf.h"
#include "headers/array.h"
#include "headers/bool.h"
#include "headers/builtins.h"
#include "headers/binaryop.h"
#include "headers/interpreter.h"

using namespace std;
ThreadManager* Interpreter::threadManager = NULL;

bnk_types::Object* Interpreter::evaluate( Node* astNode, Context* execContext, int dataTypeInfo, Identifier *lId ){
    int nodeType = astNode->getType();
    switch( nodeType ){
        case __identifier:
                            bnk_astNodes::Identifier *ident;
                            ident = CAST_TO( bnk_astNodes::Identifier, astNode );
                            if( ident != NULL ){
                                string varName = ident->getName();
                                Object* rval = execContext->get(varName);
                                if( rval != NULL ){
                                    return rval;
                                }
                                else{
                                    errorMessage( 2, "Undefined variable.", ident->getName() );
                                    exit(1);
                                }
                            }
                            break;
        case __string:
                            bnk_astNodes::String *str;                                    
                            str = CAST_TO( bnk_astNodes::String, astNode );
                            if( str != NULL ){
                                return new bnk_types::String( str->getString() );
                            }
                            break;
        case __integer:
                            bnk_astNodes::Integer *integer;
                            integer = CAST_TO( bnk_astNodes::Integer, astNode );
                            if( integer != NULL ){
                                return new bnk_types::Integer( integer->getValue() );
                            }
                            break;
        case __boolean:
                            {
                                bnk_astNodes::Bool *b;
                                b = CAST_TO(bnk_astNodes::Bool, astNode);
                                if(b != NULL){
                                    return new bnk_types::Boolean(b->getValue());
                                }
                            }
                            break;
        case __nothing:
                            bnk_astNodes::Nothing *nothing;
                            nothing = CAST_TO( bnk_astNodes::Nothing, astNode );
                            if( nothing != NULL ){
                                return new bnk_types::Nothing( nothing->getValue() );
                            }
                            break;
        case __spawn: 
                      {
                            // get the operator node.
                            //cout<<"I am in spawn block..\n";
                            Operator *spawnOp = CAST_TO(Operator, astNode);
                            // get the operands.
                            Operands *ops = spawnOp->getOperands();
                            // create a new job.
                            Job *task = new Job(ops->get(0), execContext, new Interpreter());
                            task->setIdentifier(lId);
                            // spawn the thread.
                            this->spawn(task);
                            return NULL;
                      }

        case __sync: 
                      {
                            // issue sync command to the interpreter.
                            this->sync();
                            return NULL;
                      }
                            
        case __array_list:
                            bnk_astNodes::ValueList *vlist;
                            Array *array;
                            int checkType;
                            vlist = CAST_TO( bnk_astNodes::ValueList, astNode );
                            if( vlist != NULL ){
                                array = new Array(dataTypeInfo, vlist->getLength());
                                int length = vlist->getLength(), i;
                                Object *val;
                                if(dataTypeInfo == __array_int_t)
                                    checkType = __integer_t;
                                else if(dataTypeInfo == __array_double_t)
                                    checkType = __double_t;
                                // i have forgotten why i had added this following code. o_O
                                else if( dataTypeInfo == __integer_t || dataTypeInfo == __double_t)
                                    checkType = dataTypeInfo;
                                else
                                    checkType = -1;
                                for( i = 0; i < length; i++ ){
                                    val = this->evaluate( vlist->get(i), execContext, -1 );
                                    if(checkType == -1){
                                        checkType = val->getDataType();
                                    }
                                    if(val->getDataType() == checkType){
                                        array->push_back(val);
                                    }
                                    else{
                                        errorMessage(1, "variable is not an array.");
                                        exit(1);
                                    }
                                }
                            }
                            if(dataTypeInfo == -1){
                                if(checkType == __integer_t)
                                    array->setDataType(__array_int_t);
                                else if(checkType == __double_t)
                                    array->setDataType(__array_double_t);
                                else{
                                    array->setDataType(__array_empty_t);
                                }
                            }
                            return array;
        case __indexOp:
                            {
                                Operator *indexOperand = CAST_TO(Operator, astNode);
                                Operands *ops = indexOperand->getOperands();
                                // get the identifier.
                                Identifier *id = CAST_TO(Identifier, ops->get(0));
                                string varName = id->getName();
                                // get the index value.
                                bnk_types::Integer *integer = CAST_TO(bnk_types::Integer, this->evaluate(ops->get(1), execContext, dataTypeInfo));
                                Array *array = CAST_TO(Array, execContext->get(varName));
                                Object *rval = NULL;
                                if(array != NULL){
                                    if(integer != NULL){
                                        rval = array->index(integer->getValue()->getIntVal());
                                        if(rval != NULL){
                                            return rval;
                                        }
                                        else{
                                            errorMessage(1, "ArrayOutOfBoundException...");
                                            exit(1);
                                        }
                                    }
                                    else{
                                        errorMessage(1, "Index has to be an integer...");
                                        exit(1);
                                    }
                                }
                            }
        case __sliceOp:
                            {
                                Operator *sliceOp = CAST_TO(Operator, astNode);
                                Operands *ops = sliceOp->getOperands();
                                // get the identifier node.
                                Identifier *id = CAST_TO(Identifier, ops->get(0));
                                Array *array = CAST_TO(Array, execContext->get(string(id->getName())));
                                if(array == NULL){
                                    errorMessage(1, "Variable needs to be an array for slice operation.");
                                }
                                // get the first expression node.
                                Node *firstOp = ops->get(1);
                                Node *secondOp = ops->get(2);
                                if(firstOp == NULL && secondOp == NULL){
                                    errorMessage(1, "Invalid slice operation.");
                                    exit(1);
                                }
                                else if(firstOp == NULL){
                                    // evaluate the secondOp.
                                    Object *index_2 = this->evaluate(secondOp, execContext, dataTypeInfo);
                                    if(index_2->getDataType() == __integer_t){
                                        return array->slice(NULL, index_2);
                                    }
                                }
                                else if(secondOp == NULL){
                                    // evaluate the firstOp.
                                    Object *index_1 = this->evaluate(firstOp, execContext, dataTypeInfo);
                                    if(index_1->getDataType() == __integer_t){
                                        return array->slice(index_1, NULL);
                                    }
                                }
                                else{
                                    // both operands are specified.
                                    Object *index_1 = this->evaluate(firstOp, execContext, dataTypeInfo);
                                    Object *index_2 = this->evaluate(secondOp, execContext, dataTypeInfo);
                                    if(index_1->getDataType() == __integer_t && index_2->getDataType() == __integer_t){
                                        return array->slice(index_1, index_2);
                                    }
                                }
                            }
                            break;
        case __memberShipOp:
                            {
                                Operator *memberOp = CAST_TO(Operator, astNode);
                                Operands *ops = memberOp->getOperands();
                                // get the identfier.
                                Identifier *id = CAST_TO(Identifier, ops->get(0));
                                // get the member operator.
                                Identifier *member = CAST_TO(Identifier, ops->get(1));
                                // make sure that member is "length" and "id" is an array.
                                Array *arr = CAST_TO(Array, execContext->get(string(id->getName())));
                                if(arr != NULL){
                                    char *mem = member->getName();
                                    if(strcmp("length", mem) == 0){
                                        return new bnk_types::Integer(arr->getLength());
                                    }
                                    else{
                                        errorMessage(1, "Invalid member operator.");
                                        exit(1);
                                    }
                                }
                            }
                            break;
        case __double:
                            bnk_astNodes::Double *realVal;
                            realVal = CAST_TO( bnk_astNodes::Double, astNode );
                            if( realVal != NULL ){
                                return new bnk_types::Double( realVal->getValue() );
                            }
                            break;
        case __return:
                            if( ISINSIDE_FUNCTION ){
                                Operator *returnNode = CAST_TO( Operator, astNode );
                                Operands *operands = returnNode->getOperands();
                                // construct a return object.
                                ReturnValue *value = new ReturnValue( this->evaluate( operands->get(0), execContext, -1 ) );
                                return value;
                            }
                            else{
                                errorMessage( 1, "return have to used inside a function..." );
                                exit(1);
                            }
                            break;
        case __if:
                            // evaluate the conditionalExpression node,
                            // get the truthValue, if it is true, evaluate the statements that come inside if block
                            // else evaluate either else or elif node.
                            bnk_astNodes::Operator *ifNode;
                            ifNode = CAST_TO( bnk_astNodes::Operator, astNode );
                            if( ifNode != NULL ){
                                // get the operands
                                Operands *operands = ifNode->getOperands();
                                // get the cond node.
                                Object *booleanValue = this->evaluate( operands->get(0), execContext, -1 );
                                bool truthValue = booleanValue->getValue()->getBooleanValue();
                                Object *tmpObj;                                
                                if( truthValue ){
                                    // get the block node.
                                    Node *blockNode = operands->get(1);
                                    if( blockNode->getType() == __stmtlist ){
                                        StatementList *stmtList = CAST_TO( bnk_astNodes::StatementList, blockNode );
                                        // evaluate the statment list.
                                        int length = stmtList->getLength(), i;
                                        for( i = 0; i < length; i++ ){
                                            tmpObj = this->evaluate( stmtList->get(i), execContext, -1 );
                                            if( this->isReturnType( tmpObj ) ){
                                                return tmpObj;
                                            }
                                        }
                                    }
                                    else{
                                        // evaluate single statement.
                                        tmpObj = this->evaluate( blockNode, execContext, -1 );
                                        if( this->isReturnType( tmpObj ) ){
                                            //errorMessage( 1, "In else, return object seen..." );
                                            return tmpObj;
                                        }
                                    }
                                }
                                else{
                                    // pop the blockNode.
                                    //operands->pop_front();
                                    // evaluate the elseNode block.
                                    tmpObj = this->evaluate( operands->get(2), execContext, -1 );
                                    if( this->isReturnType( tmpObj ) ){
                                        return tmpObj;
                                    }
                                    //operands->pop_front();
                                }
                            }
                            break;
        case __else:
                            bnk_astNodes::Operator *elseNode;
                            elseNode = CAST_TO( bnk_astNodes::Operator, astNode );
                            if( elseNode != NULL ){
                                // get the operands.
                                Operands *operands = elseNode->getOperands();                                
                                Node *blockNode = operands->get(0);
                                Object *tmpObj;
                                if( blockNode->getType() == __stmtlist ){
                                    StatementList *stmtList = CAST_TO( StatementList, blockNode );
                                    // evaluate the statement list.
                                    int length = stmtList->getLength(), i;
                                    for( i = 0; i < length; i++ ){
                                        tmpObj = this->evaluate( stmtList->get(i), execContext, -1 );
                                        if( this->isReturnType( tmpObj ) ){
                                            return tmpObj;
                                        }
                                    }
                                }
                                else{
                                    // evaluate single statement.
                                    tmpObj = this->evaluate( blockNode, execContext, -1 );
                                    if( this->isReturnType( tmpObj ) ){
                                        return tmpObj;
                                    }
                                }
                            }
                            break;
        case __elif:
                            bnk_astNodes::Operator *elifNode;
                            elifNode = CAST_TO( bnk_astNodes::Operator, astNode );
                            bnk_astNodes::Operator *_ifNode;
                            _ifNode = new Operator( __if, elifNode->getOpsLength(), elifNode->getOperands() );
                            return this->evaluate( _ifNode, execContext, -1 );
                            break;
        case __var_definition:
                                    int dataType;
                                    Operator *varDefinitionNode;
                                    varDefinitionNode = CAST_TO( Operator, astNode );
                                    if( varDefinitionNode != NULL ){
                                      // get the operands.
                                      Operands *operands = varDefinitionNode->getOperands();
                                      // get the datatype of the operands.
                                      Type *dataTypeNode = CAST_TO( Type, operands->get(0) );
                                      if( dataTypeNode != NULL ){
                                        dataType = dataTypeNode->getDataType();
                                      }
                                      // get the variableDeclaration list.
                                      VariableList *vlist = CAST_TO( VariableList, operands->get(1) );
                                      if( vlist != NULL ){
                                        // go through each variable declarations and evaluate them.
                                        int length = vlist->getLength();                                        
                                        for( int i = 0; i < length; i++ ){
                                          //if( !vlist->empty() ){
                                            this->evaluate( vlist->get(i), execContext, dataType );
                                          //}
                                        }
                                      }
                                    }
                                    break;
        case __assignment:
                                Operator *assignmentNode;
                                assignmentNode = CAST_TO( Operator, astNode );
                                if( assignmentNode != NULL ){
                                  Operands *operands = assignmentNode->getOperands();
                                  // getType.
                                  int dataType = dataTypeInfo;
                                  //operands->pop_front();
                                  Identifier *id = CAST_TO( Identifier, operands->get(1) );
                                  if( id != NULL ){
                                    //operands->pop_front();
                                    if( !execContext->isBound( id ) ){
                                        // get the expression node.
                                        if(operands->get(2)->getType() == __spawn){
                                            this->evaluate( operands->get(2), execContext, dataType, id );
                                        }
                                        else{
                                            Object *value = this->evaluate( operands->get(2), execContext, dataType );
                                            // check whether the type of the expression matches
                                            // with the defined type.
                                            if( dataType == value->getDataType() ){
                                                execContext->put( string( id->getName() ), value );
                                            }
                                            else if(dataType == __array_int_t && value->getDataType() == __array_empty_t ){
                                                execContext->put( string( id->getName() ), value );   
                                            }
                                            else{
                                                errorMessage( 1, "Type of the expression does not match with defined type." );
                                                exit(1);
                                            }
                                        }
                                    }
                                    else{
                                        errorMessage( 2, "multiple declarations of variable: ", id->getName() );
                                        exit(1);
                                    }
                                  }
                                }
                                break;
        case __funct_def:
                                Operator *functDefNode;
                                functDefNode = CAST_TO( Operator, astNode );
                                if( functDefNode != NULL ){
                                  // get the operands
                                  Operands *operands = functDefNode->getOperands();
                                  Identifier  *functName = CAST_TO( Identifier, operands->get(0) );
                                  if( functName != NULL && !execContext->isBound( functName ) ){
                                    UserDefinedFunction *funct = new UserDefinedFunction( operands );
                                    execContext->put( string(functName->getName()), funct );
                                    //cout<<"defining: "<<functName->getName()<<endl;
                                    if( ISINSIDE_FUNCTION ){
                                        // if so, a closure needs to be formed.
                                        // copy the current context into the function as closureLink.
                                        funct->createClosure( execContext );
                                        //cout<<"Inside function: "<<execContext->get(string("x"))->getValue()->getIntVal()<<endl;                                        
                                        if( execContext->hasEnclosingContextSet() ){
                                            //cout<<"I am in Hell..\n";
                                            // if the existing context has already has closure link.
                                            // then add this to the current function closure.
                                            // name here is misleading, i am too lazy to change it :D
                                            funct->createClosure( execContext->getEnclosingContext() );
                                        }
                                    }
                                  }
                                  else{
                                      errorMessage( 2, "Multiple Declarations name: ", functName->getName() );
                                  }
                                }
                                break;
        case __funct_call:
                                INSIDE_FUNCTION;
                                Operator *functCallNode;
                                functCallNode = CAST_TO( Operator, astNode );
                                if( functCallNode != NULL ){
                                  Operands *operands = functCallNode->getOperands();
                                  // get the function name.
                                  Identifier *functName = CAST_TO( Identifier, operands->get(0) );
                                  if( functName != NULL ){
                                    if( this->isBuiltInFunction( functName ) ){
                                      return this->evaluateBuiltInFunction( functName, operands, execContext );
                                    }
                                    else if( this->isUserDefinedFunction( functName, execContext ) ){
                                      // get the function object from the current context.
                                      //cout<<"In user defined function...\n";
                                      UserDefinedFunction *f = CAST_TO(UserDefinedFunction, execContext->get(string(functName->getName())));
                                      // get the formal parameter list
                                      FormalParameterList *fplist = f->getFormalParameterList();
                                      // get the arglist from function object.
                                      ArgumentList *farglist =  f->getArgumentList();
                                      // get arglist from current astNode.
                                      ArgumentList *arglist = CAST_TO(ArgumentList, operands->get(1));
                                      int argLength = farglist->getLength() + arglist->getLength(),
                                          fpLength = fplist->getLength();
                                      //cout<<"function_name: "<<functName->getName()<<endl;
                                      //cout<<"arglength: "<<arglist->getLength()<<endl;
                                      //cout<<"farglength: "<<farglist->getLength()<<endl;
                                      ArgumentList *newArglist = new ArgumentList();
                                      for(int i = 0; i < farglist->getLength(); i++){
                                        newArglist->push_back(farglist->get(i));
                                      }
                                      for(int i = 0; i < arglist->getLength(); i++){
                                        newArglist->push_back(arglist->get(i));
                                      }
                                      if(argLength < fpLength){
                                        // it is a currying case.
                                        // create a new UserDefinedFunction object, add these args to the existing
                                        // arglist and return the object to the caller.
                                        UserDefinedFunction *curriedFunction = new UserDefinedFunction(f->getFunctionName(),
                                            f->getFormalParameterList(), f->getReturnType(), f->getStatementList(), f->getClosureContext());
                                        curriedFunction->setArgumentList(newArglist);
                                        //cout<<"Good work\n";
                                        return curriedFunction;
                                      }
                                      else if(argLength == fpLength){
                                        // set new arglist in current operands object.
                                        Operands *ops = new Operands();
                                        for(int i = 0; i < operands->size(); i++){
                                            ops->push_back(operands->get(i));
                                        }
                                        ops->set(1, newArglist);
                                        Object *rval = this->evaluateUserDefinedFunction( functName, ops, execContext );
                                        OUTSIDE_FUNCTION;
                                        return rval;
                                      }        
                                    }
                                    else{
                                      errorMessage( 2, "Undefined function: ", functName->getName() );
                                      exit(1);
                                    }
                                  }
                                }
                                OUTSIDE_FUNCTION;
                                break;
        case __addition:
                                    // cast to Operator Node.
                                    Operator *addNode;
                                    addNode = CAST_TO( bnk_astNodes::Operator, astNode );
                                    return this->execOperation( addNode, execContext, new AdditionOperation() );
        case __subtraction:
                                    Operator *subNode;
                                    subNode = CAST_TO( bnk_astNodes::Operator, astNode );
                                    return this->execOperation( subNode, execContext, new SubtractionOperation() );
        case __multiplication:
                                    Operator *mulNode;
                                    mulNode = CAST_TO( bnk_astNodes::Operator, astNode );
                                    return this->execOperation( mulNode, execContext, new MultiplicationOperation() );
        case __div:
                                    Operator *divNode;
                                    divNode = CAST_TO( bnk_astNodes::Operator, astNode );
                                    return this->execOperation( divNode, execContext, new DivOperation() );
        case __modulo:
                                    Operator *modNode;
                                    modNode = CAST_TO(bnk_astNodes::Operator, astNode);
                                    return this->execOperation(modNode, execContext, new ModuloOperation());
        case __power:
                                    break;
        case __or:
                                    Operator *orNode;
                                    orNode = CAST_TO( bnk_astNodes::Operator, astNode );
                                    return this->execOperation( orNode, execContext, new OrOperation() );
        case __and:
                                    Operator *andNode;
                                    andNode = CAST_TO( bnk_astNodes::Operator, astNode );
                                    return this->execOperation( andNode, execContext, new AndOperation() );
        case __lt:
                                    Operator *ltNode;
                                    ltNode = CAST_TO( bnk_astNodes::Operator, astNode );
                                    return this->execOperation( ltNode, execContext, new LessThanOperator() );
        case __gt:
                                    Operator *gtNode;
                                    gtNode = CAST_TO( bnk_astNodes::Operator, astNode );
                                    return this->execOperation( gtNode, execContext, new GreaterThanOperator() );
        case __le:
                                    Operator *leNode;
                                    leNode = CAST_TO( bnk_astNodes::Operator, astNode );
                                    return this->execOperation( leNode, execContext, new LessThanOrEqualOperator() );
        case __ge:
                                    Operator *geNode;
                                    geNode = CAST_TO( bnk_astNodes::Operator, astNode );
                                    return this->execOperation( geNode, execContext, new GreaterThanOrEqualOperator() );
        case __equality:
                                    Operator *equalityNode;
                                    equalityNode = CAST_TO( Operator, astNode );
                                    return this->execOperation( equalityNode, execContext, new EqualityOperator() );
        
    }
    return NULL;
}

Object* Interpreter::execOperation( Operator* opNode, Context* execContext, BinaryOperation* op ){
    // get the operands.
    Operands *operands = opNode->getOperands();
    // get the firstOp
    Object *firstOp = this->evaluate( operands->get(0), execContext, -1 );
    //operands->pop_front();
    Object *secondOp = this->evaluate( operands->get(1), execContext, -1 );
    //operands->pop_front();
    // set the operands to the operation object.
    op->setFirstOperand( firstOp );
    op->setSecondOperand( secondOp );
    if( op->isTypeCompatible() ){
        return op->executeOperation();
    }
    else{
        errorMessage( 1, "Incompatible Operands" );
        exit(1);
    }
}

bool Interpreter::isBuiltInFunction( Identifier *functName ){
    string name = functName->getName();
    if( builtins[ name ] != NULL ){
        return true;
    }
    else{
        return false;
    }
}

bool Interpreter::isUserDefinedFunction( Identifier *functName, Context *execContext ){
    //cout<<"In user defined function...\n";
    string name = functName->getName();
    //cout<<"Name: "<<name<<endl;
    Object *value = execContext->get(name);
    //cout<<"Wow it works...\n";
    if( value != NULL ){
        if( this->isCallable( value ) ){
            return true;
        }
    }
    // either the value is not a function or else it does not exist.
    return false;
}

Object* Interpreter::evaluateBuiltInFunction( Identifier *functName, Operands *operands, Context *execContext ){
    list<Object*> *args = new list<Object*>();
    // pop the functName.
    //operands->pop_front();
    // get the argument list.
    ArgumentList *arglist = CAST_TO( ArgumentList, operands->get(1) );
    int length = arglist->getLength();
    for( int i = 0; i < length; i++ ){
        args->push_back( this->evaluate( arglist->get(i), execContext, -1 ) );
        //operands->pop_front();
    }
    BuiltInFunction function = getBuiltInFunction( functName );
    function(args);
    return NULL;
}

Object* Interpreter::evaluateUserDefinedFunction( Identifier *functName, Operands *arguments, Context *execContext ){
    Object *f = execContext->get( functName->getName() ), *rval = NULL;
    UserDefinedFunction *function = CAST_TO( UserDefinedFunction, f );
    Context *newContext = new Context();
    // put the current function object in the new context.
    // so that function name will be available in the new context [ for recursive functions ]
    // and this is done as scope rules are yet to be determined.
    newContext->put( string( functName->getName() ), f );
    // for higher order functions.
    NOTSAME( functName->getName(), function->getFunctionName() ){
        newContext->put( string( function->getFunctionName() ), f );
    }
    // check whether closure exist on this function.
    if( function->closureExist() ){
        // if so, attache the closure context to the current context.        
        newContext->setEnclosingContext(function->getClosureContext());
        //cout<<"Function_Name: "<<function->getFunctionName()<<endl;
        //cout<<"X: "<<newContext->get(string("x"))->getValue()->getIntVal()<<endl;
    }
    else{
        newContext->setEnclosingContext(execContext);
    }
    if( function != NULL ){
        // get formal parameter list.
        FormalParameterList *fpList = function->getFormalParameterList();
        ArgumentList *arglist = CAST_TO( ArgumentList, arguments->get(1) );
        // check whether fpList and argument list length is equal or not.
        if( fpList->getLength() == ( arglist->getLength() ) ){
            // go through each formal parameters, check their type,
            // if everything is OK, then put it inside the new context.
            int i, length = fpList->getLength();
            for( i = 0; i < length; i++ ){
                FormalParameter *fParameter = CAST_TO( FormalParameter, fpList->get(i) );
                Object *argVal = this->evaluate( arglist->get(i), execContext, -1 );
                // check fParameter and argVal type match or not.
                // if not throw error.
                if(fParameter->getDataType() == argVal->getDataType()){
                    newContext->put( string( fParameter->getParameterName() ), argVal );
                }
                else if(fParameter->getDataType() == __array_int_t && argVal->getDataType() == __array_empty_t){
                    newContext->put( string( fParameter->getParameterName() ), argVal );
                }
                else{
                    cout<<"Function name: "<<functName->getName()<<endl;
                    errorMessage( 1, "Type mismatch in function call." );
                    exit(1);
                }
                //arguments->pop_front();
            }
            // get the statement list and start executing the statments.
            StatementList *stmtList = function->getStatementList();
            int stLength = stmtList->getLength();
            Object *tmpObj;
            for( i = 0; i < stLength; i++ ){
                //cout<<"Statement is about to evaluated...\n";
                tmpObj = this->evaluate( stmtList->get(i), newContext, -1 );
                //cout<<"Statement evaluated...\n";
                if( this->isReturnType( tmpObj ) ){
                    ReturnValue *robj = CAST_TO( ReturnValue, tmpObj );
                    if( robj != NULL ){
                        //errorMessage( 1, "In function call, return object seen..." );
                        rval = robj->getObject();
                        break;
                    }
                }
            }
        }
        else{
            errorMessage( 1, "argument length mismatch" );
            exit(1);
        }
    }
    // delete the context.
    //delete newContext;
    return rval;
}

bool Interpreter::isReturnType( Object* obj ){
    if( obj != NULL )
        return obj->getDataType() == __return_t;
    return false;
}

void Interpreter::loadBuiltIns(void){
    builtins[ "print" ] = bnk_builtins::__bprint;
    builtins["newline"] = bnk_builtins::__emit;
}

BuiltInFunction Interpreter::getBuiltInFunction( Identifier *functName ){
    string name = functName->getName();
    return builtins[ name ];
}

void Interpreter::errorMessage( int size, ... ){
    int i;
    char *message;
    va_list args;
    va_start( args, size );
    for( i = 0; i < size; i++ ){
        message = va_arg( args, char* );
        cout<<message;
    }
    cout<<endl;
}

bool Interpreter::isCallable( Object *value ){
    return ( value->getDataType() == __function_t );
}

void Interpreter::sync(void){
    while(!jobStack.empty()){
    // get the job from the stack.
                Job* task = jobStack.front();
                // valid task.
                if(task){
                    // get the thread id.
                    while(!task->set()){
                        //cout<<"Waiting in sync..."<<endl;
                        usleep(10);
                    }
                    pthread_t threadId = task->getThreadId();
                    // i am lazy thats why i am not removing this if else code.[who will do re intendation again boring..]
                    if(true){
                        // get the identifier and the return value.
                        Identifier *id = task->getIdent();
                        if(id != NULL){
                            // get return value.
                            Object *val = task->getReturnValue();
                            if(val != NULL){
                                // get the context object and put the id in it.
                                Context *ctx = task->getContext();
                                ctx->put(string(id->getName()), val);
                            }
                        }
                    }
                }
                jobStack.pop();
            }
            if(threadManager->size() == 0 && mainThread){
                threadManager->sync();
            }
}

void Interpreter::spawn(Job *job){
    jobStack.push(job);
    threadManager->append(job);
}