#include "entity.hpp"
#include "renderer/graphics_component.hpp"
#include "physics/physics_component.hpp"
#include <string>
#include <sstream>

using namespace std;
using namespace rapidxml;

Entity::Entity()
{
	id = 0;		// 0 is invalid
	typeId = "";
	graphicsComponent = 0;
	physicsComponent = 0;
}

Entity::TypeId Entity::getTypeOfEntity()const
{
	return typeId;
}

Entity::Id Entity::getId()const
{
	return id;
}

Vec2f Entity::getPosition()const
{

	if( physicsComponent )
    {
        return physicsComponent->getPosition();
    }
    else if( graphicsComponent )
    {
        return graphicsComponent->getPosition();
    }

    return Vec2f();

}

void Entity::setPosition(const Vec2f& pos)
{

	if( physicsComponent )
    {
        physicsComponent->setPosition( pos );
    }
    else if( graphicsComponent )
    {
        graphicsComponent->setPosition( pos );
    }

}

GraphicsComponent* Entity::getGraphicsComponent()
{
	return graphicsComponent;
}

void Entity::setGraphicsComponent(GraphicsComponent* component)
{
	graphicsComponent = component;
}

void Entity::setPhysicsComponent(PhysicsComponent* component)
{
    physicsComponent = component;
}

PhysicsComponent* Entity::getPhysicsComponent()
{
    return physicsComponent;
}

xml_node<>* Entity::createXmlNode(xml_document<>* doc, float cellSize)
{

        xml_node<>* node_ent;
        node_ent = doc->allocate_node(node_element, "entity");


        float x = getPosition().x;
        float y = getPosition().y;

        while( x < 0 ) x += cellSize;
        while( x >= cellSize) x -= cellSize;
        while( y < 0) y += cellSize;
        while( y >= cellSize ) y -= cellSize;

        xml_node<>* pos_node = doc->allocate_node(node_element, "position");
        node_ent->append_node( pos_node );

        stringstream ss;
        ss << x;
        string sx = ss.str();
        char* s = doc->allocate_string(sx.c_str());
        xml_node<>* x_node = doc->allocate_node(node_element, "x", s);
        pos_node->append_node( x_node );

        ss.str( string() );
        ss.clear();
        ss << y;
        string sy = ss.str();
        s = doc->allocate_string(sy.c_str());
        xml_node<>* y_node = doc->allocate_node(node_element, "y", s);
        pos_node->append_node( y_node );

        if( graphicsComponent )
        {
            xml_node<>* graphics_node = getGraphicsComponent()->createXmlNode(doc);
            node_ent->append_node( graphics_node );
        }

        if( physicsComponent )
        {
            xml_node<>* physics_node = getPhysicsComponent()->createXmlNode(doc);
            node_ent->append_node( physics_node );
        }

        return node_ent;


}

Entity::~Entity()
{

	if( graphicsComponent != 0 )
	{
		delete graphicsComponent;
	}

}
