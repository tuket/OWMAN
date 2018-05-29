#ifndef RESOURCE_MANAGER
#define RESOURCE_MANAGER

#include "resource_table.hpp"
#include "work_queue.hpp"
#include "resource_request.hpp"
#include <pthread.h>
#include <string>

class LowLevelRenderer2D;

/** \brief This is the singleton you should use
 * Requesting resources will deliver a resource pointer
 * event if the resource data is not loaded.
 * You can check if a resource has been loaded checking
 * the status attribute.
 */
class ResourceManager
{

	static ResourceManager uniqueInstance;

	pthread_t myThread;
    pthread_mutex_t mutexTable;     //< mutex for accessing the table

	ResourceTable resourceTable;
	WorkQueue<ResourceRequest> workQueue;
	bool _stop;

public:

	static ResourceManager* getSingleton();

	ResourceManager(){}

    /**
    * \brief launches the resource manger in its own thread
    */
    void launch();

    /**
	 * \brief request a pointer to a resource
	 */
    template <typename T>
	T* obtain(std::string name);

    /**
	 * \brief release a pointer to a resource
	 */
	void release(Resource* resource);

	/**
	 * \brief stop the resource manager thread
	 */
	void stop();

	bool hasStopped();

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

#include "resource_manager_templates.hpp"

#endif
