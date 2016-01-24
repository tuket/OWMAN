#include "event_handler.hpp"
#include "../engine.hpp"
#include "../physics/physics_component.hpp"
#include "../renderer/sprite_status.hpp"
#include <cmath>
#include <iostream>

using namespace std;

EventHandler::EventHandler( Engine* engine )
{
    this->engine = engine;
	SDL_Init(SDL_INIT_EVENTS);
	for(unsigned i=0; i<4; i++) arrowKeysPressed[i] = false;
}

void EventHandler::handle()
{

    Entity* mc = engine->getMainCharacter();
    static const float v = 2000;
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
                    upArrowStatus = true;
                break;
                case SDLK_DOWN:
                    downArrowStatus = true;
                break;
                case SDLK_LEFT:
                    leftArrowStatus = true;
                break;
                case SDLK_RIGHT:
                    rightArrowStatus = true;
                break;
			}
        break;

        case SDL_KEYUP:
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    upArrowStatus = false;
                break;
                case SDLK_DOWN:
                    downArrowStatus = false;
                break;
                case SDLK_LEFT:
                    leftArrowStatus = false;
                break;
                case SDLK_RIGHT:
                    rightArrowStatus = false;
                break;
			}
        break;

	}

    if(!mc->getGraphicsComponent()->isReady()) return;

    SpriteStatus* spr = ((SpriteStatus*)mc->getGraphicsComponent());

    if(upArrowStatus)
    {
        vy += v;
        spr->setAnimation("walking_up");
    }
    if(downArrowStatus)
    {
        vy -= v;
        spr->setAnimation("walking_down");
    }
    if(leftArrowStatus)
    {
        vx -= v;
        spr->setAnimation("walking_left");
    }
    if(rightArrowStatus)
    {
        vx += v;
        spr->setAnimation("walking_right");
    }
    float len = sqrt(vx*vx + vy*vy);
    if(len > 0)
    {
        vx /= len;
        vy /= len;
        vx *= v;
        vy *= v;
    }
    else
    {
        unsigned animIndex = spr->getAnimationIndex();
        animIndex %= 4;
        spr->setAnimation(animIndex);
    }

    mc->getPhysicsComponent()->setSpeed( Vec2f(vx, vy) );

}

void EventHandler::poll()
{
	SDL_PollEvent(&event);
	handle();
	event.type = 0;
}
