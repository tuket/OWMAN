#include "../low_level_renderer_2d.hpp"
#include "../../IO/event_handler.hpp"
#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

int main()
{
	
	SDL_Init(SDL_INIT_TIMER);
	LowLevelRenderer2D::init( "Test renderer v1", 600, 600, false );
	LowLevelRenderer2D* rend = LowLevelRenderer2D::getSingleton();
	LowLevelRenderer2D::Texture text1 = rend->createTexture("img/b.png");
	LowLevelRenderer2D::Texture text2 = rend->createTexture("img/happy_guy.png");
	
	Color squareColor(0.8, 0, 0, 0.3);
	
	LowLevelRenderer2D::Camera& camera = rend->getCamera();
	
	float size = 100;
	camera.setWidth(100);
	camera.setHeight(100);
	
	EventHandler eventHandler;
	
	while(true)
	{	
		
		unsigned int beginTicks = SDL_GetTicks();
		
		eventHandler.poll();
		
		size += 0.5;
		camera.setWidth(size);
		camera.setHeight(size);
		
		// Drawing!
		rend->clear();
		rend->draw(Vec2f(0, 0), Vec2f(50, 50), &text1);
		rend->draw(Vec2f(50, 50), Vec2f(50,50), &text2);
		rend->drawColorSquare(Vec2f(50, 0), Vec2f(50, 50), squareColor);
		rend->swap();
				
		unsigned int endTicks = SDL_GetTicks();
		int sleepTicks = 1000/60 - (endTicks-beginTicks);
		if(sleepTicks > 0)
			SDL_Delay( sleepTicks );
		
	}
	
}
