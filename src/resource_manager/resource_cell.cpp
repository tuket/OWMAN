#include "resource_cell.hpp"
#include "../dependencies/rapidxml/rapidxml_print.hpp"
#include <iostream>
#include <fstream>

using namespace rapidxml;
using namespace std;

ResourceCell::ResourceCell(const string& name)
:
    Resource(name)
{
}

void ResourceCell::load()
{

    status = Status::LOADING;

    fstream fs;
	fs.open(name.c_str(), fstream::in);
	fs.seekg(0, fs.end);
	int length = fs.tellg();
	fs.seekg(0, fs.beg);
	text = new char[length+1];
	fs.read(text, length);
	text[length] = '\0';
	fs.close();

	doc.parse<0>(text);

    node = doc.first_node("cell");

    if( node == 0 )
    {
        cerr << "error: file " << name << "does not have a cell node" << endl;
    }

	status = Resource::Status::LOADED;

}

void ResourceCell::free()
{

    status = Resource::Status::SAVING;

    fstream fs;
	fs.open(name.c_str(), fstream::out);

    fs << doc << endl;

    delete[] text;

    status = Resource::Status::STORED;

}

rapidxml::xml_node<>* ResourceCell::getNode()
{
    return node;
}

rapidxml::xml_document<>* ResourceCell::getDocument()
{
    return &doc;
}

