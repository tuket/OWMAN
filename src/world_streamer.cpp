#include "world_streamer.hpp"
#include "dependencies/rapidxml/rapidxml.hpp"
#include "util/file_to_string.hpp"
#include "math/vec2i.hpp"
#include <fstream>

using namespace std;
using namespace rapidxml;

WorldStreamer::WorldStreamer
(
	string worldFolder,
	EntityFactory* entityFactory
)
{

	this->worldFolder = worldFolder;
	this->entityFactory = entityFactory;
	this->graphicsSystem = graphicsSystem;

	char* mainCharText = fileToString(worldFolder + "/main_character.xml");

	xml_document<> mainCharDoc;
	mainCharDoc.parse<0> (mainCharText);

	xml_node<> *root = mainCharDoc.first_node("main_character");

	Vec2i mainCharPos;

	xml_node<> *posNode = root->first_node("position");
		xml_node<> *posXNode = posNode->first_node("x");
		mainCharPos.x = atoi( posXNode->value() );
		xml_node<> *posYNode = posNode->first_node("y");
		mainCharPos.y = atoi( posYNode->value() );

	windowPos = mainCharPos;

	mainCharacter = entityFactory->createEntity(mainCharNode, Vec2i(0,0));

	delete[] mainCharText;

}

void WorldStreamer::init()
{



}

void WorldStreamer::update()
{



}

Vec2i WorldStreamer::getWindowPosition()const
{
	return windowPos;
}
