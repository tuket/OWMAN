#include "physics_circle.hpp"
#include "../util/xmlstr.hpp"
#include <sstream>
#include "physics_system.hpp"

using namespace std;
using namespace rapidxml;

xml_node<>* PhysicsCircle::createXmlNode(xml_document<>* doc)
{
    char* s;
    xml_node<>* root = doc->allocate_node(node_element, xmlstr::physics);

    // shape
    xml_node<>* shape_node = doc->allocate_node(node_element, xmlstr::shape, xmlstr::circle);
    root->append_node( shape_node );

    // radius
    stringstream ss;
    ss << radius;
    string radStr = ss.str();
    s = doc->allocate_string(radStr.c_str());
    xml_node<>* width_node = doc->allocate_node(node_element, xmlstr::radius, s);
    root->append_node( width_node );

    ss.str( string() );
    ss.clear();
    // mass
    ss << body->GetMass();
    string mass = ss.str();
    s = doc->allocate_string(mass.c_str());
    xml_node<>* mass_node = doc->allocate_node(node_element, xmlstr::mass, s);
    root->append_node( mass_node );

    return root;
}

void PhysicsCircle::destroyDispatcher()
{
    myPhysicsSystem->destroyPhysicsCircle(this);
}
