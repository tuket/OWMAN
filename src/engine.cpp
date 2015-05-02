#include "engine.hpp"
#include "resource_manager/resource_manager.hpp"
#include "dependencies/rapidxml/rapidxml.hpp"
#include "util/file_to_string.hpp"
#include <string>
#include <cstdio>
#include <iostream>
#include <SDL2/SDL.h>


using namespace std;
using namespace rapidxml;

Engine::Engine(std::string initFile, std::string worldFolder)
{

    end = false;
    fps = 60;

    worldStreamer = new TestWorldStreamer;
    worldStreamer->setEntityFactory(&entityFactory);

	entityFactory = EntityFactory(this);

	char* initFileText = fileToString( initFile.c_str() );

	// check errors
	if( initFileText == 0 )
	{

		cerr << "Error loading initialization file: "
		<< initFile << endl;

		graphicsSystem = new GraphicsSystem( string("OWMAN"), 400, 400, false );

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

	graphicsSystem = new GraphicsSystem( title, xResolution, yResolution, fullscreen );
	Camera* camera = graphicsSystem->getCamera();
	camera->setWidth(xResolution/2);
	camera->setHeight(yResolution/2
);

}

void Engine::init()
{

    SDL_Init(SDL_INIT_TIMER);

    ResourceManager::init();
    ResourceManager* resourceManager = ResourceManager::getSingleton();
    resourceManager->launch();

    worldStreamer->init(Vec2i(0,0), Vec2f(0,0));

}

GraphicsSystem* Engine::getGraphicsSystem()
{
	return graphicsSystem;
}

void Engine::mainLoop()
{

    while( !end )
    {

        unsigned int beginTicks = SDL_GetTicks();

        eventHandler.poll();

        // (update physics)

        // update world streamer
        worldStreamer->update( Vec2f(0, 0) );

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
                //entity->getPhysicsComponent() != 0
                false
            )
            {
                // whatever
            }
        }

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

Engine::~Engine()
{
    if( graphicsSystem ) delete graphicsSystem;
    if( worldStreamer) delete worldStreamer;
    if( mainCharacter) delete mainCharacter;
}
