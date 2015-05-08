#include "renderer/graphics_system.hpp"
#include "entity_factory.hpp"
#include "world_window.hpp"
#include "world_streamer.hpp"
#include "test_world_streamer.hpp"
#include "IO/event_handler.hpp"

#ifndef ENGINE
#define ENGINE

class Engine
{

	WorldWindow worldGrid;

	EntityFactory entityFactory;

	// Systems
	GraphicsSystem* graphicsSystem;

	IWorldStreamer* worldStreamer;
	MainCharacter* mainCharacter;

	EventHandler eventHandler;

	bool end;
	int fps;

public:

	Engine(std::string initFile, std::string worldFolder);

	void init();

	void mainLoop();

    GraphicsSystem* getGraphicsSystem();
	MainCharacter* getMainCharacter();

	float getCellSize()const;

	~Engine();

};

#endif
