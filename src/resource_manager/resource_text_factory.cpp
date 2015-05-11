#include "resource_text_factory.hpp"
#include <fstream>

using namespace std;

ResourceText* ResourceTextFactory::createResource(string name)
{

	ResourceText *res = new ResourceText;
	res->name = name;
	res->myFactory = this;

	return res;

}

void ResourceTextFactory::destroyResource(ResourceText* resource)
{

	delete resource;

}

void ResourceTextFactory::destroyResource(Resource* resource)
{

	delete resource;

}
