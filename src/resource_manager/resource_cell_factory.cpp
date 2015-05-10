#include "resource_cell_factory.hpp"


ResourceCell* ResourceCellFactory::createResource(std::string name)
{

    ResourceCell *res = new ResourceCell;
	res->name = name;

	return res;

}

void ResourceCellFactory::destroyResource(Resource* resource)
{
    delete resource;
}

void ResourceCellFactory::destroyResource(ResourceCell* resource)
{
    delete resource;
}
