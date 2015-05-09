#include <string>
#include "position.hpp"

#ifndef GRAPHICS_COMPONENT
class GraphicsComponent;
#endif

#ifndef PHYSICS_COMPONENT
class PhysicsComponent;
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
	PhysicsComponent* physicsComponent;

	Entity();

	void setGraphicsComponent(GraphicsComponent* component);
	void setPhysicsComponent(PhysicsComponent* component);

public:

	TypeId getTypeOfEntity()const;
	Id getId()const;

	Vec2f getPosition()const;
	void setPosition(const Vec2f& pos);

	GraphicsComponent* getGraphicsComponent();
	PhysicsComponent* getPhysicsComponent();

	~Entity();

};

#endif
