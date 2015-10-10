#include "graphics_system.hpp"
#include "color.hpp"
#include "../resource_manager/resource_manager.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

GraphicsSystem::PendingTask::PendingTask(const PendingTaskType& type, void* pointer)
{
	this->pendingTaskType = type;
	this->pointer = pointer;
}

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
textureManager(this),
spriteManager(this)
{

	camera.myGraphicsSystem = this;

}

void GraphicsSystem::setFullScreen(bool b)
{
    renderer.setFullScreen(b);
}

void GraphicsSystem::update(unsigned int delta)
{

	// process pending tasks
	for(unsigned int i=0; i<pendingTasks.size(); i++)
	{

		if( pendingTasks[i].pendingTaskType == PendingTaskType::DESTROY_SPRITE )
		{

			Sprite* sprite = (Sprite*)(pendingTasks[i].pointer);

			// the sprite has been laoded
			// we can now remove it and unmark the pending task
			if( sprite->isReady() )
			{

				destroySprite(sprite);

				// this technique allow to delete one element in constant
				// time if you do not care about the order of the elements
				pendingTasks[i] = pendingTasks[pendingTasks.size()-1];
				pendingTasks.pop_back();

				i--;

			}

		}


		// I think that it could be a good idea to process only one of
		// these pending tasks per frame so it is less likely to have
		// fps drops
		break;

	}

	set<GraphicsComponent*>::iterator it;
	for( it=components.begin(); it != components.end(); ++it )
	{

		(*it)->update(delta);

	}

}

void GraphicsSystem::draw()
{

    vector<GraphicsComponent*> vec(components.begin(), components.end());

    // sort by priority

    sort
    (
        vec.begin(),
        vec.end(),
        [](GraphicsComponent* gc1, GraphicsComponent* gc2) -> bool
        {
            return gc1->getPriority() < gc2->getPriority();
        }
    );

	renderer.clear();
	vector<GraphicsComponent*>::iterator it;
	for( it=vec.begin(); it != vec.end(); ++it )
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
	// what if this function is called before the texture
	// is loaded?

	// the texture of the sprite has already been loaded
	// to RAM and to video memory
	if(sprite->isReady())
	{
		components.erase(sprite);
		spriteFactory.destroySprite(sprite);
	}

	// the texture is not loaded to the video memory yet
	// we must wait for it to be loaded in order to unload it
	else
	{
		PendingTask destroyLaterTask(PendingTaskType::DESTROY_SPRITE, sprite);
		pendingTasks.push_back(destroyLaterTask);
	}

}

void GraphicsSystem::destroyGraphicsComponent(GraphicsComponent* graphicsComponent)
{

    graphicsComponent->destroyDispatcher();

}

LowLevelRenderer2D* GraphicsSystem::getRenderer()
{
	return &renderer;
}

Camera* GraphicsSystem::getCamera()
{
	return &camera;
}

void GraphicsSystem::end()
{

    renderer.end();

}
