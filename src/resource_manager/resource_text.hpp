#include "resource.hpp"

#ifndef RESOURCE_TEXT_FACTORY
class ResourceTextFactory;
#endif

#ifndef RESOURCE_MANAGER
class ResourceManager;
#endif



#ifndef RESOURCE_TEXT
#define RESOURCE_TEXT

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

	ResourceText();

	std::string getText()const;

	void destroyDispatcher();

	~ResourceText(){}

};

#endif
