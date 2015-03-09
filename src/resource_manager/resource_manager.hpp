#include "resource_table.hpp"
#include "work_queue.hpp"
#include "resource_request.hpp"
#include <pthread.h>
#include <string>

#ifndef RESOURCE_MANAGER
#define RESOURCE_MANAGER

class ResourceManager
{
	
	pthread_t myThread;
	ResourceTable resourceTable;
	WorkQueue<ResourceRequest> workQueue;
	bool stop;
	
public:

	ResourceManager(){}
	
	/**
	 * \brief launches the resurce manger in its own thread
	 */
	void launch();
	
	/**
	 * \brief request a handle to a resouce
	 */
	ResourceText* obtainText(std::string name);
	
	/**
	 * \brief release a handle to a resouce
	 */
	void releaseText(ResourceText* resource);
	
	/**
	 * \brief stop the resource manager thread
	 */
	void stop();
	
private:

	void loop();
	
};

#endif
