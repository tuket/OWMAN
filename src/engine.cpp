#include "engine.hpp"

Engine::Engine(std::string worldFolder)
:
worldStreamer
(
	"world_folder",
	&entityFactory
)
{
	
	entityFactory = EntityFactory(this);
	
}

void Engine::init()
{
	
}

GraphicsSystem* Engine::getGraphicsSystem()
{
	return graphicsSystem:
}

void Engine::mainLoop()
{
	
	eventHandler.poll();
	
	// (update physics)
	
	// update world streamer
	worldStreamer.update();
	
	// update graphics
	graphicsSystem.update()
	
	// draw
	graphicsSystem.clear();
	graphicsSystem.draw();
	graphicsSystem.swap();
	
}
