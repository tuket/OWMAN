#include "sprite.hpp"
#include "graphics_system.hpp"
#include "../resource_manager/resource_manager.hpp"
#include "../resource_manager/resource_texture.hpp"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
using namespace rapidxml;

bool Sprite::isReady()const
{
	return Status::EVERYTHING_LOADED == status;
}

void Sprite::update()
{
    if(Status::LOADING_XML == status)
    {
        if(Resource::Status::LOADED == resouceText->getStatus())
        {

        }
    }
    else if(Status::LOADING_TEXTURES)
    {
        bool allLoaded = true;
        for(unsigned i=0; i<resourceTextures.size(); i++)
        {
            if(Resource::Status::LOADED)
            {
                allLoaded = false;
                break;
            }
        }

        if(allLoaded)
        {

        }
    }
}

void Sprite::draw()const
{

}

Sprite::~Sprite()
{

	ResourceManager* resourceManager = ResourceManager::getSingleton();
	resourceManager->releaseTexture( resourceTexture );

}

void Sprite::destroyDispatcher()
{

    myGraphicsSystem->destroySprite( this );

}
