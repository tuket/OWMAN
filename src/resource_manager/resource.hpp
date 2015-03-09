#include <string>

#ifndef RESOURCE
#define RESOURCE

class Resource
{
	
protected:

	std::string name;
	
	Resource(){}
	
public:
	
	std::string getName()const;
	void setName(std::string name);
	
};

#endif
