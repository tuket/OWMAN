#ifndef PHYSICS_SYSTEM
#define PHYSICS_SYSTEM

#include <Box2D/Box2D.h>
#include "../math/vec2f.hpp"

class PhysicsComponent;
class PhysicsBox;
class PhysicsBoxFactory;

class PhysicsSystem
{

    b2World* world;

    PhysicsBoxFactory* physicsBoxFactory;

public:

    PhysicsSystem();

    void update(unsigned int delta);

    /** \brief Create a dynamic box
     * Dynamic means that is is affected by forces
     */
    PhysicsBox* createPhysicsBox( const Vec2f& position, const Vec2f& scale, float mass );

    /** \brief Create a kinematic box
     * Kinematic means that it is not affected by forces
     */
    PhysicsBox* createPhysicsBoxKinematic( const Vec2f& position, const Vec2f& scale, float mass );

    void destroyPhysicsComponent( PhysicsComponent* physicsComponent );
    void destroyPhysicsBox( PhysicsBox* physicsBox );

    b2World* getWorld();

};

#endif

