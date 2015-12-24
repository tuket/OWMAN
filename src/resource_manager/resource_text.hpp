#ifndef RESOURCE_TEXT
#define RESOURCE_TEXT

#include "resource.hpp"

class ResourceTextFactory;
class ResourceManager;

class ResourceText : public Resource
{

	friend class ResourceTextFactory;
	friend class ResourceManager;

	ResourceTextFactory* myFactory;
	std::string text;

protected:

	void load();
	void free();

public:

	ResourceText(const std::string& name);

	std::string getText()const;

	//void destroyDispatcher();

	~ResourceText(){}

};

#endif
