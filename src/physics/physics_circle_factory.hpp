#ifndef PHYSICS_CIRCLE_FACTORY
#define PHYSICS_CIRCLE_FACTORY

#include "physics_circle.hpp"

class PhysicsCircleFactory
{

    friend class PhysicsSystem;

    PhysicsSystem* myPhysicsSystem;

    PhysicsCircleFactory( PhysicsSystem* physicsSystem );

public:

    PhysicsCircle* createPhysicsCircle( const Vec2f& position, float radius, float mass );
    PhysicsCircle* createPhysicsCircleKinematic( const Vec2f& position, float radius, float mass );


    void destroyPhysicsCircle( PhysicsCircle* physicsCircle );

    PhysicsSystem* getPhysicsSystem();

};

#endif // PHYSICS_CIRCLE_FACTORY
