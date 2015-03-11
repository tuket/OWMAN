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
	ResourceTextFactory resourceTextFactory;
	WorkQueue<ResourceRequest> workQueue;
	bool _stop;
	
public:

	ResourceManager(){}
	
	/**
	 * \brief launches the resurce manger in its own thread
	 */
	void launch();
	
	/**
	 * \brief request a handle to a text resouce
	 */
	ResourceText* obtainText(std::string name);
	
	/**
	 * \brief release a handle to a text resouce
	 */
	void releaseText(ResourceText* resource);
	
	/**
	 * \brief stop the resource manager thread
	 */
	void stop();
	
private:
	
	/**
	 * \brief consumes requests
	 * Iterates for ever to handle requests.
	 */
	void loop();
	
	/**
	 * \brief this function calls loop
	 * You can not create a pthread from a member funtion
	 * so I use this static function as a helper
	 */
	static void* staticLoop(void* object);
	
};

#endif
