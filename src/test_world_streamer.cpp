#include "test_world_streamer.hpp"
#include <string>

using namespace std;

TestWorldStreamer::TestWorldStreamer(EntityFactory* entityFactory)
{
	
	this->entityFactory = entityFactory;
	
}

void TestWorldStreamer::init(Vec2i cell, Vec2f offset)
{
	
	string entityText =
	"<id> 2 </id>"

	"<position>"
	"	<x>0</x>"
	"	<y>0</y>"
	"</position>"

	"<graphics>"
	"	<texture>elf.png</texture>"
	"	<width>10</width>"
	"	<height>15</height>"
	"</graphics>"

	"<physics>"
	"	<shape>box</shape>"
	"	<width>10</width>"
	"	<height>15</height>"
	"	<mass>60</mass>"
	"</physics>"
	;
	
}

void TestWorldStreamer::update(Vec2i cell, Vec2f offset)
{
	
}

vector<Entity*> TestWorldStreamer::getActiveEntities()const
{
	return entities;
}
