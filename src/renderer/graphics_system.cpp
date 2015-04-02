#include "graphics_system.hpp"
#include "color.hpp"
#include "../resource_manager/resource_manager.hpp"
#include <iostream>

using namespace std;

GraphicsSystem::GraphicsSystem
(
	string windowTitle,
	unsigned int width, unsigned int height,
	bool fullScreen
)
:renderer
(
	windowTitle,
	width, height,
	fullScreen
),
spriteFactory(this)
{
	
	camera.myGraphicsSystem = this;
	ResourceManager* resMan = ResourceManager::getSingleton();
	resMan->setRenderer(&renderer);
	
}

void GraphicsSystem::update(unsigned int delta)
{
	set<GraphicsComponent*>::iterator it;
	for( it=components.begin(); it != components.end(); ++it )
	{
		
		(*it)->update(delta);
		
	}
	
}

void GraphicsSystem::draw()
{
	
	renderer.clear();
	set<GraphicsComponent*>::iterator it;
	for( it=components.begin(); it != components.end(); ++it )
	{
		
		if( (*it)->isReady() )
		{
			if( (*it)->isVisible() )
			{
				(*it)->draw();
			}
		}
		else
		{
			
			// loaded -> must upload to graphics card
			if((*it)->isLoaded())
			{
				(*it)->becomeReady();
			}
			
			// not loaded -> just wait
			else
			{
				renderer.drawColorSquare((*it)->position, (*it)->scale, Color(1,0.5,0.5));
			}
			
		}
		
	}
	
}

void GraphicsSystem::swap()
{
	
	renderer.swap();
	
}

Sprite* GraphicsSystem::createSprite(std::string fileName, const Vec2f& scale)
{
	Sprite* sprite = spriteFactory.createSprite(fileName, scale);
	sprite->myGraphicsSystem = this;
	components.insert(sprite);
	return sprite;
}

void GraphicsSystem::destroySprite(Sprite* sprite)
{
	components.erase(sprite);
	return spriteFactory.destroySprite(sprite);
}

Engine* GraphicsSystem::getEngine()
{
	return myEngine;
}

LowLevelRenderer2D* GraphicsSystem::getRenderer()
{
	return &renderer;
}

Camera* GraphicsSystem::getCamera()
{
	return &camera;
}
