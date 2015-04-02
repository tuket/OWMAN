#include "../math/vec2f.hpp"

#ifndef GRAPHICS_SYSTEM
class GraphicsSystem;
#endif

#ifndef CAMERA
#define CAMERA

class Camera
{
	
	friend class GraphicsSystem;
	
	GraphicsSystem* myGraphicsSystem;

public:
	
	Camera(){}
	
	Vec2f getPosition()const;
	void setPosition(const Vec2f& position);
	
	void setWidth(float width);
	void setHeight(float height);
	
};

#endif
