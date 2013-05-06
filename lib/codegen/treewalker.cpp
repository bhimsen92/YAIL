#include<iostream>
#include<cstdlib>
#include<vector>
#include<string>
#include<cstring>
#include<cstdarg>
#include<cstdio>
#include<map>
#include<stack>
#include "./headers/instr.h"
#include "./headers/ir.h"
#include "./headers/treewalker.h"
#include "../headers/node.h"
#include "../headers/context.h"

using namespace std;
using namespace yacl::ast;
using namespace yacl::codegen::ir;

Node* TreeWalker::evaluate( Node* astNode, Context* ctx, Type *dtype ){
    int nodeType = astNode->getType();
    switch( nodeType ){
        case __identifier:
                            // just returning identifier node to the caller.
                            // address calculation are offloaded to IRCode class
                            // methods[keeps things simple].
                            {
                                Identifier *id = CAST_TO(Identifier, astNode);
                                Identifier *rval = CAST_TO(Identifier, ctx->get(id->getName(), 0));
                                if(rval != NULL){
                                    Node *reg;
                                    if(!rval->isInRegister()){
                                        reg = ctx->getRegister();
                                        reg->setDataType(rval->getDataType());
                                        reg->setTypeClass(rval->getTypeClass());
                                        if(reg->hasLocationAdded()){
                                            // get the location, and move the value from
                                            // register to location.
                                            Identifier *location = CAST_TO(Identifier, reg->getLocation());
                                            reg->removeLocation();
                                            location->removeLocation();
                                            ctx->addInstruction(new Move(mov, reg, NULL, location));
                                        }
                                        reg->addLocation(rval);
                                        rval->addLocation(reg);
                                        if(this->isFunction(id)){
                                            ctx->addInstruction(new MoveAddress(mov_address, new String(id->getName()), NULL, reg));
                                        }
                                        else{
                                            ctx->addInstruction(new Move(mov, rval, NULL, reg));
                                        }
                                    }
                                    else{
                                        reg = rval->getLocation();
                                    }
                                    return reg;
                                }
                                else{
                                    errorMessage(1, "Undefined variable: ", id->getName());
                                    exit(1);
                                }
                            }
        case __string:
                            {
                                // generate a label for the string.
                                // create a dataSection object, with type set to "asciz".
                                // add it to the trewalker object, this will be used when it calls
                                // pre() function.
                                // create a register, then generate move instruction, which will
                                // load the address of this label to the generated register.
                                // return the pointer to register which will be further used in other
                                // instructions.
                                String *str = CAST_TO(String, astNode);
                                Label *stringLabel = new Label();
                                //cout<<"Label in string: "<<stringLabel->toString()<<endl;
                                Data *dobj = new Data(stringLabel, _asciz, str);
                                this->addDataObject(dobj);
                                Register *reg = ctx->getRegister();
                                Type *type = new Type(__string, 8);
                                reg->setDataType(type);
                                reg->setTypeClass(Type::getTypeClass(type));
                                ctx->addInstruction(new MoveAddress(mov_address, stringLabel, NULL, reg));
                                return reg;
                            }
                            break;
        case __integer:
                        {
                            Integer *integer;
                            integer = CAST_TO(Integer, astNode);
                            // create new Register.[uses current unused register]
                            Node *reg = ctx->getRegister();
                            if(reg == NULL){
                                cout<<"Its null i am dead..."<<endl;
                            }
                            reg->setDataType(new Type(__integer, 8));
                            reg->setTypeClass(NumberClass);
                            if(reg->hasLocationAdded()){
                                Identifier *location = CAST_TO(Identifier, reg->getLocation());
                                reg->removeLocation();
                                location->removeLocation();
                                ctx->addInstruction(new Move(mov, reg, NULL, location));                                
                            }
                            ctx->addInstruction(new Move(mov, integer, NULL, reg));
                            //this->add(new Move(mov, integer, NULL, reg));
                            // return register which will be used in further expression codegen.
                            return reg;
                        }
        case __nothing:
                            break;
        case __array_list:
                            {
                                // get the value list from the astNode,
                                // then get the length and the type info, 
                                // based on that allocate storage and generate move 
                                // instructions to fill the space.
                                // then return the register which holds the pointer to that
                                // memory address.
                                // the first item of the array would be the length of the array.
                                // so indexing starts from 1 and not 0.
                                ValueList *vlist = CAST_TO(ValueList, astNode);
                                Temp *tmp;
                                int length;
                                int checkType, dataType, dataWidth, multiplier, memory, tp;
                                vector<Node*> rlist;
                                Register *reg;                                
                                if(vlist != NULL){
                                    // get the length.
                                    length = vlist->getLength();
                                    if(dtype != NULL){
                                        //cout<<"Good morning..."<<endl;
                                        dataType = dtype->getDataType();
                                        dataWidth = dtype->getDataWidth();
                                    }
                                    else{
                                        dataType = -1;
                                        dataWidth = 8;
                                    }
                                        if(dataType == __array_int){
                                            checkType = __integer;
                                        }
                                        else if(dataType == __array_double){
                                            checkType = __double;
                                        }
                                        else if(dataType == __integer || dataType == __double){
                                            checkType = dataType;
                                        }
                                        else{
                                            checkType = -1;
                                        }
                                        Node *val;
                                        bool storageAllocated = false;
                                        for(int i = 0; i < length; i++){
                                            val = this->evaluate(vlist->get(i), ctx, dtype);
                                            if(checkType == -1){
                                                checkType = val->getDataType()->getDataType();
                                                multiplier = val->getDataType()->getDataWidth();
                                            }
                                            else{
                                                multiplier = val->getDataType()->getDataWidth();
                                            }
                                            if(val->getDataType()->getDataType() == checkType){
                                                if(!storageAllocated){
                                                    storageAllocated = true;
                                                    memory = (length + 1) * multiplier;
                                                    // generate malloc instruction.
                                                    // address will be in rax register,
                                                    // move the address from rax to some other register.
                                                    // because rax could be used inside other expressions also.
                                                    // then push the length into the first location of the list.
                                                    stack<Register*> *regStack = this->saveRegisters(ctx);
                                                    // load memory size into register rdi.
                                                    Integer *memSize = new Integer(memory);
                                                    Register *regRSI = ctx->getRegister(Register::functReg(0));
                                                    ctx->addInstruction(new Move(mov, memSize, NULL, regRSI));
                                                    ctx->addInstruction(new Call(call, new Identifier((char*)"malloc")));
                                                    // you get the result in rax register.
                                                    // generate a temp register.
                                                    tmp = new Temp(__tmp);
                                                    if(checkType == __integer){
                                                        tp = __array_int;
                                                    }
                                                    else{
                                                        tp = __array_empty;
                                                    }
                                                    Type *t = new Type(tp, multiplier);
                                                    tmp->setDataType(t);
                                                    tmp->setTypeClass(Type::getTypeClass(t));
                                                    Register *raxReg = ctx->getRegister(rax);
                                                    ctx->addTemp(tmp);        
                                                    // generate a move instruction
                                                    ctx->clearAll();
                                                    ctx->clearLocations();
                                                    ctx->addInstruction(new Move(mov, raxReg, NULL, tmp));
                                                    // restore the registers.                                                    
                                                    this->restoreRegisters(ctx, regStack);
                                                    reg = ctx->getRegister();
                                                    // generate a move instruction to move tmp to reg.
                                                    ctx->addInstruction(new Move(mov, tmp, NULL, reg));
                                                    ctx->addInstruction(new Move(mov, new Integer(length), NULL, new Offset(0, reg)));
                                                    tmp->setArrayLength(length);
                                                }
                                            }
                                            else{
                                                errorMessage(1, "variable is not an array...");
                                                exit(1);
                                            }
                                            // generate a move instrcution.tmp->setArrayLength(length);
                                            ctx->addInstruction(new Move(mov, val, NULL, new Offset((i + 1)* multiplier, reg)));
                                            // free val register.
                                            Register *regCasted = CAST_TO(Register, val);
                                            ctx->unsetAvailabilityFlag(regCasted->getRegIndex());
                                        }                         
                                } // vlist not null
                                reg->setDataType(tmp->getDataType());
                                reg->setTypeClass(tmp->getTypeClass());
                                reg->setArrayLength(tmp->getArrayLength());
                                return reg;
                            }
        case __memberShipOp: 
                             {
                                Operator *memOp = CAST_TO(Operator, astNode);
                                Operands *ops = memOp->getOperands();
                                // get the first operands.
                                Identifier *id = CAST_TO(Identifier, ops->get(0));
                                // get the member name.
                                Identifier *mem = CAST_TO(Identifier, ops->get(1));
                                Node *array = ctx->get(string(id->getName()), 0);
                                int type = array->getDataType()->getDataType();
                                //cout<<"type: "<<type<<endl;
                                if(type != __array_int && type != __array_empty){
                                    errorMessage(1, "Name needs to be an array...");
                                    exit(1);
                                }
                                else{
                                    // get the register.
                                    if(strcmp("length", mem->getName()) == 0){
                                        Register *reg = ctx->getRegister();
                                        ctx->addInstruction(new Move(mov, new Integer(array->getArrayLength()), NULL, reg));
                                        return reg;
                                    }
                                    else{
                                        errorMessage(1, "member needs to be length..");
                                        exit(1);
                                    }
                                }
                             }
        case __indexOp:  {
                            // get the operator node.
                            Operator *indexOp = CAST_TO(Operator, astNode);
                            // get the ops.
                            Operands *ops = indexOp->getOperands();
                            // get the indentifier.
                            Identifier *name = CAST_TO(Identifier, ops->get(0));
                            Node *id = ctx->get(string(name->getName()), 0);
                            // get the expression node, evaluate it, make sure it is integer.
                            // then issue an "add" instruction because our first field of the array 
                            // contains the length info.
                            Node *result = this->evaluate(ops->get(1), ctx, dtype);
                            if(result->getDataType()->getDataType() == __integer){
                                // issue an add instruction.
                                ctx->addInstruction(new Add(add, new Integer(1), result, NULL));
                                ctx->addInstruction(new Mul(imul, new Integer(8), result, NULL));
                                // i have the offset.
                                // now get a register and load the address of array into it.
                                Register *arrReg = CAST_TO(Register, id->getLocation());
                                if(arrReg == NULL){
                                    arrReg = ctx->getRegister();
                                    arrReg->addLocation(id);
                                    id->addLocation(arrReg);
                                }
                                ctx->addInstruction(new Move(mov, id, NULL, arrReg));
                                // generate an add instruction.
                                ctx->addInstruction(new Add(add, result, arrReg, NULL));
                                // then generate MoveAtAddress instruction.
                                ctx->addInstruction(new MoveAtAddress(mov_at_address, arrReg, result));
                                result->setDataType(id->getDataType());
                                result->setTypeClass(id->getTypeClass());
                                return result;
                            }
                            else{
                                // index must be an integer.
                                errorMessage(1, "Index of the array must be an integer...");
                                exit(1);
                            }
                         }
        case __double:
                            break;
        case __return:
                            if(ISINSIDE_FUNCTION(this->insideFunctionCounter)){
                                Operator *returnStmt = CAST_TO(Operator, astNode);
                                Operands *ops = returnStmt->getOperands();
                                Register *result = CAST_TO(Register, this->evaluate(ops->get(0), ctx, dtype));
                                // no need to spill if rax is already occupied.
                                // as it is the last statement that will be executed in this context.                                
                                Register *raxReg;
                                if(result && !result->is(rax)){
                                    raxReg = ctx->getRegister(rax);
                                    raxReg->setDataType(result->getDataType());
                                    raxReg->setTypeClass(result->getTypeClass());
                                    ctx->addInstruction(new Move(mov, result, NULL, raxReg));
                                }
                                else{
                                    raxReg = result;
                                }
                                // generate jump label.
                                ctx->addInstruction(new Jump(jmp, new String(ctx->getExitLabel()), NULL, NULL));
                                return astNode;
                            }
                            else{
                                errorMessage(1, "you can not use return statement outside a function.");
                            }
                            break;
        case __if:
                            {
                                Operator *ifNode = CAST_TO(Operator, astNode);
                                if( ifNode != NULL){
                                    // get the operands.
                                    Operands *ops = ifNode->getOperands();
                                    // evaluate the cond node.
                                    // return value would be label to true branch.
                                    Node *truthLabel = this->evaluate(ops->get(0), ctx, dtype);
                                    ctx->clearLocations();
                                    ctx->clearAll();                                    
                                    // get the else node[code which needs to be executed on false truthValue]
                                    Node *nextLabel = this->evaluate(ops->get(2), ctx, dtype);
                                    ctx->clearLocations();
                                    ctx->clearAll();
                                    // generate an unconditional jump node which will get you out of the control
                                    // statement "if else, if elif else."
                                    // emit true branch label name.
                                    ctx->addInstruction(new EmitLabel(emitlabel, truthLabel, NULL, NULL));
                                    Node *rval = this->evaluate(ops->get(1), ctx, dtype);
                                    ctx->clearLocations();
                                    ctx->clearAll();
                                    // generate label for converging the control.
                                    if(nextLabel && nextLabel->getType() != __return)
                                        ctx->addInstruction(new EmitLabel(emitlabel, nextLabel, NULL, NULL));
                                    return rval;
                                }
                                else{
                                    errorMessage(1, "ifNode fail.");
                                    exit(1);
                                }
                            }
                            break;
        case __else:
                            {
                                Operator *elseNode = CAST_TO(Operator, astNode);
                                if(elseNode != NULL){
                                    Operands *ops = elseNode->getOperands();
                                    // evaluate the statement list.
                                    Node *rval = this->evaluate(ops->get(0), ctx, dtype);
                                    Label *nextLabel = new Label();                                    
                                    if(rval != NULL && rval->getType() != __return){
                                        ctx->addInstruction(new Jump(jmp, nextLabel, NULL, NULL));
                                        return nextLabel;
                                    }
                                    else
                                        return rval;
                                }
                                else{
                                    errorMessage(1, "elseNode fail.");
                                    exit(1);
                                }
                            }
                            break;
        case __elif:        {
                                Operator *elifNode = CAST_TO(Operator, astNode);
                                Operands *ops = elifNode->getOperands();
                                // evaluate the cond node.
                                // return value would be label to true branch.
                                Node *truthLabel = this->evaluate(ops->get(0), ctx, dtype);
                                ctx->clearLocations();
                                ctx->clearAll();                                
                                // get the else node[code which needs to be executed on false truthValue]
                                Node *nextLabel = this->evaluate(ops->get(2), ctx, dtype);
                                ctx->clearLocations();
                                ctx->clearAll();
                                // generate an unconditional jump node which will get you out of the control
                                // statement "if else, if elif else."
                                // emit true branch label name.
                                ctx->addInstruction(new EmitLabel(emitlabel, truthLabel, NULL, NULL));
                                Node *rval = this->evaluate(ops->get(1), ctx, dtype);
                                ctx->clearLocations();
                                ctx->clearAll();                                
                                // generate label for converging the control.
                                if(nextLabel && nextLabel->getType() != __return)
                                    ctx->addInstruction(new Jump(jmp, nextLabel, NULL, NULL));
                                return rval;
                            }
                            break;
        case __var_definition:
                                    Operator *varDefNode;
                                    varDefNode = CAST_TO(Operator, astNode);
                                    if(varDefNode != NULL){
                                        // get the type operands object.
                                        Operands *ops = varDefNode->getOperands();
                                        // get the type object.
                                        Type *dataType = CAST_TO(Type, ops->get(0));
                                        if(dataType != NULL){
                                            // get the width.
                                            int dataWidth = dataType->getDataWidth();
                                            // get variable list object.
                                            VariableList *vlist = CAST_TO(VariableList, ops->get(1));
                                            // get the length and calculate the amount of storage that
                                            // needs to allocated.
                                            int allocationSize = dataWidth * vlist->getLength();
                                            // update storage for this context.
                                            ctx->updateStorage(allocationSize);
                                            // go through each variable list and generate instructions for that.
                                            for(int i = 0; i < vlist->getLength(); i++){
                                                this->evaluate(vlist->get(i), ctx, dataType);
                                            }
                                        }
                                    }
                                    break;
        case __assignment:
                                Operator *assignNode;
                                assignNode = CAST_TO(Operator, astNode);
                                if(assignNode != NULL){
                                    Operands *ops = assignNode->getOperands();
                                    // get the identifier node.
                                    Identifier *id = CAST_TO(Identifier, ops->get(1));
                                    // check whether the name is already defined in the current
                                    // context or not.
                                    if(!ctx->isBound(id,0)){
                                        // get the expression node.
                                        Node *expressionNode = ops->get(2);
                                        // generate op code for expression and
                                        // return the result in an temp node.
                                        Node *result = this->evaluate(expressionNode, ctx, dtype);
                                        Type *type = result->getDataType();
                                        id->setDataType(type);
                                        id->setTypeClass(result->getTypeClass());
                                        if(type->getDataType() == __array_int || type->getDataType() == __array_empty){
                                            id->setArrayLength(result->getArrayLength());
                                        }
                                        // add this register to the address descriptor of this identifier.
                                        id->addLocation(result);
                                        // add this id to the register descriptor of the result[register]
                                        result->addLocation(id);
                                        // put the name into the symbol table and its associated object.
                                        ctx->put(id->getName(), id);
                                        // put the id into contexts variables list.
                                        ctx->addVar(id);
                                        // add assignment instruction to contexts instruction list.
                                        // [assigment instruction=> move instruction]
                                        /* THINK ABOUT THE FOLLOWING LINES, looks like there is no need for it.*/
                                        // generate move instruction, if the result is returned in
                                        // rax register, as it will be a result of function call,
                                        // and it can be overwritten in the future.

                                        //ctx->addInstruction(new Move(mov, result, NULL, id));
                                        // assignment instruction returns nothing.
                                        //Register::clearAll();
                                        break;
                                    }
                                    else{
                                        errorMessage(1, "Variable is already defined");
                                        exit(1);
                                    }
                                }
                                break;
        case __funct_def:       {
                                    INSIDE_FUNCTION(this->insideFunctionCounter);
                                    Context *nctx = new Context();
                                    Operator *functNode = CAST_TO(Operator, astNode);
                                    // get the operands.
                                    Operands *ops = functNode->getOperands();
                                    // get the name of the function.
                                    Identifier *functName = CAST_TO(Identifier, ops->get(0));
                                    // get the formal paramter list.
                                    FormalParameterList *fplist = CAST_TO(FormalParameterList, ops->get(1));
                                    // put this info in the current context.
                                    if(!ctx->isBound(functName, 0)){
                                        // standard procedure for functions.
                                        char buffer[512];
                                        sprintf(buffer, "\n.type %s, @function", functName->getName());
                                        nctx->addInstruction(new Emit(emit, new String(buffer)));
                                        nctx->addInstruction(new EmitLabel(emitlabel, new Label(functName), NULL, NULL));
                                        nctx->addInstruction(new Push(push, ctx->getRegister(rbp)));
                                        nctx->addInstruction(new Move(mov, ctx->getRegister(rsp), NULL, ctx->getRegister(rbp)));
                                        Function *f = new Function();
                                        FormalParameter *fp;
                                        for(int i = 0, len = fplist->getLength(); i < len; i++){
                                            fp = CAST_TO(FormalParameter, fplist->get(i));             
                                            // get the name of the parameter.
                                            char* name = fp->getParameterName();
                                            // generate an identifier node.
                                            Identifier *id = new Identifier(name);
                                            Type *t = Type::getType(fp->getDataType());                                            
                                            id->setDataType(t);                   
                                            id->setTypeClass(Type::getTypeClass(t));
                                            if(!nctx->isBound(id,0)){
                                                nctx->put(string(name), id);
                                                Register *functReg = ctx->getRegister(Register::functReg(i));
                                                functReg->setDataType(id->getDataType());
                                                functReg->setTypeClass(id->getTypeClass());
                                                nctx->addInstruction(new Move(mov, functReg, NULL, id));
                                                ctx->unsetAvailabilityFlag(functReg->getRegIndex());
                                                //id->addLocation(functReg);
                                                //functReg->addLocation(id);
                                                // put it paramter list.
                                                nctx->addFunctionParamter(id);
                                                // this information is used while function call
                                                // for matching type information with definition.
                                                f->addParamterType(id);
                                            }
                                        }// all processing of formal paramter is done.
                                        // now process statement list.
                                        Type *returnType = CAST_TO(Type, ops->get(2));
                                        f->addReturnType(returnType);
                                        // put the function info in the current context.
                                        // and in the new context.
                                        this->addFunction(functName);
                                        ctx->put(string(functName->getName()), f);
                                        nctx->put(string(functName->getName()), f);
                                        nctx->attachContext(ctx);
                                        this->evaluate(ops->get(3), nctx, returnType);
                                        nctx->addInstruction(new EmitLabel(emitlabel, new String(ctx->getExitLabel()), NULL, NULL));
                                        nctx->addInstruction(new Move(mov, ctx->getRegister(rbp), NULL, ctx->getRegister(rsp)));
                                        nctx->addInstruction(new Pop(pop, ctx->getRegister(rbp)));
                                        nctx->addInstruction(new Return(ret));
                                        // store this context into the global context list.
                                        this->addContext(nctx);
                                        ctx->clearAll();
                                        OUTSIDE_FUNCTION(this->insideFunctionCounter);
                                    }
                                }
                                break;
        case __funct_call:
                                {
                                    // before making a call first save all the the registers used by the current context.
                                    // check to see whether the function exists or not in the current context.
                                    // if so, evaluate the user defined function.
                                    stack<Register*> *regStack = this->saveRegisters(ctx);
                                    // all registers that got used are spilled.
                                    // or saved on the stack.
                                    Operator *functCallNode = CAST_TO(Operator, astNode);
                                    // get operand list.
                                    Operands *ops = functCallNode->getOperands();
                                    ArgumentList *arglist = CAST_TO(ArgumentList, ops->get(1));
                                    for(int i = 0; i < arglist->getLength() && i < 6; i++){
                                        Node *result = this->evaluate(arglist->get(i), ctx, dtype);
                                        // generate a new register and move the result into
                                        // this register.
                                        Register *functReg = ctx->getRegister(Register::functReg(i));
                                        functReg->setDataType(result->getDataType());
                                        functReg->setTypeClass(result->getTypeClass());
                                        ctx->addInstruction(new Move(mov, result, NULL, functReg));
                                        Register *dummy = CAST_TO(Register, result);
                                        if(dummy != NULL){
                                            ctx->unsetAvailabilityFlag(dummy->getRegIndex());
                                            if(dummy->hasLocationAdded()){
                                                // function args are just expressions,
                                                // they are not going to change any memory locations.
                                                // so no need to generate move instruction, in this case.
                                                Node *loc = dummy->getLocation();
                                                loc->removeLocation();
                                                dummy->removeLocation();
                                            }
                                        }
                                    }
                                    // generate call instruction.
                                    Identifier *functName = CAST_TO(Identifier, ops->get(0));
                                    if(this->isFunction(functName)){
                                        ctx->addInstruction(new Move(mov, new Integer(0), NULL, ctx->getRegister(rax)));
                                        ctx->addInstruction(new Call(call, functName));
                                    }
                                    else{
                                        Node *res = this->evaluate(ops->get(0), ctx, dtype);
                                        ctx->addInstruction(new IndirectCall(call, res));
                                    }
                                    // call is done. restore values stored in the registers.
                                    ctx->clearAll();
                                    ctx->clearLocations();
                                    this->restoreRegisters(ctx, regStack);
                                    Register *returnVal = ctx->getRegister(rax);
                                    Function *f = CAST_TO(Function, ctx->get(string(functName->getName()), 0));
                                    if(f != NULL){
                                        Type *rtype = f->getReturnType();
                                        returnVal->setDataType(rtype);
                                        returnVal->setTypeClass(Type::getTypeClass(rtype));
                                    }
                                    else{
                                        Type *rtype = new Type(__integer, 8);
                                        returnVal->setDataType(rtype);
                                        returnVal->setTypeClass(Type::getTypeClass(rtype));
                                    }
                                    return returnVal;
                                }
                                break;
        case __addition:        {
                                    Operator *addition = CAST_TO(Operator, astNode);
                                    return this->execOperation(addition, ctx, new AdditionOperation(ctx));
                                }
                                break;
        case __subtraction:     {
                                    Operator *subtraction = CAST_TO(Operator, astNode);
                                    return this->execOperation(subtraction, ctx, new SubtractionOperation(ctx));
                                }
                                break;
        case __multiplication:
                                {
                                    Operator *mul = CAST_TO(Operator, astNode);
                                    return this->execOperation(mul, ctx, new MultiplicationOperation(ctx));
                                }
                                break;
        case __div:
                                break;
        case __power:
                                break;
        case __or:
                                break;
        case __and:
                                break;
        case __lt:
                                break;
        case __gt:
                                break;
        case __le:
                                break;
        case __ge:
                                break;
        case __equality:
                                {
                                    //cout<<"In equalityNode..\n";
                                    Operator *equalityNode = CAST_TO(Operator, astNode);
                                    return this->execOperation(equalityNode, ctx, new EqualityOperator(ctx));
                                }
                                break;
        case __stmtlist:
                                {
                                    StatementList *stmtList = CAST_TO(StatementList, astNode);
                                    Node *val = NULL;
                                    if(stmtList != NULL){
                                        int len = stmtList->getLength();
                                        for(int i = 0; i < len; i++){
                                            val = this->evaluate(stmtList->get(i), ctx, dtype);
                                        }
                                        return val;
                                    }
                                }
                                break;
    }
    return NULL;
}

Node* TreeWalker::execOperation(Operator* opNode, Context* ctx, BinaryOperation* op){
    // get the operands from the operator node.
    // evaluate the operands by generating code for them,
    // then, check for type compatibility, if everything seems ok,
    // generate code for executing this operation.
    // temp node generation and generating code for them is offloaded to BinaryOperation subclasses.
    Operands *ops = opNode->getOperands();
    Register *firstOp = CAST_TO(Register, this->evaluate(ops->get(0), ctx, NULL));
    if(firstOp->is(rax)){
        Register *tmp = ctx->getRegister();
        tmp->setDataType(firstOp->getDataType());
        tmp->setTypeClass(Type::getTypeClass(firstOp->getDataType()));
        // generate move instruction.
        ctx->addInstruction(new Move(mov, firstOp, NULL, tmp));
        firstOp = tmp;
    }
    Node *location = firstOp->getLocation();
    Node *secondOp = CAST_TO(Register, this->evaluate(ops->get(1), ctx, NULL));
    if(secondOp->is(rax)){
        Register *tmp = ctx->getRegister();
        tmp->setDataType(secondOp->getDataType());
        tmp->setTypeClass(Type::getTypeClass(secondOp->getDataType()));
        // generate move instruction.
        ctx->addInstruction(new Move(mov, secondOp, NULL, tmp));
        secondOp = tmp;
    }
    Register *reg = CAST_TO(Register, location != NULL ? location->getLocation() : NULL);

    if(reg && firstOp && reg->getRegIndex() == firstOp->getRegIndex())
        op->setFirstOperand(firstOp);
    else if(location)
        op->setFirstOperand(location);
    else
        op->setFirstOperand(firstOp);
    op->setSecondOperand(secondOp);
    if(op->isTypeCompatible()){
        Node *rval = op->executeOperation();
        return rval;
    }
    else{
        errorMessage(1, "Incompatible operands for this operation");
        exit(1);
    }
}

bool TreeWalker::isBuiltInFunction( Identifier *functName ){
}

bool TreeWalker::isUserDefinedFunction( Identifier *functName, Context *ctx ){
}

Node* TreeWalker::evaluateBuiltInFunction( Identifier *functName, Operands *operands, Context *ctx ){
}

Node* TreeWalker::evaluateUserDefinedFunction( Identifier *functName, Operands *arguments, Context *ctx ){
}

bool TreeWalker::isReturnType(Node* node){
}

stack<Register*>* TreeWalker::saveRegisters(Context *ctx){
    stack<Register*> *regStack = new stack<Register*>();
    int index = 0, count = ctx->getRegisterAllocatedLength();
    Register *tmp = ctx->spill();
    while(index < count){
        if(tmp && tmp->hasLocationAdded()){
            // get the location.
            Identifier *location = CAST_TO(Identifier, tmp->getLocation());
            location->removeLocation();
            tmp->removeLocation();
            ctx->addInstruction(new Move(mov, tmp, NULL, location));
        }
        else if(tmp){
            if(tmp && !tmp->is(rsp) && !tmp->is(rbp)){//&& !tmp->is(rax)){// && !tmp->isFree()){
                regStack->push(tmp);
                ctx->addInstruction(new Push(push, tmp));
            }
        }
        tmp = ctx->spill();
        index++;
    }
    return regStack;
}

void TreeWalker::restoreRegisters(Context *ctx, stack<Register*> *regStack){
    while(!regStack->empty()){
        Register *r = regStack->top();
        if(r != NULL){
            ctx->setAvailabilityFlag(r->getRegIndex());
            ctx->addInstruction(new Pop(pop, r));
        }
        regStack->pop();
    }
}

//void TreeWalker::loadBuiltIns(void){
//}

//BuiltInFunction TreeWalker::getBuiltInFunction( Identifier *functName ){
//}

void TreeWalker::errorMessage( int size, ... ){
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

//bool TreeWalker::isCallable( Object *value ){
//    return ( value->getDataType() == __function_t );
//}
