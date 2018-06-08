#ifndef CAMERA
#define CAMERA

#include "../math/vec2f.hpp"

class GraphicsSystem;

/** \brief High level abstraction camera
 * You can set the position and dimensions of the camera
 */
class Camera
{

	friend class GraphicsSystem;

	GraphicsSystem* myGraphicsSystem;

public:

	Camera(){}

	Vec2f getPosition()const;
	void setPosition(const Vec2f& position);

	float getWidth()const;
	float getHeight()const;

	void setWidth(float width);
	void setHeight(float height);

};

#endif
