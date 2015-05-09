#include "i_world_streamer.hpp"
#include "world_window.hpp"
#include "world_cell.hpp"
#include "entity.hpp"
#include "resource_manager/resource_text.hpp"
#include <string>
#include <map>
#include <set>

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

class WorldStreamer : public IWorldStreamer
{

	// windowPos is the center of the squared window
	// that holds the active entities
	// concides with the cell where the main character is
	// and with origin of coordinates
	Vec2i windowPos;
	const float cellSize = 250;

    // data structure where the WorldCells(vector of entities) are located
	WorldWindow worldWindow;

	// the folder where you can find the cell files and the main character file
	std::string worldFolder;

    // In the initialization of the world streamer we search in the world folder
    // for all the files that are named like cell_X_Y.xml ( where X and Y are positive ints)
    // In the following set are stored all the found cells.
	std::set<Vec2i> availableCells;

    // Cells for which we are still loading the .xml file
	std::map<Vec2i, ResourceText*> loadingCellResources;

	EntityFactory* entityFactory;

public:

	WorldStreamer(){}
	WorldStreamer
	(
		std::string worldFolder,
		EntityFactory* entityFactory,
		float cellSize = 250.f,
		unsigned int windowSize = 2
	);

	/**
	 * \brief Inits the world streamer.
	 * \param cell the cell where the main character is located.
	 * \param offset of the character wrt the cell bot left corner.
	 * Both params could be ingnored by the implementation.
	 **/
	void init(const Vec2i& cell, const Vec2f& offset);

	/**
	 * \brief Updates the world streamer.
	 * \param cell the cell where the main character is located.
	 * \param offset of the character wrt the cell bot left corner.
	 * Both params could be ingnored by the implementation.
	 **/
	void update(const Vec2f& position, MainCharacter* mainCharacter);

	/**
	 * \brief Returns a vector of pointers to all the active entities
	 *
	 **/
	std::vector<Entity*> getEntities()const;

	Vec2i getWindowPosition()const;

	float getCellSize()const;

};

#endif
