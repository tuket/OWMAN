#include "event_handler.hpp"
#include "../engine.hpp"
#include "../physics/physics_component.hpp"
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
    float vx = 0;
    float vy = 0;


	switch (event.type) {
		/* close button clicked */
		case SDL_QUIT:
			engine->endGame();
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
					engine->endGame();
                break;

                case SDLK_UP:
                    vy += 2000;
                break;
                case SDLK_DOWN:
                    vy -= 2000;
                break;
                case SDLK_LEFT:
                    vx -= 2000;
                break;
                case SDLK_RIGHT:
                    vx += 2000;
                break;

                default:
                    vx = 0;
                    vy = 0;

			}
        break;

	}

    mc->getPhysicsComponent()->setSpeed( Vec2f(vx, vy) );

}

void EventHandler::poll()
{
	SDL_PollEvent(&event);
	handle();
	event.type = 0;
}
