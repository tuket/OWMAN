#include "entity.hpp"
#include "main_character.hpp"
#include <rapidxml.hpp>

#ifndef ENGINE
class Engine;
#endif

#ifndef ENTITY_FACTORY
#define ENTITY_FACTORY

class EntityFactory
{

	Engine* myEngine;

	// Entities con be created by suplying a fixed id,
	// otherwise it will be assigned an arbitrary id
	// If you are giving a fixed id to an entity in the xml file
	// you must choose a number between 1 and DEFAULT_INIT_ID
	static const Entity::Id DEFAULT_INIT_ID = 0x1000000;

	// 0 means invalid id
	Entity::Id countId;

public:

	EntityFactory(){}
	EntityFactory(Engine* engine);

	/**
	 * \brief Create an entity
	 * \param node The root xml node
	 * \param toCenter Number of cells to the center of the world window
	 * \return A pointer to the entity. Use destroyEntity() to release.
	 **/
	Entity* createEntity(rapidxml::xml_node<> *node, const Vec2i& toCenter);


    /**
	 * \brief Create a main character
	 * \param node The root xml node
	 * \return A pointer to the entity. Use destroyEntity() to release.
	 **/
	MainCharacter* createMainCharacter(rapidxml::xml_node<> *node);

	void destroyEntity(Entity* entity);

};

#endif
