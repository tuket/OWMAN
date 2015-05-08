#include <SDL2/SDL.h>

#ifndef ENGINE
class Engine;
#endif

#ifndef EVENT_HANDLER
#define EVENT_HANDLER

class EventHandler
{

	SDL_Event event;

	Engine* engine;

public:

	EventHandler( Engine* engine );

	virtual void handle();
	void poll();

};

#endif
