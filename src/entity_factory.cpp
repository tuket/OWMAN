#include "entity_factory.hpp"
#include "cell_size.hpp"
#include "renderer/graphics_component.hpp"
#include "engine.hpp"
#include <string>

using namespace rapidxml;
using namespace std;

EntityFactory::EntityFactory(Engine* engine)
{
	countId = DEFAULT_INIT_ID;
	myEngine = engine;
}


Entity* EntityFactory::createEntity
(
	xml_node<> *node,
	const Vec2i& toCenter
)
{

	Entity* entity = new Entity;

	Vec2f pos;
	pos.x = toCenter.x * cellSize;
	pos.y = toCenter.y * cellSize;

	xml_node<> *id_node = node->first_node("id");
	if( id_node != 0 )
	{
		entity->id = atoi(id_node->value());
	}
	else
	{
		entity->id = countId;
		countId++;
	}

	// position
	xml_node<> *position_node = node->first_node("position");
		xml_node<> *x_position_node = position_node->first_node("x");
		pos.x += atof( x_position_node->value() );
		xml_node<> *y_position_node = position_node->first_node("y");
		pos.y += atof( y_position_node->value() );

	// graphics
	xml_node<> *graphics_node = node->first_node("graphics");
		xml_node<> *texture_node = graphics_node->first_node("texture");
		string textureFileName( string("img/") + texture_node->value() );
		xml_node<> *width_graphics_node = graphics_node->first_node("width");
		float width_graphics = atof( width_graphics_node->value() );
		xml_node<> *height_graphics_node = graphics_node->first_node("height");
		float height_graphics = atof( height_graphics_node->value() );

	// physics
		// TODO



	GraphicsComponent* graphicsComponent =
	myEngine->getGraphicsSystem()->createSprite
	(
		textureFileName,
		Vec2f( width_graphics, height_graphics )
	);

	entity->setGraphicsComponent( graphicsComponent );

	entity->setPosition( pos );

	return entity;

}

void EntityFactory::destroyEntity(Entity* entity)
{

	delete entity;

}
