#include "physics_system.hpp"

PhysicsSystem::PhysicsSystem()
{

    physicsBoxFactory = new PhysicsBoxFactory( this );
    physicsCircleFactory = new PhysicsCircleFactory( this );
    b2Vec2 gravity(0, 0);
    world = new b2World(gravity);

}

void PhysicsSystem::update(unsigned int delta)
{

    float seconds = delta / 1000.0f;
    world->Step(seconds, 12, 5);

}

PhysicsBox* PhysicsSystem::createPhysicsBox
    ( const Vec2f& position, const Vec2f& scale, float mass )
{

    PhysicsBox* physicsBox;
    physicsBox = physicsBoxFactory->createPhysicsBox(position, scale, mass);
    physicsBox->myPhysicsSystem = this;
    return physicsBox;

}

PhysicsBox* PhysicsSystem::createPhysicsBoxKinematic
    ( const Vec2f& position, const Vec2f& scale, float mass )
{

    PhysicsBox* physicsBox;
    physicsBox = physicsBoxFactory->createPhysicsBoxKinematic(position, scale, mass);
    physicsBox->myPhysicsSystem = this;
    return physicsBox;

}

PhysicsCircle* PhysicsSystem::createPhysicsCircle
    ( const Vec2f& position, float radius, float mass )
{
    PhysicsCircle* physicsCircle;
    physicsCircle = physicsCircleFactory->createPhysicsCircle(position, radius, mass);
    physicsCircle->myPhysicsSystem = this;
    return physicsCircle;
}

PhysicsCircle* PhysicsSystem::createPhysicsCircleKinematic
    ( const Vec2f& position, float radius, float mass )
{
    PhysicsCircle* physicsCircle;
    physicsCircle = physicsCircleFactory->createPhysicsCircleKinematic(position, radius, mass);
    physicsCircle->myPhysicsSystem = this;
    return physicsCircle;
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

void PhysicsSystem::destroyPhysicsCircle( PhysicsCircle* physicsCircle )
{
    physicsCircleFactory->destroyPhysicsCircle(physicsCircle);
}

b2World* PhysicsSystem::getWorld()
{
    return world;
}
