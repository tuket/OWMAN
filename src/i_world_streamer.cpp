#include "i_world_streamer.hpp"

EntityFactory* IWorldStreamer::getEntityFactory()const
{
	return entityFactory;
}

float IWorldStreamer::getCellSize()const
{
    return 1;
}

void IWorldStreamer::setEntityFactory(EntityFactory* entityFactory)
{
	this->entityFactory = entityFactory;
}
