#include "resource_table_entry.hpp"
#include "resource_factory.hpp"
#include "resource_text_factory.hpp"
#include <map>
#include <string>

#ifndef RESOURCE_TABLE
#define RESOURCE_TABLE

class ResourceTable
{
	
	std::map< std::string, ResourceTableEntry > table;
	
	// Factories
	ResourceTextFactory resourceTextFactory;
	
public:
	
	const Resource* getResource(std::string name, ResourceFactory* factory);
	const ResourceText* getResourceText(std::string name);
	
	void release(const ResourceText* resource);
	void release(const Resource* resource, ResourceFactory* factory);
	
	
};

#endif
