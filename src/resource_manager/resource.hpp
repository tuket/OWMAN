#include <string>

#ifndef RESOURCE
#define RESOURCE

/**
 * \brief Resouce data class
 * This class hold the data for different types of
 * resource. In order to create a new type of resource
 * just extend from this class
 */

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
		LOADED,
		READY
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
