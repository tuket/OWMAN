#include "renderer/graphics_system.hpp"
#include "physics/physics_system.hpp"
#include "entity_factory.hpp"
#include "world_window.hpp"
#include "world_streamer.hpp"
#include "test_world_streamer.hpp"
#include "IO/event_handler.hpp"

#ifndef ENGINE
#define ENGINE

/** \brief encapsulates all systems
 * Has the main loop. Contains all systems like graphics system
 * and physics system
 */
class Engine
{

	WorldWindow worldGrid;

	EntityFactory entityFactory;

	// Systems
	GraphicsSystem* graphicsSystem;
	PhysicsSystem* physicsSystem;

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
    PhysicsSystem* getPhysicsSystem();

	MainCharacter* getMainCharacter();

	float getCellSize()const;

	void endGame();

	~Engine();

};

#endif
