#include "event_handler.hpp"

EventHandler::EventHandler()
{
	SDL_Init(SDL_INIT_EVENTS);
}

void EventHandler::handle()
{
	
	switch (event.type) {
		/* close button clicked */
		case SDL_QUIT:
			exit(0);
			break;
			
		/* handle the keyboard */
		/*
		case SDL_KEYDOWN:
		
			switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
				case SDLK_q:
					gameover = true;
					break;
			}
			break;
		*/
	}
	
}

void EventHandler::poll()
{
	SDL_PollEvent(&event);
	handle();
}
