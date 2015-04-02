#include "resource_texture_factory.hpp"
#include <iostream>

using namespace std;

ResourceTexture* ResourceTextureFactory::createResource(std::string name)
{
	
	ResourceTexture* res = new ResourceTexture;
	res->name = name;
	res->myFactory = this;
	
	return res;
	
}

void ResourceTextureFactory::destroyResource(ResourceTexture* resource)
{
	
	delete resource;
	
}

void ResourceTextureFactory::destroyResource(Resource* resource)
{
	
	delete resource;
	
}

void ResourceTextureFactory::setRenderer(LowLevelRenderer2D* renderer)
{
	this->renderer = renderer;
}

LowLevelRenderer2D* ResourceTextureFactory::getRenderer()
{
	return renderer;
}
