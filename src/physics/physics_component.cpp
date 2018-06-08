#include "physics_component.hpp"
#include <Box2D/Box2D.h>

Vec2f PhysicsComponent::getPosition()const
{
    return Vec2f( body->GetPosition().x, body->GetPosition().y );
}

void PhysicsComponent::setPosition(const Vec2f& v)
{
    body->SetTransform( b2Vec2(v.x ,v.y), 0 );
}

Vec2f PhysicsComponent::getSpeed()const
{
    return Vec2f( body->GetLinearVelocity().x, body->GetLinearVelocity().y);
}

void PhysicsComponent::setSpeed(const Vec2f& v)
{
    body->SetLinearVelocity( b2Vec2( v.x, v.y ) );
}
