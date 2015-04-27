#include "i_world_streamer.hpp"

#ifndef TEST_WORLD_STREAMER
#define TEST_WORLD_STREAMER

/**
 * This world streamer is just for testing purposes.
 * It return a fixed vector of entites.
 **/

class TestWorldStreamer : public IWorldStreamer
{
	
protected:

	EntityFactory* entityFactory;
	vector<Entity*> entities;
	
public:

	TestWorldStreamer(){}
	
	TestWorldStreamer(EntityFactory* entityFactory);
	
	void init(Vec2i cell, Vec2f offset);
	
	void update(Vec2i cell, Vec2f offset);
	
	std::vector<Entity*> getActiveEntities()const;
	
};

#endif
