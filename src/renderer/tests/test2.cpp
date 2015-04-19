#include "../graphics_system.hpp"
#include "../../IO/event_handler.hpp"
#include "../../resource_manager/resource_manager.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <pthread.h>
using namespace std;

int main()
{
	
	SDL_Init(SDL_INIT_TIMER);
	
	const unsigned int timeToLaunchResMan = 5000;
	ResourceManager::init();
	ResourceManager* resMan = ResourceManager::getSingleton();
	resMan->launch();
	
	
	GraphicsSystem graphicsSystem
	(
		"test2",
		600, 600,
		false
	);
	
	Sprite* sprite = graphicsSystem.createSprite("img/b.png", Vec2f(200, 100));
	//graphicsSystem.destroySprite(sprite);
	
	sprite->setPosition(Vec2f(50, 50));
	
	Camera* camera = graphicsSystem.getCamera();
	camera->setPosition(Vec2f(0,0));
	camera->setWidth(200);
	camera->setHeight(200);
	
	EventHandler eventHandler;
		
	
	unsigned int timeBeg = SDL_GetTicks();
	
	while(true)
	{
		
		unsigned int beginTicks = SDL_GetTicks();
				
		eventHandler.poll();
		
		graphicsSystem.update(1000.0/60);
		graphicsSystem.draw();
		graphicsSystem.swap();
		
		unsigned int endTicks = SDL_GetTicks();
		int sleepTicks = 1000/60 - (endTicks-beginTicks);
		if(sleepTicks > 0)
			SDL_Delay( sleepTicks );
		
	}
	
	
}
