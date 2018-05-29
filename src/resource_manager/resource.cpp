#include "resource.hpp"

using namespace std;

Resource::Resource(const string& name)
:
    name(name)
{
	status = Status::STORED;
}

string Resource::getName()const
{
	return name;
}

void Resource::setName(string name)
{
	this->name = name;
}

Resource::Status Resource::getStatus()const
{
	return status;
}
