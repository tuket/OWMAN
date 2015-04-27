#include <vector>

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
	
	/**
	 * \brief Inits the world streamer.
	 * \param cell the cell where the main character is located.
	 * \param offset of the character wrt the cell bot left corner.
	 * Both params could be ingnored by the implementation.
	 **/
	void init(Vec2i cell, Vec2f offset);
	
	/**
	 * \brief Updates the world streamer.
	 * \param cell the cell where the main character is located.
	 * \param offset of the character wrt the cell bot left corner.
	 * Both params could be ingnored by the implementation.
	 **/
	void update(Vec2i cell, Vec2f offset);
	
	/**
	 * \brief Returns a vector of pointers to all the active entities
	 * 
	 **/
	std::vector<Entity*> getActiveEntities()const;
	
};

#endif
