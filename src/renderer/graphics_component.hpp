#include "../math/vec2f.hpp"

#ifndef ENTITY
class Entity;
#endif

#ifndef GRAPHICS_SYSTEM
class GraphicsSystem;
#endif

#ifndef GRAPHICS_COMPONENT
#define GRAPHICS_COMPONENT

class GraphicsComponent
{
	
	friend class Entity;
	friend class GraphicsSystem;

protected:

	Entity* myEntity;
	GraphicsSystem* myGraphicsSystem;
	bool visible;
	
	Vec2f position;
	Vec2f scale;
	
public:

	GraphicsComponent()
	:visible(true){}
	
	virtual void update(unsigned int delta) = 0;
	virtual void draw()const = 0;
	
	bool isVisible()const;
	void setVisible(bool visible);
	
	virtual bool isReady()const = 0;
	virtual bool isLoaded()const = 0;
	
	virtual void becomeReady()const = 0;
	
	Vec2f getPosition()const;
	Vec2f getScale()const;
	void setPosition(const Vec2f& position);
	void setScale(const Vec2f& scale);
	
};

#endif
