#include "world_window.hpp"
#include "world_cell.hpp"

WorldWindow::WorldWindow()
{
	table = 0;
}

WorldWindow::WorldWindow(unsigned int windowSize)
{
	
	this->windowSize = windowSize;
	
	table = new WorldCell** [ windowSize*2+1 ];
	table[0] = new WorldCell* [ (windowSize*2+1)*(windowSize*2+1) ];
	for(int i=1; i<windowSize*2+1; i++)
	{
		table[i] = &table[0][ i * (windowSize*2+1) ];
	}
	
	for(int i=0; i<(windowSize*2+1)*(windowSize*2+1); i++)
	{
		table[0][i] = 0;
	}
	
}

WorldCell *& WorldWindow::operator()(int x, int y)
{
	
	return table[y][x];
	
}

WorldWindow::~WorldWindow()
{
	
	if(table != 0)
	{
		
		delete[] table[0];
		delete[] table;
		
	}
	
}
