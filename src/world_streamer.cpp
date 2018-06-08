#include "world_streamer.hpp"
#include <rapidxml.hpp>
#include "util/file_to_string.hpp"
#include "math/vec2i.hpp"
#include "resource_manager/resource_manager.hpp"
#include "renderer/graphics_component.hpp"
#include "entity_factory.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <typeinfo>
#include <regex>
#include <cmath>

using namespace std;
using namespace rapidxml;

// helper
/** \brief returns whether a given string is the name of a cell file
 * \param the name of the file
 * \return whether it is a cell file
 *
 */
bool isCellFile(string fileName)
{

    string minSample = "cell_0_0.xml";
    if( fileName.size() < minSample.size() ) return false;

    int slash = 0;
    for(int i = fileName.size(); i>=0; i--)
    if( fileName[i] == '/' )
    {
        slash = i;
        slash++;
        break;
    }
    int i = slash;

    string s1 = "cell_";

    for(unsigned int j=0; j<s1.size(); j++, i++)
    {
        if( s1[j] != fileName[i] ) return false;
    }

    if( fileName[i] == '0' )
    {

        if( fileName[i+1] != '_' ) return false;
        i += 2;

    }
    else
    {

        if( !('1' <= fileName[i] && fileName[i] <= '9') ) return false;
        i++;

        while( '0' <= fileName[i] && fileName[i] <= '9' )
        {
            i++;
        }

        if( fileName[i] != '_' ) return false;

        i++;

    }

    if( fileName[i] == '0' )
    {

        if( fileName[i+1] != '.' ) return false;
        i += 2;

    }
    else
    {

        if( !('1' <= fileName[i] && fileName[i] <= '9') ) return false;
        i++;

        while( '0' <= fileName[i] && fileName[i] <= '9' )
        {
            i++;
        }

        if( fileName[i] != '.' ) return false;

        i++;

    }

    string s2 = "xml";

    for(unsigned int j=0; j<s2.size(); j++, i++)
    {
        if( fileName[i] != s2[j] ) return false;
    }

    return true;

}

// helper
/** \brief returns the cell position from the file name
 * \param the name of the file
 * \return the position of the cell
 * For example "cell_3_4.xml" -> Vec2i(3, 4). <br>
 * Assumes the the file name is valid (i.e. has been
 * checked with isCellFile()
 */
Vec2i getCell(string fileName)
{

    int slash = 0;
    for(int i = fileName.size(); i>=0; i--)
    if( fileName[i] == '/' )
    {
        slash = i;
        slash++;
        break;
    }
    int i = slash;

    while( !('0' <= fileName[i] && fileName[i] <= '9')  )
    {
        i++;
    }

    int x = 0;
    while( '0' <= fileName[i] && fileName[i] <= '9' )
    {
        x *= 10;
        x += (int)(fileName[i] - '0');

        i++;
    }

    while( !('0' <= fileName[i] && fileName[i] <= '9')  )
    {
        i++;
    }

    int y = 0;
    while( '0' <= fileName[i] && fileName[i] <= '9' )
    {
        y *= 10;
        y += (int)(fileName[i] - '0');

        i++;
    }

    return Vec2i(x, y);

}



// helper
/** \brief modifies an xml_document to represent the given cell
 *
 * \param the document to be modified
 * \param the cell
 */
void cellToXmlDocument(xml_document<>* doc, const WorldCell& wc, float cellSize)
{

    doc->remove_all_attributes();
    doc->remove_all_nodes();
    doc->clear();

    const char* str_cell = doc->allocate_string("cell");
    if( wc.size() == 0 )
    {
        const char* str_space = doc->allocate_string(" ");
        xml_node<>* root = doc->allocate_node(node_element, str_cell, str_space);
        doc->append_node( root );
        return;
    }

    xml_node<>* root = doc->allocate_node(node_element, str_cell);
    doc->append_node( root );

    xml_node<>* node_ent;
    for( unsigned int i=0; i<wc.size(); i++ )
    {

        node_ent = wc[i]->createXmlNode(doc, cellSize);
        root->append_node( node_ent );

    }

}


WorldStreamer::WorldStreamer
(
	string worldFolder,
	EntityFactory* entityFactory,
	float cellSize,
    unsigned int windowSize
)
:
cellSize(cellSize),
worldWindow(windowSize)
{

	this->worldFolder = worldFolder;
	this->entityFactory = entityFactory;

    fstream fs;
    fs.open("world_folder/world_file.txt", ios::in);

    int x, y;
    while(fs >> x)
    {
        fs >> y;
        Vec2i cell(x, y);
        availableCells.insert( cell );
    }

}

void WorldStreamer::init(const Vec2i& cell, const Vec2f& offset)
{

    windowPos = cell;

    for
    (
        int y = cell.y - worldWindow.windowSize;
        y <= (int)(cell.y + worldWindow.windowSize);
        y++
    )
    for
    (
        int x = cell.x - worldWindow.windowSize;
        x <= (int)(cell.x + worldWindow.windowSize);
        x++
    )
    if( availableCells.find( Vec2i(x, y) ) != availableCells.end() )
    {

        stringstream ss;
        ss << worldFolder
        << "/"
        << "cell_"
        << x
        << "_"
        << y
        << ".xml";

        string fileName = ss.str();
        // cout << fileName << endl;

        ResourceManager* resMan = ResourceManager::getSingleton();
        ResourceCell* cellResource = resMan->obtain<ResourceCell>(fileName);
        loadingCellResources[ Vec2i(x, y) ] = cellResource;

    }

}

void WorldStreamer::update(const Vec2f& position, MainCharacter* mainCharacter)
{

    // check if the entities have changed of cell

    for
    (
        map<Vec2i, WorldCell>::iterator it = worldWindow.cells.begin();
        it != worldWindow.cells.end();
        ++it
    )
    {

        WorldCell& wc = it->second;
        Vec2i currentCell = it->first;

        for(unsigned int i=0; i<wc.size(); i++)
        {

            Vec2f pos = wc[i]->getPosition();
            Vec2i goodCell = Vec2i( floor(pos.x/cellSize), floor(pos.y/cellSize) );
            goodCell += windowPos;

            // the entity is not in the cell it should be
            // --> change of cell
            if( currentCell != goodCell )
            {

                map<Vec2i, WorldCell>::iterator it2;
                it2 = worldWindow.cells.find( goodCell );
                // the cell is loaded -> just append
                if( it2 != worldWindow.cells.end() )
                {
                    Entity* ent = wc[i];

                    wc[i] = wc.back();
                    wc.pop_back();

                    it2->second.push_back(ent);

                    i--;

                }

                // the cell is not loaded, what to do?
                // --> load it
                else if( availableCells.find(goodCell) != availableCells.end() )
                {

                    stringstream ss;
                    ss << worldFolder
                    << "/"
                    << "cell_"
                    << goodCell.x
                    << "_"
                    << goodCell.y
                    << ".xml";

                    string fileName = ss.str();

                    ResourceManager* resMan = ResourceManager::getSingleton();
                    ResourceCell* cellResource = resMan->obtain<ResourceCell>(fileName);
                    loadingCellResources[ goodCell ] = cellResource;

                }

            }

        }

    }

    // check if the main character changed of cell

    Vec2i nextCell = windowPos;
    Vec2f pos = position;

    while( pos.x < 0.0f )
    {
        nextCell.x--;
        pos.x += cellSize;
    }
    while( pos.x > cellSize )
    {
        nextCell.x++;
        pos.x -= cellSize;
    }

    while( pos.y < 0.0 )
    {
        nextCell.y--;
        pos.y += cellSize;
    }
    while( pos.y > cellSize )
    {
        nextCell.y++;
        pos.y -= cellSize;
    }

    // changed of cell
    // must change the coordinate system origin
    if( nextCell != windowPos )
    {

        // update window pos
        windowPos = nextCell;

        // update entities pos
        vector<Entity*> ents = getEntities();
        for(unsigned int i=0; i<ents.size(); i++)
        {
            Vec2f pPos = ents[i]->getPosition();
            ents[i]->setPosition( pPos + (pos-position) );
        }
        mainCharacter->setPosition( pos );

        // delete old cells
        for
        (
            map<Vec2i, WorldCell>::const_iterator it = worldWindow.cells.begin();
            it != worldWindow.cells.end();
            // ++it
        )
        {

            if
            (
                (int)(nextCell.x - worldWindow.windowSize) > it->first.x ||
                it->first.x > (int)(nextCell.x + worldWindow.windowSize) ||
                (int)(nextCell.y - worldWindow.windowSize) > it->first.y ||
                it->first.y > (int)(nextCell.y + worldWindow.windowSize)
            )
            {

                // update XML document
                const WorldCell& wc = it->second;
                xml_document<>* doc = loadedCellResources[ it->first ]->getDocument();
                cellToXmlDocument( doc, wc, cellSize );

                // release all the entities of the cell
                for
                (
                    WorldCell::const_iterator it = wc.begin();
                    it != wc.end();
                    ++it
                )
                {
                    entityFactory->destroyEntity( *it );
                }

                ResourceManager* resMan = ResourceManager::getSingleton();
                resMan->release( loadedCellResources[ it->first ] );
                loadedCellResources.erase(it->first);

                auto nextIt = it;
                nextIt++;
                worldWindow.cells.erase(it);
                it = nextIt;



                continue;


            }

            it++;

        }

        // insert new cells
        for
        (
            int y = (int)(nextCell.y - worldWindow.windowSize);
            y <= (int)(nextCell.y + worldWindow.windowSize);
            y++
        )
        for
        (
            int x = (int)(nextCell.x - worldWindow.windowSize);
            x <= (int)(nextCell.x + worldWindow.windowSize);
            x++
        )
        if
        (
            worldWindow.cells.find( Vec2i(x, y) ) == worldWindow.cells.end() &&     // no
            availableCells.find( Vec2i(x, y) ) != availableCells.end() &&           // yes
            loadingCellResources.find( Vec2i(x, y) ) == loadingCellResources.end()  // no
        )
        {

            stringstream ss;
            ss << worldFolder
            << "/"
            << "cell_"
            << x
            << "_"
            << y
            << ".xml";

            string fileName = ss.str();

            ResourceManager* resMan = ResourceManager::getSingleton();
            ResourceCell* cellResource = resMan->obtain<ResourceCell>(fileName);
            loadingCellResources[ Vec2i(x, y) ] = cellResource;

        }


    }

    // parse loaded cell resources
    map<Vec2i, ResourceCell*>::iterator it;
    for
    (
        it = loadingCellResources.begin();
        it != loadingCellResources.end();
        //++it
    )
    {

        ResourceCell* res = it->second;
        // the resource file is finally loaded
        if
        (
            res->getStatus() == Resource::Status::LOADED // finally loaded
        )
        {

            /*
            // loaded late.
            // finally loaded but it is not needed anymore,
            // so release resource without parsing
            if
            (
                (int)(windowPos.x - worldWindow.windowSize) > it->first.x ||
                it->first.x > (int)(windowPos.x + worldWindow.windowSize )||
                (int)(windowPos.y - worldWindow.windowSize) > it->first.y ||
                it->first.y > (int)(windowPos.y + worldWindow.windowSize)
            )
            {

                ResourceManager* resMan = ResourceManager::getSingleton();
                resMan->releaseCell( res );
                loadingCellResources.erase( it );
                continue;

            }
            */

            WorldCell wc;

            xml_node<> *node = res->getNode();

            node = node->first_node("entity");

            while( node != 0 )
            {

                Entity* ent = entityFactory->createEntity(node, it->first-windowPos);

                wc.push_back( ent );
                node = node->next_sibling();

            }


            Vec2i cell = it->first;
            worldWindow.cells[ cell ] = wc;

            auto nextIt = it;
            nextIt++;
            loadedCellResources[ cell ] = it->second;
            loadingCellResources.erase( it );
            it = nextIt;


            continue;

        }
        it++;
    }

}

Vec2i WorldStreamer::getWindowPosition()const
{
	return windowPos;
}

float WorldStreamer::getCellSize()const
{
    return cellSize;
}

vector<Entity*> WorldStreamer::getEntities()const
{

    int len = 0;

    for
    (
        map<Vec2i, WorldCell>::const_iterator it = worldWindow.cells.begin();
        it != worldWindow.cells.end();
        ++it
    )
    {
        len += it->second.size();
    }

    vector<Entity*> ents;
    ents.reserve(len);

    for
    (
        map<Vec2i, WorldCell>::const_iterator it = worldWindow.cells.begin();
        it != worldWindow.cells.end();
        ++it
    )
    {
        const WorldCell& wc = it->second;

        for(unsigned int i=0; i<wc.size(); i++)
        {
            ents.push_back(wc[i]);
        }

    }

    return ents;

}

void WorldStreamer::end()
{

    for
    (
        map<Vec2i, WorldCell>::const_iterator it = worldWindow.cells.begin();
        it != worldWindow.cells.end();
        // ++it
    )
    {



        // update XML document
        const WorldCell& wc = it->second;
        xml_document<>* doc = loadedCellResources[ it->first ]->getDocument();
        cellToXmlDocument( doc, wc, cellSize );

        // release all the entities of the cell
        for
        (
            WorldCell::const_iterator it = wc.begin();
            it != wc.end();
            ++it
        )
        {
            entityFactory->destroyEntity( *it );
        }

        ResourceManager* resMan = ResourceManager::getSingleton();
        resMan->release( loadedCellResources[ it->first ] );
        loadedCellResources.erase(it->first);

        auto nextIt = it;
        nextIt++;
        worldWindow.cells.erase(it);
        it = nextIt;

    }


}
