#include "physics_component.hpp"
#include <Box2D/Box2D.h>
#include "../math/vec2f.hpp"

#ifndef PHYSICS_BOX_FACTORY
class PhysicsBoxFactory;
#endif

#ifndef PHYSICS_BOX
#define PHYSICS_BOX

class PhysicsBox : public PhysicsComponent
{

    friend class PhysicsBoxFactory;

    b2Body* body;

    PhysicsBox(){}

public:

    Vec2f getPosition()const;
    void setPosition(const Vec2f& v);

    virtual ~PhysicsBox(){}

};

#endif
