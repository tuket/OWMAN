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

	bool arrowKeysPressed[4];

	bool& upArrowStatus = arrowKeysPressed[0];
	bool& downArrowStatus = arrowKeysPressed[1];
	bool& leftArrowStatus = arrowKeysPressed[2];
	bool& rightArrowStatus = arrowKeysPressed[3];

public:

	EventHandler( Engine* engine );

	virtual void handle();
	void poll();

};

#endif
