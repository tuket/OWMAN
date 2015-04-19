#include "renderer/graphics_system.hpp"
#include "entity_factory.hpp"
#include "world_window.hpp"
#include "world_streamer.hpp"
#include "IO/event_handler.hpp"

#ifndef ENGINE
#define ENGINE

class Engine
{
	
	WorldWindow worldGrid;
	
	EntityFactory entityFactory;
	
	// Systems
	GraphicsSystem graphicsSystem;
	
	WorldStreamer worldStreamer;
	EventHandler eventHandler;
	
public:
	
	Engine(std::string worldFolder);
	
	void init();
	
	GraphicsSystem* getGraphicsSystem();
	
	void mainLoop();
	
};

#endif
