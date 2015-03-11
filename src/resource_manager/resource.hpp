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
		STORED,
		QUEUED,
		LOADING,
		LOADED
	};
	
protected:

	std::string name;
	Status status;
	
	virtual void load() = 0;
	virtual void free() = 0;
	
public:
	
	Resource();
	
	std::string getName()const;
	void setName(std::string name);
	Resource::Status getStatus()const;
	
	virtual ~Resource(){};
	
};

#endif
