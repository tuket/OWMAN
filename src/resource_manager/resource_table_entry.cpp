#include "resource_table_entry.hpp"

unsigned int ResourceTableEntry::getCount()const
{
	return count;
}

void ResourceTableEntry::setCount(unsigned int count)
{
	this->count = count;
}

void ResourceTableEntry::incCount()
{
	count++;
}

void ResourceTableEntry::decCount()
{
	count--;
}

Resource* ResourceTableEntry::getPointer()const
{
	return resource;
}

void ResourceTableEntry::setPointer(Resource* resource)
{
	this->resource = resource;
}
