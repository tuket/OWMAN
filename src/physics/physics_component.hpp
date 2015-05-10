#include "../math/vec2f.hpp"

#ifndef PHYSICS_SYSTEM
class PhysicsSystem;
#endif

#ifndef PHYSICS_COMPONENT
#define PHYSICS_COMPONENT

class PhysicsComponent
{

    friend class PhysicsSystem;

protected:

    PhysicsSystem* myPhysicsSystem;

public:

    virtual Vec2f getPosition()const = 0;
    virtual void setPosition(const Vec2f& v) = 0;

    /** \brief this will call to the corresponding PhysicsSystem function \
     * in charge of deleting this PhysicsComponent
     */
	virtual void destroyDispatcher() = 0;

};

#endif
