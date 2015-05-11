#include "resource_factory.hpp"
#include "resource_cell.hpp"


#ifndef RESOURCE_CELL_FACTORY
#define RESOURCE_CELL_FACTORY

class ResourceCellFactory : public ResourceFactory
{


public:

	ResourceCell* createResource(std::string name);
	void destroyResource(Resource* resource);
	void destroyResource(ResourceCell* resource);


};

#endif
