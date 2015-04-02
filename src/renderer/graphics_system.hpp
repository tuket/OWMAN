#include "low_level_renderer_2d.hpp"
#include "sprite_factory.hpp"
#include <string>
#include <set>
#include "camera.hpp"

#ifndef ENGINE
class Engine;
#endif

#ifndef GRAPHICS_SYSTEM
#define GRAPHICS_SYSTEM

class GraphicsSystem
{
	
	Engine* myEngine;
	
	Camera camera;
	LowLevelRenderer2D renderer;
	
	std::set<GraphicsComponent*> components;
	
	// Factories
	SpriteFactory spriteFactory;
	
public:
	
	GraphicsSystem
	(
		std::string windowTitle,
		unsigned int width, unsigned int height,
		bool fullScreen
	);
	
	void update(unsigned int delta);
	void draw();
	void swap();
	
	Sprite* createSprite(std::string fileName, const Vec2f& scale);
	void destroySprite(Sprite* sprite);
	
	Engine* getEngine();
	LowLevelRenderer2D* getRenderer();
	Camera* getCamera();
	
};

#endif
