#include "i_world_streamer.hpp"

EntityFactory* IWorldStreamer::getEntityFactory()const
{
	return entityFactory;
}

void IWorldStreamer::setEntityFactory(EntityFactory* entityFactory)
{
	this->entityFactory = entityFactory;
}
