#include "resource_request.hpp"

using namespace std;

ResourceRequest::ResourceRequest(Type type, string name)
{
	this->type = type;
	this->name = name;
}

ResourceRequest ResourceRequest::operator=(const ResourceRequest& resourceRequest)
{
	type = resourceRequest.type;
	name = resourceRequest.name;
	return *this;
}

ResourceRequest::Type ResourceRequest::getType()const
{
	return type;
}

std::string ResourceRequest::getName()const
{
	return name;
}
