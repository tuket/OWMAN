#ifndef WORK_QUEUE
#define WORK_QUEUE

#include <pthread.h>
#include <list>

/**
 * \brief Thread safe queue
 * This queue can be used concurrently by several threads.
 * It is specially designed for the consumer producer-pattern.
 */

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
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
	}

	T pop()
	{
		pthread_mutex_lock(&mutex);
		while( queue.size() == 0 )
		{
			// this instruction unlocks the mutex automatically
			pthread_cond_wait(&cond, &mutex);
		}
		T elem = queue.front();
		queue.pop_front();
		pthread_mutex_unlock(&mutex);

		return elem;
	};

	~WorkQueue()
	{
		pthread_mutex_destroy(&mutex);
		pthread_cond_destroy(&cond);
	}

};

#endif
