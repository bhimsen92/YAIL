#include<iostream>
#include<vector>
#include "object.h"

#ifndef __YAIL_ARRAY
#define __YAIL_ARRAY
using namespace std;

namespace bnk_types{
    class List : public Object{
        public:
                List( int t ) : Object( t, ListClass ){
                }
                Object* getCopy(void){ return NULL; }
    };
    
    class Array : public List{
      private:
            int length, capacity;
      public:
            Array( int _type, int size ) : List( _type ){
                value = new Value();
                capacity = size;
                length = 0;
                vector<Object*> *arr = new vector<Object*>();
                value->setYailArrayVal(arr);
            }
            
            void push_back( Object *item ){
                vector<Object*> *array = value->getYailArrayVal();
                if( array == NULL ){
                    array = new vector<Object*>();
                    value->setYailArrayVal( array );
                }
                array->push_back( item );
                length++;
            }
            
            Object* index( int i ){
                Object* rval = NULL;
                if( i < length ){
                    vector<Object*> *array = value->getYailArrayVal();
                    rval = (*array)[i];
                }
                return rval;
            }

            Object* slice(Object *index_1, Object *index_2){
                int start, end;
                // get the first index value.
                if(index_1 == NULL){
                    start = 0;
                }
                else{
                    start = index_1->getValue()->getIntVal();
                }
                // get the second index value.
                if(index_2 == NULL){
                    end = length;
                }
                else{
                    end = index_2->getValue()->getIntVal();
                }

                Array *arr = new Array(this->getDataType(), end - start + 1);
                for(int i = start; i < end; i++){
                    arr->push_back(index(i));
                }
                return arr;
            }

            int getLength(){
                return length;
            }
            
            Object* getCopy(void){
                return NULL;
            }
    };
}
#endif