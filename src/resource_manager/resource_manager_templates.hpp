#ifndef RESOURCE_MANAGER_TEMPLATES
#define RESOURCE_MANAGER_TEMPLATES

template <typename T>
T* ResourceManager::obtain(std::string name)
{
    mutexTable.lock();
        unsigned int count = resourceTable.getCount( name );
	mutexTable.unlock();

	// not loaded
	if( count == 0 )
	{
		T* resource = new T(name);

		pthread_mutex_lock(&mutexTable);
            resourceTable.addEntry(name, resource);
		mutexTable.unlock();

		workQueue.push( ResourceRequest( ResourceRequest::Type::OBTAIN, name ) );
		return resource;
	}

	// loaded
	else
	{
	   mutexTable.lock();
            resourceTable.incEntry(name);
		mutexTable.unlock();

       mutexTable.lock();
            T* res = (T*)resourceTable.getResource(name);
        mutexTable.unlock();

		return res;
	}
}


#endif // RESOURCE_MANAGER_TEMPLATES
