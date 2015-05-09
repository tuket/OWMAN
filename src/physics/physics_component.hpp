#include "../math/vec2f.hpp"

#ifndef PHYSICS_COMPONENT
#define PHYSICS_COMPONENT

class PhysicsComponent
{


public:

    virtual Vec2f getPosition()const = 0;
    virtual void setPosition(const Vec2f& v) = 0;

};

#endif
