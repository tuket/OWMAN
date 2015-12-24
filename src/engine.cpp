#include "engine.hpp"
#include "resource_manager/resource_manager.hpp"
#include "dependencies/rapidxml/rapidxml.hpp"
#include "util/file_to_string.hpp"
#include "physics/physics_component.hpp"
#include "renderer/graphics_component.hpp"
#include <string>
#include <sstream>
#include <cstdio>
#include <iostream>
#include <SDL2/SDL.h>


using namespace std;
using namespace rapidxml;

Engine::Engine(std::string initFile, std::string worldFolder)
:
eventHandler( this )
{

    end = false;
    fps = 60;

	char* initFileText = fileToString( initFile.c_str() );

	// check errors
	if( initFileText == 0 )
	{

		cerr << "Error loading initialization file: "
		<< initFile << endl;

		return;

	}

	xml_document<> doc;
	doc.parse<0>( initFileText );

	xml_node<>* node;

	node = doc.first_node("window_title");
	string title = node->value();

	node = doc.first_node("fullscreen");
	string fullscreenString = node->value();
	bool fullscreen =
	(
		(fullscreenString == string("true")) ?
		true :
		false
	);


	node = doc.first_node("x_resolution");
	int xResolution = atof( node->value() );


	node = doc.first_node("y_resolution");
	int yResolution = atof( node->value() );

	node = doc.first_node("cell_size");
	float cellSize = atof( node->value() );

	node = doc.first_node("window_size");
	int windowSize = atoi( node->value() );

	worldStreamer = new WorldStreamer(worldFolder, &entityFactory, cellSize, windowSize);

	entityFactory = EntityFactory(this);

    // init systems
	graphicsSystem = new GraphicsSystem( title, xResolution, yResolution, fullscreen );
	Camera* camera = graphicsSystem->getCamera();
	camera->setWidth(xResolution/2);
	camera->setHeight(yResolution/2);

	physicsSystem = new PhysicsSystem();

	delete initFileText;

    // main character

    stringstream ss;
    ss << worldFolder << "/" << "main_character.xml";
    string mcFileName = ss.str();

    char* mcFileText = fileToString(mcFileName.c_str());

    assert(mcFileText && "main_character.xml not found");

    xml_document<> mcDoc;
    mcDoc.parse<0>( mcFileText );

    node = mcDoc.first_node("main_character");

    mainCharacter = entityFactory.createMainCharacter(node);


    delete mcFileText;

}

void Engine::init()
{

    SDL_Init(SDL_INIT_TIMER);

    ResourceManager* resourceManager = ResourceManager::getSingleton();
    resourceManager->launch();

    if( !mainCharacter )
    {
        //worldStreamer->init(mainCharacter->getCell(), mainCharacter->getPosition());
    }
    else
    {
        worldStreamer->init
        (
            mainCharacter->getCell(),
            mainCharacter->getPosition()
        );
    }


}

void Engine::mainLoop()
{

    while( !end )
    {

        unsigned int beginTicks = SDL_GetTicks();

        eventHandler.poll();

        // update physics
        physicsSystem->update( 1000/fps );

        // update world streamer
        worldStreamer->update( mainCharacter->getPosition(), mainCharacter );

        // get list of entities
        vector<Entity*> entities = worldStreamer->getEntities();

        // move graphics components to match physics components
        // (update position of graphics components)
        for(unsigned int i=0; i<entities.size(); i++)
        {
            Entity* entity = entities[i];
            if
            (
                entity->getGraphicsComponent() != 0 &&
                entity->getPhysicsComponent() != 0
            )
            {
                GraphicsComponent* gc = entity->getGraphicsComponent();
                PhysicsComponent* pc = entity->getPhysicsComponent();
                gc->setPosition( pc->getPosition() );
            }
        }

        GraphicsComponent* gc = mainCharacter->getGraphicsComponent();
        PhysicsComponent* pc = mainCharacter->getPhysicsComponent();
        gc->setPosition( pc->getPosition() );


        // follow main character with the camera
        graphicsSystem->getCamera()->setPosition( -mainCharacter->getPosition() );

        // update graphics
        graphicsSystem->update(1000/fps);

        // draw
        graphicsSystem->draw();
        graphicsSystem->swap();

        unsigned int endTicks = SDL_GetTicks();
		int sleepTicks = 1000/fps - (endTicks-beginTicks);
		if(sleepTicks > 0)
			SDL_Delay( sleepTicks );

    }

}

GraphicsSystem* Engine::getGraphicsSystem()
{
	return graphicsSystem;
}

PhysicsSystem* Engine::getPhysicsSystem()
{
    return physicsSystem;
}

MainCharacter* Engine::getMainCharacter()
{
    return mainCharacter;
}

float Engine::getCellSize()const
{

    return worldStreamer->getCellSize();

}

void Engine::endGame()
{
    worldStreamer->end();
    graphicsSystem->end();
    end = true;
}

Engine::~Engine()
{
    if( graphicsSystem ) delete graphicsSystem;
    if( worldStreamer) delete worldStreamer;
    if( mainCharacter) delete mainCharacter;
}
