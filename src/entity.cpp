#include "entity.hpp"
#include "renderer/graphics_component.hpp"

Entity::Entity()
{
	id = 0;		// 0 is invalid
	typeId = "";
	graphicsComponent = 0;
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
	return graphicsComponent->getPosition();
}

void Entity::setPosition(const Vec2f& pos)
{
	graphicsComponent->setPosition( pos );
}

GraphicsComponent* Entity::getGraphicsComponent()
{
	return graphicsComponent;
}

void Entity::setGraphicsComponent(GraphicsComponent* component)
{
	graphicsComponent = component;
}

Entity::~Entity()
{

	if( graphicsComponent != 0 )
	{
		delete graphicsComponent;
	}

}
