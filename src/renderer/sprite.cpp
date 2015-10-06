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
