#include "resource.hpp"

Resource::Resource()
{
	status = Status::STORED;
}

std::string Resource::getName()const
{
	return name;
}

void Resource::setName(std::string name)
{
	this->name = name;
}

Resource::Status Resource::getStatus()const
{
	return status;
}
