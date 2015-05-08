#include <vector>
#include <map>
#include "position.hpp"
#include "world_cell.hpp"

#ifndef ENTITY
class Entity;
#endif

#ifndef WORLD_WINDOW
#define WORLD_WINDOW

class WorldWindow
{

	friend class WorldStreamer;

	std::map<Vec2i, WorldCell> cells;

	unsigned int windowSize;

public:

	WorldWindow();

	WorldWindow(unsigned int windowSize);

    std::vector<Entity*> getEntities()const;

	~WorldWindow();

};

#endif
