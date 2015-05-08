#include "event_handler.hpp"
#include "../engine.hpp"
//#include "../renderer/graphics_system.hpp"
#include <cmath>
#include <iostream>

using namespace std;

EventHandler::EventHandler( Engine* engine )
{
    this->engine = engine;
	SDL_Init(SDL_INIT_EVENTS);
}

void EventHandler::handle()
{

    Entity* mc = engine->getMainCharacter();
    float x = mc->getPosition().x;
    float y = mc->getPosition().y;


	switch (event.type) {
		/* close button clicked */
		case SDL_QUIT:
			exit(0);
        break;

		case SDL_MOUSEWHEEL:
        {
            GraphicsSystem* gs = engine->getGraphicsSystem();
            float w = gs->getCamera()->getWidth();
            float h = gs->getCamera()->getHeight();

            float p = pow(1.02f, event.wheel.y);
            w *= p;
            h *= p;

            gs->getCamera()->setWidth(w);
            gs->getCamera()->setHeight(h);
        }
        break;

		/* handle the keyboard */

		case SDL_KEYDOWN:

			switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
				//case SDLK_q:
					exit(0);
                break;

                case SDLK_UP:
                    y += 5;
                break;
                case SDLK_DOWN:
                    y -= 5;
                break;
                case SDLK_LEFT:
                    x -= 5;
                break;
                case SDLK_RIGHT:
                    x += 5;
                break;

			}
        break;

	}

    mc->setPosition( Vec2f(x, y) );

}

void EventHandler::poll()
{
	SDL_PollEvent(&event);
	handle();
	event.type = 0;
}
