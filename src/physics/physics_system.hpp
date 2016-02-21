#ifndef PHYSICS_SYSTEM
#define PHYSICS_SYSTEM

#include <Box2D/Box2D.h>
#include "../math/vec2f.hpp"

#include "physics_component.hpp"
#include "physics_box.hpp"
#include "physics_box_factory.hpp"
#include "physics_circle.hpp"
#include "physics_circle_factory.hpp"

class PhysicsSystem
{

    b2World* world;

    PhysicsBoxFactory* physicsBoxFactory;
    PhysicsCircleFactory* physicsCircleFactory;

public:

    PhysicsSystem();

    void update(unsigned int delta);

    /** \brief Create a dynamic box
     * Dynamic means that it is affected by forces
     */
    PhysicsBox* createPhysicsBox( const Vec2f& position, const Vec2f& scale, float mass );

    /** \brief Create a kinematic box
     * Kinematic means that it is not affected by forces
     */
    PhysicsBox* createPhysicsBoxKinematic( const Vec2f& position, const Vec2f& scale, float mass );

    /** \brief Create a dynamic circle
    * Dynamic means that it is affected by forces
    */
    PhysicsCircle* createPhysicsCircle( const Vec2f& position, float radius, float mass );

    /** \brief Create a kinematic circle
    * Kinematic means that it is not affected by forces
    */
    PhysicsCircle* createPhysicsCircleKinematic( const Vec2f& position, float radius, float mass );

    void destroyPhysicsComponent( PhysicsComponent* physicsComponent );
    void destroyPhysicsBox( PhysicsBox* physicsBox );
    void destroyPhysicsCircle( PhysicsCircle* physicsCircle );

    b2World* getWorld();

};

#endif

