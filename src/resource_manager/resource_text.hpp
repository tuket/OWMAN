#include "resource.hpp"

#ifndef RESOURCE_TEXT
#define RESOURCE_TEXT

#ifndef RESOURCE_TEXT_FACTORY
class ResourceTextFactory;
#endif

#ifndef RESOURCE_MANAGER
class ResourceManager;
#endif

class ResourceText : public Resource
{

	friend class ResourceTextFactory;
	friend class ResourceManager;
	std::string text;

protected:

	void load();
	void free();

public:

	ResourceText();

	std::string getText()const;

	~ResourceText(){}

};

#endif
