#include <pthread.h>
#include <list>

#ifndef WORK_QUEUE
#define WORK_QUEUE

template <typename T>
class WorkQueue
{
	
	std::list<T> queue;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	
public:
	
	WorkQueue()
	{
		pthread_mutex_init(&mutex, 0);
		pthread_cond_init(&cond, 0);
	}
	
	void push(T elem)
	{
		pthread_mutex_lock(&mutex);
		queue.push_back(elem);
	}
	
	~WorkQueue()
	{
		pthread_mutex_destroy(&mutex);
		pthread_cond_destroy(&cond);
	}
	
};

#endif
