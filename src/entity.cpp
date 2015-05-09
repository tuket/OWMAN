#include "entity.hpp"
#include "renderer/graphics_component.hpp"
#include "physics/physics_component.hpp"

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

Entity::~Entity()
{

	if( graphicsComponent != 0 )
	{
		delete graphicsComponent;
	}

}
