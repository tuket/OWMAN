#include "graphics_component.hpp"
#include "graphics_system.hpp"

bool GraphicsComponent::isVisible()const
{
	return visible;
}

void GraphicsComponent::setVisible(bool visible)
{
	this->visible = visible;
}

Vec2f GraphicsComponent::getPosition()const
{
	return position;
}

Vec2f GraphicsComponent::getScale()const
{
	return scale;
}

void GraphicsComponent::setPosition(const Vec2f& position)
{
	this->position = position;
}

void GraphicsComponent::setScale(const Vec2f& scale)
{
	this->scale = scale;
}

int GraphicsComponent::getPriority()const
{
	return priority;
}

void GraphicsComponent::setPriority(int priority)
{
	this->priority = priority;
}


