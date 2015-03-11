#include "resource_table.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

unsigned int ResourceTable::getCount(std::string name)const
{

	map< string, ResourceTableEntry >::const_iterator it;
	it = table.find(name);
	
	if( it == table.end() )
	{
		return 0;
	}
	else
	{
		return it->second.count;
	}

}

Resource* ResourceTable::getResource(std::string name)
{
	
	map< string, ResourceTableEntry >::iterator it;
	it = table.find(name);
	
	Resource* res;
	// not found
	if( it == table.end() )
	{
		
		res = (Resource*)0;
		
	}
	
	// found
	else
	{
		
		res = it->second.resource;
		
	}
	
	return res;
	
}

void ResourceTable::addEntry(std::string name, Resource* resource)
{
	
	ResourceTableEntry entry(resource);
	table[name] = entry;
	
}

void ResourceTable::removeEntry(std::string name)
{
	
	table.erase(name);
	
}

void ResourceTable::incEntry(string name)
{
	
	map< string, ResourceTableEntry >::iterator it;
	it = table.find(name);
	
	// not found
	if( it == table.end() )
	{
		
		cerr << "fatal error" << endl;
		exit(1);
		
	}
	
	// found
	else
	{
		
		unsigned int &count = it->second.count;
		count++;

	}
	
}

void ResourceTable::decEntry(string name)
{
	
	map< string, ResourceTableEntry >::iterator it;
	it = table.find(name);
	
	// not found
	if( it == table.end() )
	{
		
		cerr << "fatal error" << endl;
		exit(1);
		
	}
	
	// found
	else
	{
		
		unsigned int &count = it->second.count;
		count--;

	}
	
}

