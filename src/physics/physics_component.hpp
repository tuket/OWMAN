#ifndef PHYSICS_COMPONENT
#define PHYSICS_COMPONENT

#include "../math/vec2f.hpp"
#include "../dependencies/rapidxml/rapidxml.hpp"

class PhysicsSystem;
class b2Body;

class PhysicsComponent
{

    friend class PhysicsSystem;

protected:

    PhysicsSystem* myPhysicsSystem;

    b2Body* body;

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
    virtual rapidxml::xml_node<>* createXmlNode(rapidxml::xml_document<>* doc) = 0;

    /** \brief this will call to the corresponding PhysicsSystem function \
     * in charge of deleting this PhysicsComponent
     */
	virtual void destroyDispatcher() = 0;

};

#endif
