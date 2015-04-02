#include "resource_texture.hpp"
#include "resource_texture_factory.hpp"
#include <iostream>
#include <SOIL/SOIL.h>

using namespace std;

ResourceTexture::ResourceTexture()
{
	status = Resource::Status::STORED;
}

LowLevelRenderer2D::Texture* ResourceTexture::getTexture()
{
	return &texture;
}

void ResourceTexture::loadToGraphicsCard()
{
	
	LowLevelRenderer2D* renderer;
	renderer = myFactory->getRenderer();
	
	texture = renderer->createTexture(imageData, width, height);
	status = Resource::Status::READY;
	
}

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
	
	if(imageData == 0)
	{
		cerr << "Error loading: " << name << endl;
		return;
	}

	status = Resource::Status::LOADED;
	
}

void ResourceTexture::free()
{
	
	LowLevelRenderer2D* renderer;
	renderer = myFactory->getRenderer();
	renderer->destroyTexture(&texture);
	
}
