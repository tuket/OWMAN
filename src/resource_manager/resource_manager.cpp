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

	unsigned int count = resourceTable.getCount( name );

	// not loaded
	if( count == 0 )
	{
		ResourceText* resource = resourceTextFactory.createResource(name);
		resourceTable.addEntry(name, resource);
		workQueue.push( ResourceRequest( ResourceRequest::Type::OBTAIN, name ) );
		return resource;
	}

	// loaded
	else
	{
		resourceTable.incEntry(name);
		return (ResourceText*)resourceTable.getResource(name);
	}

}

void ResourceManager::releaseText(ResourceText* resource)
{

	string name = resource->getName();
	unsigned int count = resourceTable.getCount(name);

	// last reference
	if( count == 1 )
	{

		resourceTextFactory.destroyResource(resource);
		resourceTable.removeEntry(name);

	}

	// more references
	else
	{
		resourceTable.decEntry(name);
	}

}

ResourceTexture* ResourceManager::obtainTexture(std::string name)
{

	unsigned int count = resourceTable.getCount( name );

	// not loaded
	if( count == 0 )
	{
		ResourceTexture* resource = resourceTextureFactory.createResource(name);
		resourceTable.addEntry(name, resource);
		workQueue.push( ResourceRequest( ResourceRequest::Type::OBTAIN, name ) );
		return resource;
	}

	// loaded
	else
	{
		resourceTable.incEntry(name);
		return (ResourceTexture*)resourceTable.getResource(name);
	}

}

void ResourceManager::releaseTexture(ResourceTexture* resource)
{

	string name = resource->getName();
	unsigned int count = resourceTable.getCount(name);

	// last reference
	if( count == 1 )
	{

		resourceTextureFactory.destroyResource(resource);
		resourceTable.removeEntry(name);

	}

	// more references
	else
	{
		resourceTable.decEntry(name);
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
			Resource* resource = resourceTable.getResource(name);
			resource->load();

		}

		// release
		else if( request.getType() == ResourceRequest::Type::RELEASE )
		{

			string name = request.getName();
			Resource* resource = resourceTable.getResource(name);
			resource->free();

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
