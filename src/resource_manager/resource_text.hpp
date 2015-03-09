#include "resource.hpp"

#ifndef RESOURCE_TEXT
#define RESOURCE_TEXT

#ifndef RESOURCE_TEXT_FACTORY
class ResourceTextFactory;
#endif

class ResourceText : public Resource
{
	
	friend class ResourceTextFactory;
	std::string text;
	
public:
	
	ResourceText(){};
	
	std::string getText()const;
	
};

#endif
