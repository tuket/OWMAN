#include "physics_system.hpp"
#include "physics_box.hpp"
#include "physics_box_factory.hpp"

PhysicsSystem::PhysicsSystem()
{

    physicsBoxFactory = new PhysicsBoxFactory( this );
    b2Vec2 gravity(0, 0);
    world = new b2World(gravity);

}

void PhysicsSystem::update(unsigned int delta)
{

    world->Step(delta/1000000.0f, 96, 40);

}

PhysicsBox* PhysicsSystem::createPhysicsBox( const Vec2f& position, const Vec2f& scale, float mass )
{
    return physicsBoxFactory->createPhysicsBox(position, scale, mass);
}

PhysicsBox* PhysicsSystem::createPhysicsBoxKinematic( const Vec2f& position, const Vec2f& scale, float mass )
{
    return physicsBoxFactory->createPhysicsBoxKinematic(position, scale, mass);
}

b2World* PhysicsSystem::getWorld()
{
    return world;
}
