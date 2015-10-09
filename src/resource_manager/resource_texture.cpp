#include "resource_texture.hpp"
#include "resource_texture_factory.hpp"
#include <iostream>
#include <SOIL/SOIL.h>

using namespace std;

ResourceTexture::ResourceTexture(const string& name)
{
	status = Resource::Status::STORED;
	this->name = name;
}

/*
void ResourceTexture::loadToGraphicsCard()
{

	LowLevelRenderer2D* renderer;
	renderer = myFactory->getRenderer();

	texture = renderer->createTexture(imageData, width, height);
	status = Resource::Status::READY;

	SOIL_free_image_data(imageData);

}
*/

// this function is called by the resource manager thread
void ResourceTexture::load()
{

	LowLevelRenderer2D* renderer;
	renderer = myFactory->getRenderer();

	imageData =
	SOIL_load_image
	(
		name.c_str(),	// file name
		&width,				// pointer where width will be saved
		&height,				// pointer where height will be saved
		0,					// pointer where num of chanel will be saved
		SOIL_LOAD_RGBA		// RGB
	);

	texture.setWidth(width);
	texture.setHeight(height);

	if(imageData == 0)
	{
		cerr << "Error loading: " << name << endl;
		return;
	}

	status = Resource::Status::LOADED;

}

void ResourceTexture::free()
{

	SOIL_free_image_data(imageData);

}

void ResourceTexture::destroyDispatcher()
{
    myFactory->destroyResource(this);
}
