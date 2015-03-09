#include <string>

#ifndef RESOURCE
#define RESOURCE

class Resource
{
	
	friend class ResourceManager;
	
public:

	enum class Status
	{
		UNKOWN,
		QUEUED,
		LOADING,
		LOADED
	};
	
protected:

	std::string name;
	Status status;
	
	Resource(){}
	
public:
	
	std::string getName()const;
	void setName(std::string name);
	Resource::Status getStatus()const;
	
	
};

#endif
