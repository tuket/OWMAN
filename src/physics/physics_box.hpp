#ifndef PHYSICS_BOX
#define PHYSICS_BOX

#include "physics_component.hpp"
#include <Box2D/Box2D.h>
#include "../math/vec2f.hpp"

class PhysicsBoxFactory;


/**
 * This class represents a box shaped physics body.
 */

class PhysicsBox : public PhysicsComponent
{

    friend class PhysicsBoxFactory;

    b2Body* body;

    Vec2f scale;

    PhysicsBox(){}

public:

    Vec2f getPosition()const;
    void setPosition(const Vec2f& v);

    Vec2f getSpeed()const;
    void setSpeed(const Vec2f& v);

    /** \brief Creates a physics XML node
     * Returns an XML node representing the class itself
     * \param The XML document
     * \return The XML node
     */
    rapidxml::xml_node<>* createXmlNode(rapidxml::xml_document<>* doc);

    virtual ~PhysicsBox(){}

    /** \brief this will call to the corresponding PhysicsSystem function \
     * in charge of deleting this PhysicsComponent
     */
    void destroyDispatcher();

};

#endif
