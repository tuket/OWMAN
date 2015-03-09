#include "resource.hpp"

#ifndef RESOURCE_FACTORY
#define RESOURCE_FACTORY

class ResourceFactory
{
	

public:

	virtual Resource* createResource(std::string name) = 0;
	virtual void destroyResource(Resource* resource) = 0;
	
};

#endif
