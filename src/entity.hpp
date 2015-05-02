#include <string>
#include "position.hpp"

#ifndef GRAPHICS_COMPONENT
class GraphicsComponent;
#endif

#ifndef ENTITY
#define ENTITY

class Entity
{

public:

	typedef std::string TypeId;
	typedef unsigned int Id;

	friend class EntityFactory;

protected:

	TypeId typeId;
	Id id;

	GraphicsComponent* graphicsComponent;
	// Physics component here

	Entity();

	void setGraphicsComponent(GraphicsComponent* component);

public:

	TypeId getTypeOfEntity()const;
	Id getId()const;

	Vec2f getPosition()const;
	void setPosition(const Vec2f& pos);

	GraphicsComponent* getGraphicsComponent();

	~Entity();

};

#endif
