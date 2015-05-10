#include "resource_factory.hpp"
#include "resource_cell.hpp"


#ifndef RESOURCE_CELL_FACTORY
#define RESOURCE_CELL_FACTORY

class ResourceCellFactory : public ResourceFactory
{

	void destroyResource(Resource* resource);

public:

	ResourceCell* createResource(std::string name);
	void destroyResource(ResourceCell* resource);


};

#endif
