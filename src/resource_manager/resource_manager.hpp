#include "resource_table.hpp"
#include "work_queue.hpp"
#include "resource_request.hpp"
#include "resource_text_factory.hpp"
#include "resource_texture_factory.hpp"
#include <pthread.h>
#include <string>

#ifndef LOW_LEVEL_RENDERER_2D
class LowLevelRenderer2D;
#endif


#ifndef RESOURCE_MANAGER
#define RESOURCE_MANAGER

class ResourceManager
{

	static ResourceManager uniqueInstance;

	pthread_t myThread;
	ResourceTable resourceTable;
	ResourceTextFactory resourceTextFactory;
	ResourceTextureFactory resourceTextureFactory;
	WorkQueue<ResourceRequest> workQueue;
	bool _stop;

public:

	static void init();

	static ResourceManager* getSingleton();

	ResourceManager(){}

	/**
	 * \brief launches the resurce manger in its own thread
	 */
	void launch();

	/**
	 * \brief request a pointer to a text resource
	 */
	ResourceText* obtainText(std::string name);

	/**
	 * \brief release a pointer to a text resource
	 */
	void releaseText(ResourceText* resource);

	/**
	 * \brief request a pointer to a texture resource
	 */
	ResourceTexture* obtainTexture(std::string name);

	/**
	 * \brief release a pointer to a texture resource
	 */
	void releaseTexture(ResourceTexture* resource);

	/**
	 * \brief stop the resource manager thread
	 */
	void stop();

	void setRenderer(LowLevelRenderer2D* renderer);

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
