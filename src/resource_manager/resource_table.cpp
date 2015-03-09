#include "resource_table.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;


const ResourceText* ResourceTable::getResourceText(std::string name)
{
	
	return (ResourceText*) getResource(name, &resourceTextFactory);
	
}

const Resource* ResourceTable::getResource
(
	std::string name,
	ResourceFactory* factory
)
{
	
	map< string, ResourceTableEntry >::iterator it;
	it = table.find(name);
	
	Resource* res;
	// not found
	if( it == table.end() )
	{
		
		res = factory->createResource( name );
		ResourceTableEntry rte;
		rte.resource = res;
		rte.count = 1;
		
	}
	
	// found
	else
	{
		
		res = it->second.resource;
		
	}
	
	return res;
	
}

// release

void ResourceTable::release(const ResourceText* resource)
{
	
	release(resource, &resourceTextFactory);
	
}

void ResourceTable::release(const Resource* resource, ResourceFactory* factory)
{
	
	string name = resource->getName();
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
		
		// must erase
		if( count == 1 )
		{
			
			table.erase( it );
			factory->destroyResource( it->second.resource );
			
		}
		
		// decrement count
		else
		{
			
			count--;
			
		}
		
		
	}
	
}

