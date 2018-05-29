#include "resource_manager.hpp"
#include <iostream>

using namespace std;

ResourceManager ResourceManager::uniqueInstance;

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

void ResourceManager::release(Resource* resource)
{

    string name = resource->getName();

	pthread_mutex_lock(&mutexTable);
        unsigned int count = resourceTable.getCount(name);
	pthread_mutex_unlock(&mutexTable);

	// last reference
	if( count == 1 )
	{

        pthread_mutex_lock(&mutexTable);
            resourceTable.decEntry(name);
        pthread_mutex_unlock(&mutexTable);

        workQueue.push( ResourceRequest( ResourceRequest::Type::RELEASE, name ) );

	}

	// more references
	else
	{
	    pthread_mutex_lock(&mutexTable);
            resourceTable.decEntry(name);
		pthread_mutex_unlock(&mutexTable);
	}

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

            string name = request.getName();

            pthread_mutex_lock(&mutexTable);
                Resource* resource = resourceTable.getResource(name);
			pthread_mutex_unlock(&mutexTable);

			resource->free();

            pthread_mutex_lock(&mutexTable);
                resourceTable.removeEntry(name);
			pthread_mutex_unlock(&mutexTable);

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
