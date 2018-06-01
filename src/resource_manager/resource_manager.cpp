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
    _stop = false;
    try
    {
        myThread = std::thread(ResourceManager::staticLoop, this);
    }
    catch (std::exception e)
	{
		cerr << "Error creating thread for ResouceManager: "
		<< e.what() << endl;
		exit(1);
	}
}

void ResourceManager::release(Resource* resource)
{

    string name = resource->getName();

	mutexTable.lock();
        unsigned int count = resourceTable.getCount(name);
	mutexTable.unlock();

	// last reference
	if( count == 1 )
	{

        mutexTable.lock();
            resourceTable.decEntry(name);
        mutexTable.unlock();

        workQueue.push( ResourceRequest( ResourceRequest::Type::RELEASE, name ) );

	}

	// more references
	else
	{
	    mutexTable.lock();
            resourceTable.decEntry(name);
		mutexTable.unlock();
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

			mutexTable.lock();
                Resource* resource = resourceTable.getResource(name);
			mutexTable.unlock();

			resource->load();

		}

		// release
		else if( request.getType() == ResourceRequest::Type::RELEASE )
		{

            string name = request.getName();

            mutexTable.lock();
                Resource* resource = resourceTable.getResource(name);
			mutexTable.unlock();

			resource->free();

            mutexTable.lock();
                resourceTable.removeEntry(name);
			mutexTable.unlock();

		}

		// stop
		else if( request.getType() == ResourceRequest::Type::STOP )
		{
			_stop = true;
		}

        std::this_thread::sleep_for(1ms);
	}

}

void* ResourceManager::staticLoop(void* object)
{

	((ResourceManager*)object)->loop();
	return 0;

}
