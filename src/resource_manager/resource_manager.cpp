#include "resource_manager.hpp"
#include <iostream>

using namespace std;

void ResourceManager::launch()
{
	
	int idThread;
	stop = false;
	idThread = pthread_create( &myThread, 0, loop, 0);
	
	// check error
	if( idThread )
	{
		cerr << "Error creating thread for ResouceManager: "
		<< idThread << endl;
		exit(1);
	}
	
}

void ResourceManager::loop()
{
	
	// this might seem polling but it is not.
	// The pop function of WorkQueue will stall
	// if the are not elements in the queue
	while( !stop )
	{
		
		ResourceRequest request;
		request = workQueue.pop();
		
		// obtain
		if( request.getType() == ResourceRequest::Type::OBTAIN )
		{
			Resource* resource = resourceTable.getResourceText(name);
			resource->status = Resource::Status::LOADED;
		}
		
		// release
		else if( request.getType() == ResourceRequest::Type::OBTAIN )
		{
			
		}
		
		// stop
		else
		{
			stop = true;
		}
		
	}
	
}
