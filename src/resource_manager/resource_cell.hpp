#include "resource.hpp"
#include "../dependencies/rapidxml/rapidxml.hpp"

#ifndef RESOURCE_CELL
#define RESOURCE_CELL

class ResourceCell
{

    friend class ResourceTextFactory;
	friend class ResourceManager;
	char* text;
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<> *node;

protected:

	void load();
	void free();

public:

	ResourceCell();

	rapidxml::xml_node<>* getNode();

	~ResourceCell(){}

};

#endif
