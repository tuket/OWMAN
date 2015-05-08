#include "sprite.hpp"
#include "graphics_system.hpp"
#include "../resource_manager/resource_manager.hpp"
#include "../resource_manager/resource_texture.hpp"
#include <iostream>

using namespace std;

bool Sprite::isReady()const
{
	return resourceTexture->getStatus() == Resource::Status::READY;
}

bool Sprite::isLoaded()const
{
	return resourceTexture->getStatus() == Resource::Status::LOADED;
}

void Sprite::becomeReady()const
{
	resourceTexture->loadToGraphicsCard();
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
