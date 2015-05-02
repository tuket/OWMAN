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
	const float cellSize = 100;
	
	WorldWindow worldWindow;
	std::string worldFolder;
	
	EntityFactory* entityFactory;
	
public:
	
	WorldStreamer(){}
	WorldStreamer
	(
		std::string worldFolder,
		EntityFactory* entityFactory,
		float cellSize = 100.f
	);
	
	/**
	 * \brief Inits the world streamer.
	 * \param cell the cell where the main character is located.
	 * \param offset of the character wrt the cell bot left corner.
	 * Both params could be ingnored by the implementation.
	 **/
	void init(Vec2i cell, Vec2f offset);
	
	/**
	 * \brief Updates the world streamer.
	 * \param cell the cell where the main character is located.
	 * \param offset of the character wrt the cell bot left corner.
	 * Both params could be ingnored by the implementation.
	 **/
	void update(Vec2i cell, Vec2f offset);
	
	Vec2i getWindowPosition()const;
	
};

#endif
