#include "resource.hpp"
#include <string>

#ifndef RESOURCE_REQUEST
#define RESOURCE_REQUEST

class ResourceRequest
{

public:

	enum class Type
	{
		OBTAIN,		//< request a handle to a resource
		RELEASE,	//< notifies to release the resource handle 
		STOP		//< stop the resource manager
	};
	
private:
	
	Type type;
	std::string name;
	
public:
	
	ResourceRequest(){}
	ResourceRequest(Type type, std::string name);
	
	ResourceRequest operator=(const ResourceRequest& resourceRequest);
	
	ResourceRequest::Type getType()const;
	std::string getName()const;
	
};

#endif
