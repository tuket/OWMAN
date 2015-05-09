#include "graphics_component.hpp"
#include "low_level_renderer_2d.hpp"
#include "../math/vec2f.hpp"

#ifndef SPRITE_FACTORY
class SpriteFactory;
#endif

#ifndef RESOURCE_TEXTURE
class ResourceTexture;
#endif

#ifndef GRAPHICS_SYSTEM
class GraphicsSystem;
#endif

#ifndef SPRITE
#define SPRITE

class Sprite : public GraphicsComponent
{

	friend class Entity;
	friend class GraphicsSystem;

	friend class SpriteFactory;

	SpriteFactory* myFactory;

	ResourceTexture* resourceTexture;

public:

	Sprite(SpriteFactory* factory)
	:GraphicsComponent(),
	myFactory(factory){}

	void update(unsigned int delta){}
	void draw()const;

	bool isReady()const;
	bool isLoaded()const;

	void becomeReady()const;

	~Sprite();

	void destroyDispatcher();

};

#endif
