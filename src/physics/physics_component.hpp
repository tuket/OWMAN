#ifndef PHYSICS_COMPONENT
#define PHYSICS_COMPONENT

#include "../math/vec2f.hpp"
#include "../dependencies/rapidxml/rapidxml.hpp"

class PhysicsSystem;

class PhysicsComponent
{

    friend class PhysicsSystem;

protected:

    PhysicsSystem* myPhysicsSystem;

public:

    virtual Vec2f getPosition()const = 0;
    virtual void setPosition(const Vec2f& v) = 0;

    virtual Vec2f getSpeed()const = 0;
    virtual void setSpeed(const Vec2f& v) = 0;

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
