#include "physics_box.hpp"
#include "physics_system.hpp"
#include <string>
#include <sstream>
#include "../util/xmlstr.hpp"

using namespace std;
using namespace rapidxml;

Vec2f PhysicsBox::getPosition()const
{
    return Vec2f( body->GetPosition().x, body->GetPosition().y );
}

void PhysicsBox::setPosition(const Vec2f& v)
{
    body->SetTransform( b2Vec2(v.x ,v.y), 0 );
}

Vec2f PhysicsBox::getSpeed()const
{
    return Vec2f( body->GetLinearVelocity().x, body->GetLinearVelocity().y);
}

void PhysicsBox::setSpeed(const Vec2f& v)
{
    body->SetLinearVelocity( b2Vec2( v.x, v.y ) );
}

xml_node<>* PhysicsBox::createXmlNode(xml_document<>* doc)
{

    char* s;
    xml_node<>* root = doc->allocate_node(node_element, xmlstr::physics);

    // shape
    xml_node<>* shape_node = doc->allocate_node(node_element, xmlstr::shape, xmlstr::box);
    root->append_node( shape_node );

    // width
    stringstream ss;
    ss << scale.x;
    string width = ss.str();
    s = doc->allocate_string(width.c_str());
    xml_node<>* width_node = doc->allocate_node(node_element, xmlstr::width, s);
    root->append_node( width_node );

    ss.str( string() );
    ss.clear();
    // height
    ss << scale.y;
    string height = ss.str();
    s = doc->allocate_string(height.c_str());
    xml_node<>* height_node = doc->allocate_node(node_element, xmlstr::height, s);
    root->append_node( height_node );

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

void PhysicsBox::destroyDispatcher()
{
    myPhysicsSystem->destroyPhysicsBox(this);
}
