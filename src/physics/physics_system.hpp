#include <Box2D/Box2D.h>
#include "../math/vec2f.hpp"

#ifndef PHYSICS_COMPONENT
class PhysicsComponent;
#endif

#ifndef PHYSICS_BOX
class PhysicsBox;
#endif

 #ifndef PHYSICS_BOX_FACTORY
 class PhysicsBoxFactory;
 #endif

#ifndef PHYSICS_SYSTEM
#define PHYSICS_SYSTEM

class PhysicsSystem
{

    b2World* world;

    PhysicsBoxFactory* physicsBoxFactory;

public:

    PhysicsSystem();

    void update(unsigned int delta);

    PhysicsBox* createPhysicsBox( const Vec2f& position, const Vec2f& scale, float mass );
    PhysicsBox* createPhysicsBoxKinematic( const Vec2f& position, const Vec2f& scale, float mass );

    void destroyPhysicsComponent( PhysicsComponent* physicsComponent );
    void destroyPhysicsBox( PhysicsBox* physicsBox );

    b2World* getWorld();

};

#endif

