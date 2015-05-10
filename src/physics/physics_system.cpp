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

    PhysicsBox* physicsBox;
    physicsBox = physicsBoxFactory->createPhysicsBox(position, scale, mass);
    physicsBox->myPhysicsSystem = this;
    return physicsBox;

}

PhysicsBox* PhysicsSystem::createPhysicsBoxKinematic( const Vec2f& position, const Vec2f& scale, float mass )
{

    PhysicsBox* physicsBox;
    physicsBox = physicsBoxFactory->createPhysicsBoxKinematic(position, scale, mass);
    physicsBox->myPhysicsSystem = this;
    return physicsBox;

}

// destroyers

void PhysicsSystem::destroyPhysicsComponent( PhysicsComponent* physicsComponent )
{
    physicsComponent->destroyDispatcher();
}

void PhysicsSystem::destroyPhysicsBox( PhysicsBox* physicsBox )
{
    physicsBoxFactory->destroyPhysicsBox( physicsBox );
}

b2World* PhysicsSystem::getWorld()
{
    return world;
}
