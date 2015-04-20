#include <vector>
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
	
	WorldCell*** table;
	
	unsigned int windowSize;

public:
	
	WorldWindow();
	
	WorldWindow(unsigned int windowSize);
	
	
	WorldCell *& operator()(int x, int y);
	
	~WorldWindow();
	
};

#endif
