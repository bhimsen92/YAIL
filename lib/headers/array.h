/**
    The following code implements the Array data type. Right now only one dimensional arrays are supported.
    created by: Bhimsen S K [bhimsen.pes@gmail.com]

    Array class is a subclass List class which in turn is a subclass of Object[the root object for all types]
    List class exist just to create hirarchy.
    Array class is based on C++'s vector data type, and supports addition, slicing and index operation.
*/
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
            // appends an item at the end of the array.
            void push_back( Object *item ){
                vector<Object*> *array = value->getYailArrayVal();
                if( array == NULL ){
                    array = new vector<Object*>();
                    value->setYailArrayVal( array );
                }
                array->push_back( item );
                length++;
            }
            // returns the specified element from the array[given by the index]
            Object* index( int i ){
                Object* rval = NULL;
                if( i < length ){
                    vector<Object*> *array = value->getYailArrayVal();
                    rval = (*array)[i];
                }
                return rval;
            }
            // returns a subarray from the source array.
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

            // returns the length of the array.
            int getLength(){
                return length;
            }
            
            // creates a copy of the array, needed while creating closure.
            Object* getCopy(void){
                Array *arr = new Array(this->getDataType(), length);
                for(int i = 0; i < length; i++){
                    arr->push_back(index(i));
                }
                return arr;
            }
    };
}
#endif