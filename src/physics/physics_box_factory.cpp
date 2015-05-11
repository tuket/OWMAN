#include "physics_box_factory.hpp"
#include "physics_system.hpp"
#include <Box2D/Box2D.h>

PhysicsBoxFactory::PhysicsBoxFactory( PhysicsSystem* physicsSystem )
{
    myPhysicsSystem = physicsSystem;
}

PhysicsBox* PhysicsBoxFactory::createPhysicsBox( const Vec2f& position, const Vec2f& scale, float mass )
{

    b2World* world = myPhysicsSystem->getWorld();

    PhysicsBox* res = new PhysicsBox;
    res->scale = scale;

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    bodyDef.active = true;
    bodyDef.position.Set(position.x, position.y);
    bodyDef.linearDamping = 0.1;
    res->body = world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(scale.x/2, scale.y/2);

    b2FixtureDef fixtureDef;
    fixtureDef.density = mass/(scale.x*scale.y);
    fixtureDef.shape = &shape;

    res->body->CreateFixture(&fixtureDef);

    return res;

}

PhysicsBox* PhysicsBoxFactory::createPhysicsBoxKinematic( const Vec2f& position, const Vec2f& scale, float mass )
{

    b2World* world = myPhysicsSystem->getWorld();

    PhysicsBox* res = new PhysicsBox;
    res->scale = scale;

    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    bodyDef.fixedRotation = true;
    bodyDef.active = true;
    bodyDef.position.Set(position.x, position.y);
    bodyDef.linearDamping = 0.1;
    res->body = world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(scale.x/2, scale.y/2);

    b2FixtureDef fixtureDef;
    fixtureDef.density = mass/(scale.x*scale.y);
    fixtureDef.shape = &shape;

    res->body->CreateFixture(&fixtureDef);

    return res;

}

void PhysicsBoxFactory::destroyPhysicsBox( PhysicsBox* physicsBox )
{

    b2World* world = myPhysicsSystem->getWorld();

    world->DestroyBody( physicsBox->body );
    delete physicsBox;

}

PhysicsSystem* PhysicsBoxFactory::getPhysicsSystem()
{
    return myPhysicsSystem;
}
