#include "resource_manager.hpp"
#include <iostream>

using namespace std;

ResourceManager ResourceManager::uniqueInstance;

void ResourceManager::init()
{



}

ResourceManager* ResourceManager::getSingleton()
{
	return &uniqueInstance;
}

void ResourceManager::launch()
{

	int idThread;
	_stop = false;
	idThread = pthread_create( &myThread, 0, &ResourceManager::staticLoop, (void*)this);
    pthread_mutex_init(&mutexTable, 0);

	// check error
	if( idThread )
	{
		cerr << "Error creating thread for ResouceManager: "
		<< idThread << endl;
		exit(1);
	}

}

ResourceText* ResourceManager::obtainText(std::string name)
{

    pthread_mutex_lock(&mutexTable);
        unsigned int count = resourceTable.getCount( name );
	pthread_mutex_unlock(&mutexTable);

	// not loaded
	if( count == 0 )
	{
		ResourceText* resource = resourceTextFactory.createResource(name);

		pthread_mutex_lock(&mutexTable);
            resourceTable.addEntry(name, resource);
		pthread_mutex_unlock(&mutexTable);

		workQueue.push( ResourceRequest( ResourceRequest::Type::OBTAIN, name ) );
		return resource;
	}

	// loaded
	else
	{

	    pthread_mutex_lock(&mutexTable);
            resourceTable.incEntry(name);
		pthread_mutex_unlock(&mutexTable);

        pthread_mutex_lock(&mutexTable);
            ResourceText* res = (ResourceText*)resourceTable.getResource(name);
        pthread_mutex_unlock(&mutexTable);

		return res;
	}

}

void ResourceManager::releaseText(ResourceText* resource)
{

	string name = resource->getName();

	pthread_mutex_lock(&mutexTable);
        unsigned int count = resourceTable.getCount(name);
	pthread_mutex_unlock(&mutexTable);

	// last reference
	if( count == 1 )
	{

		resourceTextFactory.destroyResource(resource);

		pthread_mutex_lock(&mutexTable);
            resourceTable.removeEntry(name);
		pthread_mutex_unlock(&mutexTable);

	}

	// more references
	else
	{
	    pthread_mutex_lock(&mutexTable);
            resourceTable.decEntry(name);
		pthread_mutex_unlock(&mutexTable);
	}

}

ResourceTexture* ResourceManager::obtainTexture(std::string name)
{

    pthread_mutex_lock(&mutexTable);
        unsigned int count = resourceTable.getCount( name );
	pthread_mutex_unlock(&mutexTable);

	// not loaded
	if( count == 0 )
	{
		ResourceTexture* resource = resourceTextureFactory.createResource(name);

		pthread_mutex_lock(&mutexTable);
            resourceTable.addEntry(name, resource);
		pthread_mutex_unlock(&mutexTable);

		workQueue.push( ResourceRequest( ResourceRequest::Type::OBTAIN, name ) );
		return resource;
	}

	// loaded
	else
	{
	    pthread_mutex_lock(&mutexTable);
            resourceTable.incEntry(name);
		pthread_mutex_unlock(&mutexTable);

        pthread_mutex_lock(&mutexTable);
            ResourceTexture* res = (ResourceTexture*)resourceTable.getResource(name);
        pthread_mutex_unlock(&mutexTable);

		return res;
	}

}

void ResourceManager::releaseTexture(ResourceTexture* resource)
{

	string name = resource->getName();

	pthread_mutex_lock(&mutexTable);
        unsigned int count = resourceTable.getCount(name);
	pthread_mutex_unlock(&mutexTable);

	// last reference
	if( count == 1 )
	{

        // release of textures requires
        // (due to some limitations of OpenGL) to be deleted by
        // the main thread
		resource->free();
        resourceTextureFactory.destroyResource(resource);

        pthread_mutex_lock(&mutexTable);
            resourceTable.removeEntry(name);
        pthread_mutex_unlock(&mutexTable);

	}

	// more references
	else
	{
	    pthread_mutex_lock(&mutexTable);
            resourceTable.decEntry(name);
		pthread_mutex_unlock(&mutexTable);
	}

}

// the implementation of this resource is a bit more tricky
// because the changes on cells are permanent.
ResourceCell* ResourceManager::obtainCell(std::string name)
{
    pthread_mutex_lock(&mutexTable);
        unsigned int count = resourceTable.getCount( name );
	pthread_mutex_unlock(&mutexTable);

	// not loaded
	if( count == 0 )
	{
		ResourceCell* resource = resourceCellFactory.createResource(name);

		pthread_mutex_lock(&mutexTable);
            resourceTable.addEntry(name, resource);
		pthread_mutex_unlock(&mutexTable);

		workQueue.push( ResourceRequest( ResourceRequest::Type::OBTAIN, name ) );
		return resource;
	}

	// loaded
	else
	{
	    pthread_mutex_lock(&mutexTable);
            resourceTable.incEntry(name);
		pthread_mutex_unlock(&mutexTable);

        pthread_mutex_lock(&mutexTable);
            ResourceCell* res = (ResourceCell*)resourceTable.getResource(name);
        pthread_mutex_unlock(&mutexTable);

		return res;
	}
}

void ResourceManager::releaseCell(ResourceCell* resource)
{

    string name = resource->getName();

	pthread_mutex_lock(&mutexTable);
        unsigned int count = resourceTable.getCount(name);
	pthread_mutex_unlock(&mutexTable);

	// last reference
	if( count == 1 )
	{

		resource->free();
        resourceCellFactory.destroyResource(resource);

        pthread_mutex_lock(&mutexTable);
            resourceTable.removeEntry(name);
        pthread_mutex_unlock(&mutexTable);

	}

	// more references
	else
	{
	    pthread_mutex_lock(&mutexTable);
            resourceTable.decEntry(name);
		pthread_mutex_unlock(&mutexTable);
	}

}

void ResourceManager::setRenderer(LowLevelRenderer2D* renderer)
{
	resourceTextureFactory.setRenderer(renderer);
}

void ResourceManager::loop()
{

	// this might seem polling but it is not.
	// The pop function of WorkQueue will stall
	// if the are not elements in the queue
	while( !_stop )
	{

		ResourceRequest request;
		request = workQueue.pop();

		// obtain
		if( request.getType() == ResourceRequest::Type::OBTAIN )
		{

			string name = request.getName();

			pthread_mutex_lock(&mutexTable);
                Resource* resource = resourceTable.getResource(name);
			pthread_mutex_unlock(&mutexTable);

			resource->load();

		}

		// release
		else if( request.getType() == ResourceRequest::Type::RELEASE )
		{

			// save

		}

		// stop
		else if( request.getType() == ResourceRequest::Type::STOP )
		{
			_stop = true;
		}

	}

}

void* ResourceManager::staticLoop(void* object)
{

	((ResourceManager*)object)->loop();
	return 0;

}
