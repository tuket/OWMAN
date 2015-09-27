#include "resource_table.hpp"
#include "work_queue.hpp"
#include "resource_request.hpp"
#include "resource_text_factory.hpp"
#include "resource_texture_factory.hpp"
#include "resource_cell_factory.hpp"
#include <pthread.h>
#include <string>

#ifndef LOW_LEVEL_RENDERER_2D
class LowLevelRenderer2D;
#endif


#ifndef RESOURCE_MANAGER
#define RESOURCE_MANAGER

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

	static void init();

	static ResourceManager* getSingleton();

	ResourceManager(){}

    /**
	 * \brief request a pointer to a resource
	 */
    template <typename R>
	R* obtain<R>(std::string name);

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

#endif
