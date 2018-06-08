#include "resource_text.hpp"
#include <fstream>
#include <iostream>

using namespace std;

ResourceText::ResourceText(const string& name)
:
    Resource(name)
{
}

std::string ResourceText::getText()const
{
	return text;
}

void ResourceText::load()
{

    status = Status::LOADING;

	fstream fs;
	fs.open(name.c_str(), fstream::in);
	fs.seekg(0, fs.end);
	int length = fs.tellg();
	fs.seekg(0, fs.beg);
	char* buffer = new char[length+1];
	fs.read(buffer, length);
	buffer[length] = '\0';
	fs.close();

	text = string(buffer);
	status = Resource::Status::LOADED;

	delete[] buffer;

}

void ResourceText::free()
{

	text = "";
	status = Resource::Status::STORED;

}

/*
void ResourceText::destroyDispatcher()
{
    myFactory->destroyResource(this);
}
*/
