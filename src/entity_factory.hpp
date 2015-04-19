#include "entity.hpp"
#include "dependencies/rapidxml/rapidxml.hpp"

#ifndef ENGINE
class Engine;
#endif

#ifndef ENTITY_FACTORY
#define ENTITY_FACTORY

class EntityFactory
{
	
	Engine* myEngine;
	
	unsigned int countId;
	
public:
	
	EntityFactory(){}
	EntityFactory(Engine* engine);
	
	Entity* createEntity(rapidxml::xml_node<> *node, const Vec2i& toCenter);
	void destroyEntity(Entity* entity);
	
};

#endif
