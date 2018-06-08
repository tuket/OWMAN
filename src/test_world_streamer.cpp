#include "test_world_streamer.hpp"
#include "entity.hpp"
#include "entity_factory.hpp"
#include <rapidxml.hpp>
#include <string>

using namespace std;
using namespace rapidxml;

TestWorldStreamer::TestWorldStreamer(EntityFactory* entityFactory)
{

	this->entityFactory = entityFactory;

}

void TestWorldStreamer::init(Vec2i& cell, Vec2f& offset)
{

	char entityText[] =
	"<entity>"
	"	<id> 2 </id>"

	"	<position>"
	"		<x>0</x>"
	"		<y>0</y>"
	"	</position>"

	"	<graphics>"
	"		<texture>elf.png</texture>"
	"		<width>50</width>"
	"		<height>75</height>"
	"	</graphics>"

	"	<physics>"
	"		<shape>box</shape>"
	"		<width>10</width>"
	"		<height>15</height>"
	"		<mass>60</mass>"
	"	</physics>"
	"</entity>"
	;

	xml_document<> doc;
	doc.parse<0>(entityText);

	xml_node<>* root = doc.first_node("entity");
	Entity* entity = entityFactory->createEntity( root, Vec2i(0, 0) );

	entities.push_back(entity);

}

void TestWorldStreamer::update(Vec2f& position)
{

}

vector<Entity*> TestWorldStreamer::getEntities()const
{
	return entities;
}
