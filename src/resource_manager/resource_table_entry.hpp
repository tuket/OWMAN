#include "resource.hpp"

#ifndef RESOURCE_TABLE_ENTRY
#define RESOURCE_TABLE_ENTRY

#ifndef RESOURCE_TABLE
class ResourceTable;
#endif

class ResourceTableEntry
{
	
	friend class ResourceTable;
	
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
