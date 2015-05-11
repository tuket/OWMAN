#include "sprite.hpp"
#include "graphics_system.hpp"
#include "../resource_manager/resource_manager.hpp"
#include "../resource_manager/resource_texture.hpp"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
using namespace rapidxml;

bool Sprite::isReady()const
{
	return resourceTexture->getStatus() == Resource::Status::READY;
}

bool Sprite::isLoaded()const
{
	return resourceTexture->getStatus() == Resource::Status::LOADED;
}

void Sprite::becomeReady()const
{
	resourceTexture->loadToGraphicsCard();
}

void Sprite::draw()const
{

	LowLevelRenderer2D* renderer = myFactory->getGraphicsSystem()->getRenderer();
	renderer->draw(position, scale, resourceTexture->getTexture());

}

xml_node<>* Sprite::createXmlNode(xml_document<>* doc)
{

    char* s;
    xml_node<>* root = doc->allocate_node(node_element, "graphics");

    string textureName = resourceTexture->getName();
    unsigned int i = textureName.size()-1;
    while( textureName[i] != '/' && i >= 0 ) i--;
    if( textureName[i] == '/' ) i++;
    string tn;
    while( i < textureName.size() ) tn += textureName[i++];

    s = doc->allocate_string(tn.c_str());
    xml_node<>* texture_node = doc->allocate_node(node_element, "texture", s);
    root->append_node( texture_node );

    Vec2f scale = getScale();
    stringstream ss;
    ss << scale.x;
    string width = ss.str();

    ss.str( string() );
    ss.clear();

    ss << scale.y;
    string height = ss.str();

    s = doc->allocate_string(width.c_str());
    xml_node<>* width_node = doc->allocate_node(node_element, "width", s);
    root->append_node( width_node );

    s = doc->allocate_string(height.c_str());
    xml_node<>* height_node = doc->allocate_node(node_element, "height", s);
    root->append_node( height_node );

    return root;

}

Sprite::~Sprite()
{

	ResourceManager* resourceManager = ResourceManager::getSingleton();
	resourceManager->releaseTexture( resourceTexture );

}

void Sprite::destroyDispatcher()
{

    myGraphicsSystem->destroySprite( this );

}
