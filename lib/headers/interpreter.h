#include<iostream>
#include<cstdlib>
#include<vector>
#include<string>
#include<cstring>
#include<map>
#include<stack>
#include<pthread.h>
#include<queue>
#include<cstdio>
#include<cstdlib>
#include<unistd.h>

#include "bnKapi.h"
#include "node.h"
#include "tokens.h"
#include "context.h"
#include "object.h"
#include "binaryop.h"

using namespace std;
using namespace bnk_astNodes;
//using namespace bnk_builtins;

#ifndef __INTERP
#define __INTERP

#define ISINSIDE_FUNCTION ( insideFunctionCounter > 0 )
#define INSIDE_FUNCTION   ( insideFunctionCounter++ )
#define OUTSIDE_FUNCTION  ( insideFunctionCounter-- )
#define NOTSAME( str1, str2 ) if( strcmp( str1, str2 ) )

class Job;

typedef unsigned int uint;
class Mutex{
        private:
            pthread_mutex_t this_lock;
        public:
            Mutex();
            ~Mutex(); 
            void lock(); 
            void unlock();
};

class ThreadManager{
        private:
            Mutex mutex0, mutex1, mutex2;
            bool running;
            uint thread_num;
            uint running_jobs;
            queue<Job*> jobs;
            pthread_t *threads; 

        public: 
            ThreadManager (uint size);
            ~ThreadManager (); 

            uint size();        /* the job size in Thread Manager      */
            void append(Job*); /* append a job to the queue          */
            void sync();        /* wait till all the jobs are done    */
            void worker();      /* the slave process to fetch and run */
};

class Interpreter{
    private:
            map<string, BuiltInFunction> builtins;
            stack<Job*> jobStack;
            static ThreadManager *threadManager;
            int insideFunctionCounter;
            bool mainThread;
    public:
        Interpreter(bool isMainThread = false){
            this->loadBuiltIns();
            insideFunctionCounter = 0;
            mainThread = isMainThread;
            if(threadManager == NULL)
                threadManager = new ThreadManager(64);
        }
        bool isCallable( Object* obj );
        bnk_types::Object* evaluate( Node* astNode, Context* execContext, int dataTypeInfo );
        Object* execOperation( Operator* opNode, Context* execContext, BinaryOperation *op );
        bool isBuiltInFunction( Identifier *functName );
        bool isUserDefinedFunction( Identifier *functName, Context *execContext );
        Object* evaluateBuiltInFunction( Identifier *functName, Operands *operands, Context *execContext );
        Object* evaluateUserDefinedFunction( Identifier *functName, Operands *operands, Context *execContext );
        void loadBuiltIns(void);
        BuiltInFunction getBuiltInFunction( Identifier *functName );
        void errorMessage( int size, ... );
        bool isReturnType( Object *obj );

        void spawn(Job *job){
            jobStack.push(job);
            threadManager->append(job);
        }

        void sync(void){
            threadManager->sync();
        }

};

// job has been defined here to avoid cyclic dependency.
class Job {
    protected:
            Node *astNode;
            Context *ctx;
            Interpreter *interp;
            char* ident;
            Object *returnVal;
    public:
            Job(Node* node, Context *context, Interpreter *interpreter){
                astNode = node;
                ctx = context;
                interp = interpreter;
                returnVal = NULL;
            }

            void setIdentifier(char* id){
                ident = id;
            }

            void setReturnValue(Object *rval){
                returnVal = rval;
            }

            char* getIdent(void){
                return ident;
            }

            Object* getReturnValue(void){
                return returnVal;
            }

            void run(){
                //cout<<"Whats wrong...\n";
                returnVal = interp->evaluate(astNode, ctx, -1);
                //cout<<"Nothing wrong..\n";
            }
};
#endif
