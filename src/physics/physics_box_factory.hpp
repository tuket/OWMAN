#ifndef PHYSICS_BOX_FACTORY
#define PHYSICS_BOX_FACTORY

#include "physics_box.hpp"

class PhysicsSystem;

class PhysicsBoxFactory
{

    friend class PhysicsSystem;

    PhysicsSystem* myPhysicsSystem;

    PhysicsBoxFactory( PhysicsSystem* physicsSystem );

public:

    PhysicsBox* createPhysicsBox( const Vec2f& position, const Vec2f& scale, float mass );
    PhysicsBox* createPhysicsBoxKinematic( const Vec2f& position, const Vec2f& scale, float mass );


    void destroyPhysicsBox( PhysicsBox* physicsBox );

    PhysicsSystem* getPhysicsSystem();

};

#endif
