#ifndef RESOURCE_TABLE_ENTRY
#define RESOURCE_TABLE_ENTRY

#include "resource.hpp"

class ResourceTable;

class ResourceTableEntry
{

	friend class ResourceTable;

public:

	ResourceTableEntry(){}

private:

	ResourceTableEntry(Resource* resource);

	unsigned int count;
	Resource* resource;

	unsigned int getCount()const;

	void setCount(unsigned int count);
	void incCount();
	void decCount();

	Resource* getPointer()const;
	void setPointer(Resource* resource);

};

#endif
