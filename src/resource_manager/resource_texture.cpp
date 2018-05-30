#include "resource_texture.hpp"
#include "resource_texture_factory.hpp"
#include <iostream>
#include <stb_image.h>

using namespace std;

ResourceTexture::ResourceTexture(const string& name)
:
    Resource(name)
{
}

const unsigned char* ResourceTexture::getTextureData()const
{
    return imageData;
}

int ResourceTexture::getWidth()const
{
    return width;
}

int ResourceTexture::getHeight()const
{
    return height;
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
    status = Status::LOADING;

	imageData =
	stbi_load
	(
		name.c_str(),	// file name
		&width,				// pointer where width will be saved
		&height,				// pointer where height will be saved
		0,					// pointer where num of chanel will be saved
		0		// desired chanels
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

	stbi_image_free(imageData);

}

/*
void ResourceTexture::destroyDispatcher()
{
    myFactory->destroyResource(this);
}
*/
