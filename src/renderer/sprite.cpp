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
	return ready;
}

void Sprite::update()
{
    if( !ready )
    {
        if( resourceText->getStatus() == Resource::Status::LOADED )
        {
            string text = resourceText->getText();

        }
    }
}

void Sprite::draw()const
{

	LowLevelRenderer2D* renderer = myFactory->getGraphicsSystem()->getRenderer();
	renderer->draw(position, scale, resourceTexture->getTexture());

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
