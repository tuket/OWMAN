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
	
public:
	
	unsigned int getCount(std::string name)const;
	
	void addEntry(std::string name, Resource* resource);
	void removeEntry(std::string name);
	
	void incEntry(std::string name);
	void decEntry(std::string name);
	
	Resource* getResource(std::string name);
	
};

#endif
