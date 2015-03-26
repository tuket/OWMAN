#include "../low_level_renderer_2d.hpp"
#include <SDL2/SDL.h>

int main()
{
	
	SDL_Init(SDL_INIT_TIMER);
	LowLevelRenderer2D rend( "Test renderer v1", 600, 600, false );
	LowLevelRenderer2D::Texture text1("b.png");
	
	while(true)
	{	
		unsigned int beginTicks = SDL_GetTicks();
		
		// Drawing!
		rend.clear();
		rend.draw(Vec2f(0, 0), Vec2f(1, 1), &text1);
		rend.swap();
				
		unsigned int endTicks = SDL_GetTicks();
		int sleepTicks = 1000/60 - (endTicks-beginTicks);
		if(sleepTicks > 0)
			SDL_Delay( sleepTicks );
		
	}
	
}
