#include "world_window.hpp"
#include "world_cell.hpp"

using namespace std;

WorldWindow::WorldWindow()
{

}

WorldWindow::WorldWindow(unsigned int windowSize)
{

	this->windowSize = windowSize;

}

vector<Entity*> WorldWindow::getEntities()const
{

    int len = 0;

    for
    (
        map<Vec2i, WorldCell>::const_iterator it = cells.begin();
        it != cells.end();
        ++it
    )
    {

        len += it->second.size();

    }

    vector<Entity*> res;
    res.reserve(len);

    for
    (
        map<Vec2i, WorldCell>::const_iterator it = cells.begin();
        it != cells.end();
        ++it
    )
    {

        const WorldCell& wc = it->second;

        for(unsigned int i=0; i<wc.size(); i++)
        {
            res.push_back( wc[i] );
        }

    }

    return res;

}

WorldWindow::~WorldWindow()
{

}
