#include "resource_text_factory.hpp"
#include <fstream>

using namespace std;

ResourceText* ResourceTextFactory::createResource(string name)
{
	
	fstream fs;
	fs.open(name.c_str(), fstream::in);
	fs.seekg(0, fs.end);
	int length = fs.tellg();
	char* buffer = new char[length+1];
	fs.read(buffer, length);
	buffer[length] = '\0';
	fs.close();
	
	ResourceText *res = new ResourceText;
	res->text = string(buffer);
	res->name = name;
	res->status = Resource::Status::UNKNOWN;
	
	delete[] buffer;
	
	return res;
	
}

void ResourceTextFactory::destroyResource(ResourceText* resource)
{
	
	delete resource;
	
}

void ResourceTextFactory::destroyResource(Resource* resource)
{
	
	delete resource;
	
}
