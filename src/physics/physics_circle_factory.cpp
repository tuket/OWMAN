#include "physics_circle_factory.hpp"
#include "physics_system.hpp"
#include <Box2D/Box2D.h>
#include <iostream>
#include "../math/functions.hpp"

using namespace std;

PhysicsCircleFactory::PhysicsCircleFactory( PhysicsSystem* physicsSystem )
{
    myPhysicsSystem = physicsSystem;
}

PhysicsCircle* PhysicsCircleFactory::createPhysicsCircle
    ( const Vec2f& position, float radius, float mass )
{

    b2World* world = myPhysicsSystem->getWorld();

    PhysicsCircle* res = new PhysicsCircle;
    res->radius = radius;

    b2BodyDef bodyDef;
    bodyDef.type = (mass == 0) ? b2_staticBody : b2_dynamicBody;
    bodyDef.fixedRotation = true;
    bodyDef.active = true;
    bodyDef.position.Set(position.x, position.y);
    bodyDef.linearDamping = 0.2;
    res->body = world->CreateBody(&bodyDef);

    b2CircleShape shape;
    shape.m_radius = radius;

    b2FixtureDef fixtureDef;
    fixtureDef.density = mass/(M_PI * radius*radius);
    fixtureDef.restitution = 0.5;
    fixtureDef.shape = &shape;

    res->body->CreateFixture(&fixtureDef);

    return res;

}

PhysicsCircle* PhysicsCircleFactory::createPhysicsCircleKinematic
    ( const Vec2f& position, float radius, float mass )
{

    b2World* world = myPhysicsSystem->getWorld();

    PhysicsCircle* res = new PhysicsCircle;
    res->radius = radius;

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    bodyDef.active = true;
    bodyDef.position.Set(position.x, position.y);
    bodyDef.linearDamping = 0.01;
    res->body = world->CreateBody(&bodyDef);

    b2CircleShape shape;
    shape.m_radius = radius;

    b2FixtureDef fixtureDef;
    fixtureDef.density = mass/(M_PI * radius*radius);
    fixtureDef.shape = &shape;

    res->body->CreateFixture(&fixtureDef);

    return res;

}

void PhysicsCircleFactory::destroyPhysicsCircle( PhysicsCircle* physicsCircle )
{

    b2World* world = myPhysicsSystem->getWorld();

    world->DestroyBody( physicsCircle->body );
    delete physicsCircle;

}

PhysicsSystem* PhysicsCircleFactory::getPhysicsSystem()
{
    return myPhysicsSystem;
}
