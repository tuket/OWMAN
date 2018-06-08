#ifndef WORK_QUEUE
#define WORK_QUEUE

#include <condition_variable>
#include <mutex>
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
	std::mutex mutex;
	std::condition_variable cond;

public:

	WorkQueue()
	{

	}

	void push(T elem)
	{
        mutex.lock();
		queue.push_back(elem);
        cond.notify_one();
        mutex.unlock();
	}

	T pop()
	{
        std::unique_lock<std::mutex> lock(mutex);
		while( queue.size() == 0 )
		{
			// this instruction unlocks the mutex automatically
            cond.wait(lock);
		}
		T elem = queue.front();
		queue.pop_front();

		return elem;
	};

	~WorkQueue()
	{

	}

};

#endif
