#include<iostream>
#include<cstdlib>
#include<pthread.h>
using namespace std;

#ifndef __THREAD
#define __THREAD
class Thread{
    private:
        pthread_t thread_id;
    public:
           Thread(){
           }
           void wait(void){
           }
           void run(void){
           }
};
#endif
