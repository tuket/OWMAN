#include "resource_factory.hpp"
#include "resource_text.hpp"

#ifndef RESOURCE_TEXT_FACTORY
#define RESOURCE_TEXT_FACTORY

class ResourceTextFactory : public ResourceFactory
{
	
	void destroyResource(Resource* resource);
	
public:
	
	ResourceText* createResource(std::string name);
	void destroyResource(ResourceText* resource);
	
};

#endif
