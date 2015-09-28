#ifndef RESOURCE_MANAGER_TEMPLATES
#define RESOURCE_MANAGER_TEMPLATES

template <typename T>
T* ResourceManager::obtain(std::string name)
{
    pthread_mutex_lock(&mutexTable);
        unsigned int count = resourceTable.getCount( name );
	pthread_mutex_unlock(&mutexTable);

	// not loaded
	if( count == 0 )
	{
		T* resource = new T(name);

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
            T* res = (T*)resourceTable.getResource(name);
        pthread_mutex_unlock(&mutexTable);

		return res;
	}
}


#endif // RESOURCE_MANAGER_TEMPLATES
