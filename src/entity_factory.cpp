#include "entity_factory.hpp"
#include "cell_size.hpp"
#include "renderer/graphics_component.hpp"
#include "physics/physics_component.hpp"
#include "physics/physics_box.hpp"
#include "engine.hpp"
#include "renderer/sprite_status.hpp"
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
	pos.x = toCenter.x * myEngine->getCellSize();
	pos.y = toCenter.y * myEngine->getCellSize();

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
	if( graphics_node )
	{

		xml_node<> *sprite_node = graphics_node->first_node("sprite");
		string spriteName = sprite_node->value();
		xml_node<> *width_graphics_node = graphics_node->first_node("width");
		float width_graphics = atof( width_graphics_node->value() );
		xml_node<> *height_graphics_node = graphics_node->first_node("height");
		float height_graphics = atof( height_graphics_node->value() );
		xml_node<> *priority_node = graphics_node->first_node("priority");

		GraphicsComponent* graphicsComponent =
        myEngine->getGraphicsSystem()->instanceSprite
        (
            spriteName,
            Vec2f( width_graphics, height_graphics )
        );

        if( priority_node )
		{
            int priority = atoi( priority_node->value() );
            graphicsComponent->setPriority( priority );
		}

        entity->setGraphicsComponent( graphicsComponent );

    }

	// physics
	xml_node<> *physics_node = node->first_node("physics");
	if( physics_node )
	{

        xml_node<> *shape_node = physics_node->first_node("shape");
        string sShape( shape_node->value() );
        xml_node<> *width_physics_node = physics_node->first_node("width");
        float width_physics = atof( width_physics_node->value() );
        xml_node<> *height_physics_node = physics_node->first_node("height");
        float height_physics = atof( height_physics_node->value() );
        xml_node<> *mass_node = physics_node->first_node("mass");
        float mass = atof( mass_node->value() );

        PhysicsComponent* physicsComponent =
        myEngine->getPhysicsSystem()->createPhysicsBox
        (
            pos,
            Vec2f(width_physics, height_physics),
            mass
        );

        entity->setPhysicsComponent( physicsComponent );

    }


	entity->setPosition( pos );

	return entity;

}

MainCharacter* EntityFactory::createMainCharacter(rapidxml::xml_node<> *node)
{

    MainCharacter* entity = new MainCharacter;

	Vec2f pos;

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
        xml_node<> *cell_x_node = position_node->first_node("cell_x");
        int cell_x = atoi( cell_x_node->value() );
        xml_node<> *cell_y_node = position_node->first_node("cell_y");
        int cell_y = atoi( cell_y_node->value() );
		xml_node<> *x_position_node = position_node->first_node("x");
		pos.x = atof( x_position_node->value() );
		xml_node<> *y_position_node = position_node->first_node("y");
		pos.y = atof( y_position_node->value() );

	// graphics
	xml_node<> *graphics_node = node->first_node("graphics");
	if( graphics_node )
	{

		xml_node<> *sprite_node = graphics_node->first_node("sprite");
		string spriteName = sprite_node->value();
		xml_node<> *width_graphics_node = graphics_node->first_node("width");
		float width_graphics = atof( width_graphics_node->value() );
		xml_node<> *height_graphics_node = graphics_node->first_node("height");
		float height_graphics = atof( height_graphics_node->value() );
		xml_node<> *priority_node = graphics_node->first_node("priority");

		GraphicsComponent* graphicsComponent =
        myEngine->getGraphicsSystem()->instanceSprite
        (
            spriteName,
            Vec2f( width_graphics, height_graphics )
        );

        if( priority_node )
		{
            int priority = atoi( priority_node->value() );
            graphicsComponent->setPriority( priority );
		}

        entity->setGraphicsComponent( graphicsComponent );

    }

	// physics
    xml_node<> *physics_node = node->first_node("physics");

    if( physics_node )
    {

        xml_node<> *shape_node = physics_node->first_node("shape");
        string sShape( shape_node->value() );
        xml_node<> *width_physics_node = physics_node->first_node("width");
        float width_physics = atof( width_physics_node->value() );
        xml_node<> *height_physics_node = physics_node->first_node("height");
        float height_physics = atof( height_physics_node->value() );
        xml_node<> *mass_node = physics_node->first_node("mass");
        float mass = atof( mass_node->value() );

        PhysicsComponent* physicsComponent =
        myEngine->getPhysicsSystem()->createPhysicsBoxKinematic
        (
            pos,
            Vec2f(width_physics, height_physics),
            mass
        );

        entity->setPhysicsComponent( physicsComponent );

    }


	entity->setPosition( pos );
	entity->setCell( Vec2i(cell_x, cell_y) );

	return entity;

}

void EntityFactory::destroyEntity(Entity* entity)
{

    GraphicsComponent* gc = entity->getGraphicsComponent();
    if( gc )
    {
        myEngine->getGraphicsSystem()->destroyGraphicsComponent( gc );
    }

	PhysicsComponent* pc = entity->getPhysicsComponent();
	if( pc )
	{
        myEngine->getPhysicsSystem()->destroyPhysicsComponent(pc);
    }

}
