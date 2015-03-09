#include "resource.hpp"

std::string Resource::getName()const
{
	return name;
}

void Resource::setName(std::string name)
{
	this->name = name;
}
