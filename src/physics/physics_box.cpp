#include "physics_box.hpp"

Vec2f PhysicsBox::getPosition()const
{
    return Vec2f( body->GetPosition().x, body->GetPosition().y );
}

void PhysicsBox::setPosition(const Vec2f& v)
{
    body->SetTransform( b2Vec2(v.x ,v.y), 0 );
}
