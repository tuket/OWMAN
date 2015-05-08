#include <vector>
#include "math/vec2i.hpp"
#include "math/vec2f.hpp"

#ifndef ENTITY
class Entity;
#endif

#ifndef ENTITY_FACTORY
class EntityFactory;
#endif

#ifndef I_WORLD_STREAMER
#define I_WORLD_STREAMER

class IWorldStreamer
{

protected:

	EntityFactory* entityFactory;

public:

	IWorldStreamer(){}

	IWorldStreamer(EntityFactory* entityFactory);

	EntityFactory* getEntityFactory()const;
	void setEntityFactory(EntityFactory* entityFactory);

	/**
	 * \brief Inits the world streamer.
	 * \param cell the cell where the main character is located.
	 * \param offset of the character wrt the cell bot left corner.
	 * Both params could be ignored by the implementation.
	 **/
	virtual void init(Vec2i& cell, Vec2f& offset) = 0;

	/**
	 * \brief Updates the world streamer.
	 * \param offset of the character wrt the cell bot left corner.
	 * The param could be ignored by the implementation.
	 **/
	virtual void update(Vec2f& position) = 0;

	/**
	 * \brief Returns a vector of pointers to all the active entities
	 *
	 **/
	virtual std::vector<Entity*> getEntities()const = 0;

	virtual float getCellSize()const;

	virtual ~IWorldStreamer(){}

};

#endif
