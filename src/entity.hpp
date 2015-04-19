#include <string>
#include "position.hpp"

#ifndef GRAPHICS_COMPONENT
class GraphicsComponent;
#endif

#ifndef ENTITY
#define ENTITY

class Entity
{
	
	typedef std::string TypeId;
	typedef unsigned int Id;
	
	friend class EntityFactory;
	
	TypeId typeId;
	Id id;
	
	GraphicsComponent* graphicsComponent;
	
	Entity();
	
public:
	
	TypeId getTypeOfEntity()const;
	Id getId()const;
	
	Vec2f getPosition()const;
	void setPosition(const Vec2f& pos);
	
	GraphicsComponent* getGraphicsComponent();
	void setGraphicsComponent(GraphicsComponent* component);
	
};

#endif
