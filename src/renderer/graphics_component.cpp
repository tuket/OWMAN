#include "graphics_component.hpp"
#include "graphics_system.hpp"
#include <sstream>
#include "../util/xmlstr.hpp"

using namespace std;
using namespace rapidxml;

GraphicsComponent::GraphicsComponent(GraphicsSystem* graphicsSystem)
:
myGraphicsSystem(graphicsSystem),
visible(true),
priority(0),
position(0, 0),
scale(1, 1)
{}

GraphicsSystem* GraphicsComponent::getGraphicsSystem()
{
    return myGraphicsSystem;
}

bool GraphicsComponent::isVisible()const
{
	return visible;
}

void GraphicsComponent::setVisible(bool visible)
{
	this->visible = visible;
}

const Vec2f& GraphicsComponent::getPosition()const
{
	return position;
}

Vec2f& GraphicsComponent::getPosition()
{
	return position;
}

Vec2f GraphicsComponent::getScale()const
{
	return scale;
}

void GraphicsComponent::setPosition(const Vec2f& position)
{
	this->position = position;
}

void GraphicsComponent::setScale(const Vec2f& scale)
{
	this->scale = scale;
}

int GraphicsComponent::getPriority()const
{
	return priority;
}

void GraphicsComponent::setPriority(int priority)
{
	this->priority = priority;
}

rapidxml::xml_node<>* GraphicsComponent::createXmlNode(rapidxml::xml_document<>* doc)
{
    xml_node<>* root = doc->allocate_node(node_element, xmlstr::graphics);
    stringstream ss;
    // scaleX
    ss << scale.x;
    const char* scaleX = doc->allocate_string( ss.str().c_str() );
    // clear
    ss.clear();
    ss.str(string());
    //scaleY
    ss << scale.y;
    const char* scaleY = doc->allocate_string( ss.str().c_str() );
    // clear
    ss.clear();
    ss.str(string());
    // priority
    ss << priority;
    const char* prio = doc->allocate_string( ss.str().c_str() );
    // allocate strings

    // allocate nodes
    xml_node<>* node_width = doc->allocate_node(node_element, xmlstr::width, scaleX);
    xml_node<>* node_height = doc->allocate_node(node_element, xmlstr::height, scaleY);
    xml_node<>* node_priority = doc->allocate_node(node_element, xmlstr::priority, prio);
    // attach nodes
    root->append_node(node_width);
    root->append_node(node_height);
    root->append_node(node_priority);
    return root;
}
