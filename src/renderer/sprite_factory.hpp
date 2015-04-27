#include "sprite.hpp"
#include <string>

#ifndef GRAPHICS_SYSTEM
class GraphicsSystem;
#endif

#ifndef SPRITE_FACTOTY
#define SPRITE_FACTORY

class SpriteFactory
{
	
	friend class GraphicsSystem;
	
	GraphicsSystem* myGraphicsSystem;
	
	SpriteFactory(GraphicsSystem* graphicsSystem);
	
public:
	
	void destroyGraphicsComponent(GraphicsComponent* graphicsComponent);
	
	Sprite* createSprite(std::string fileName, const Vec2f& scale);
	void destroySprite(Sprite* sprite);
	
	GraphicsSystem* getGraphicsSystem();
	
};

#endif
