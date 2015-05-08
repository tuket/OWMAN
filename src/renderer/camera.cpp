#include "camera.hpp"
#include "graphics_system.hpp"

Vec2f Camera::getPosition()const
{
	return myGraphicsSystem->getRenderer()->getCamera()->getPosition();
}

void Camera::setPosition(const Vec2f& position)
{
	myGraphicsSystem->getRenderer()->getCamera()->setPosition(position);
}

float Camera::getWidth()const
{
    return myGraphicsSystem->getRenderer()->getCamera()->getWidth();
}

float Camera::getHeight()const
{
    return myGraphicsSystem->getRenderer()->getCamera()->getHeight();
}

void Camera::setWidth(float width)
{
	myGraphicsSystem->getRenderer()->getCamera()->setWidth(width);
}

void Camera::setHeight(float height)
{
	myGraphicsSystem->getRenderer()->getCamera()->setHeight(height);
}
