#include <SDL2/SDL.h>

#ifndef EVENT_HANDLER
#define EVENT_HANDLER

class EventHandler
{
	
	SDL_Event event;
	
public:
	
	EventHandler();
	
	virtual void handle();
	void poll();
	
};

#endif
