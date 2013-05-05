#include "../headers/interpreter.h"

using namespace std;
	Mutex::Mutex() { pthread_mutex_init(&this_lock, NULL); }
	Mutex::~Mutex() { pthread_mutex_destroy(&this_lock); }
	void Mutex::lock() { pthread_mutex_lock(&this_lock); }
	void Mutex::unlock() { pthread_mutex_unlock(&this_lock); }

	void *wrapper(void *param) 
	{
		ThreadManager *t = (ThreadManager *) param;
		t->worker();
		return NULL;
	}

	ThreadManager::ThreadManager(uint size):thread_num(size) 
	{
		running = true;
		running_jobs = 0;
		if (size > 10000000) {
			fputs("The thread_num is too big\n", stderr);
			exit(1);
		}

		threads = new pthread_t[size];
		for (uint i = 0; i < size; i++) {
			int rc = pthread_create(&threads[i], NULL, wrapper, (void *)this);
			if(rc != 0){
				fputs("Error while creating the thread...", stderr);
				exit(1);
			}
		}
	}

	ThreadManager::~ThreadManager()
	{
		this->sync();
		running = false;
		for (uint i = 0; i < thread_num; i++) {
			if (pthread_join(threads[i], NULL) != 0) {
				fprintf(stderr, "joined the %d thread error\n", i);
				exit(1);
			}
		}
		fprintf(stderr, "joined all %d threads\n", thread_num);

		delete []threads;
	}

	void ThreadManager::sync() 
	{
		while (running_jobs > 0) { usleep(10); }
	}

	void ThreadManager::decrementJobNo(){
		mutex2.lock();
		running_jobs--;
		mutex2.unlock();
	}

	uint ThreadManager::size() 
	{
		return running_jobs;
	}

	void ThreadManager::worker() 
	{
		for (; running; usleep(10)) {

			mutex1.lock();
			Job *ajob = NULL;
			if (jobs.size() > 0) {
				//cout<<"New job feched...\n";
				ajob = jobs.front();
				jobs.pop();
			}
			mutex1.unlock();

			if (ajob) {	//succ acquire a Job
				//cout<<"I am about to run the job...\n";
				ajob->run();
				//cout<<"job finished working...\n";
				mutex2.lock();
				ajob->setThreadId(pthread_self());
				ajob->setThreadSetFlag(true);				
				running_jobs--;
				mutex2.unlock();
			}
		}
	}

	void ThreadManager::append(Job * ajob) 
	{
		mutex0.lock();
		while (jobs.size() > this->thread_num * 2) {
			//cout<<"Waiting...."<<endl;
			usleep(10);
		}
		running_jobs++;
		jobs.push(ajob);
		mutex0.unlock();
	}
