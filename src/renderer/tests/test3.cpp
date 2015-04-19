#include "../graphics_system.hpp"
#include "../../IO/event_handler.hpp"
#include "../../resource_manager/resource_manager.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <string>
#include <sstream>
using namespace std;

int main()
{
	
	
	srand(214235);
	
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
	
	Camera* camera = graphicsSystem.getCamera();
	camera->setPosition(Vec2f(0,0));
	camera->setWidth(200);
	camera->setHeight(200);
	
	EventHandler eventHandler;
	
	vector<Sprite*> sprites;
	
	int count = 0;
	unsigned int timeBeg = SDL_GetTicks();
	
	while(true)
	{
		
		unsigned int beginTicks = SDL_GetTicks();
		
		eventHandler.poll();
		
		if(count >= 60)
		{
			
			int randn = rand()%4+1;
			stringstream ss;
			ss << "img/" << randn << ".png";
			string fileName = ss.str();
			
			int p = rand()%3;
			if(sprites.size() == 0 || p != 0)
			{
				Sprite* sprite = graphicsSystem.createSprite(fileName, Vec2f(75, 75));
				sprite->setPosition(Vec2f(rand()%200-100, rand()%200-100));
				sprites.push_back(sprite);
			}
			else
			{
				int dd = rand()%sprites.size();
				graphicsSystem.destroySprite(sprites[dd]);
				sprites[dd] = sprites[sprites.size()-1];
				sprites.pop_back();
			}
			
			count = 0;
			
		}
		count++;
		
		graphicsSystem.update(1000.0/60);
		graphicsSystem.draw();
		graphicsSystem.swap();
		
		unsigned int endTicks = SDL_GetTicks();
		int sleepTicks = 1000/60 - (endTicks-beginTicks);
		if(sleepTicks > 0)
			SDL_Delay( sleepTicks );
		
	}
	
	
}
