#include "world_window.hpp"
#include "world_cell.hpp"
#include "entity.hpp"
#include <string>

#ifndef ENTITY_FACTORY
class EntityFactory;
#endif

#ifndef MAIN_CHARACTER
class MainCharacter;
#endif

#ifndef GRAPHICS_SYSTEM
class GraphicsSystem;
#endif



#ifndef WORLD_STREAMER
#define WORLD_STREAMER

class WorldStreamer
{
	
	// windowPos is the center of the squared window
	// that holds the active entities
	// concides with the cell where the main character is
	// and with origin of coordinates
	Vec2i windowPos;
	
	WorldWindow worldWindow;
	std::string worldFolder;
	
	Entity* mainCharacter;
	
	EntityFactory* entityFactory;
	
public:
	
	WorldStreamer(){}
	WorldStreamer
	(
		std::string worldFolder,
		EntityFactory* entityFactory,
	);
	
	
	void init();
	void update();
	
	Vec2i getWindowPosition()const;
	
};

#endif
