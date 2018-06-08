#ifndef PHYSICS_CIRCLE
#define PHYSICS_CIRCLE

#include "physics_component.hpp"
#include <Box2D/Box2D.h>
#include <rapidxml.hpp>
#include "../math/vec2f.hpp"

class PhysicsCircleFactory;


/**
 * This class represents a circular shaped physics body.
 */

 class PhysicsCircle : public PhysicsComponent
 {

    friend class PhysicsCircleFactory;

    float radius;

    PhysicsCircle(){}

public:

    /** \brief Creates a physics XML node
     * Returns an XML node representing the class itself
     * \param The XML document
     * \return The XML node
     */
    rapidxml::xml_node<>* createXmlNode(rapidxml::xml_document<>* doc);

    virtual ~PhysicsCircle(){}

    /** \brief this will call to the corresponding PhysicsSystem function \
     * in charge of deleting this PhysicsComponent
     */
    void destroyDispatcher();

 };

#endif // PHYSICS_CIRCLE
