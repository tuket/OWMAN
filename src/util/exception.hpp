#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>
#include <string>

class Exception : public std::exception
{

    std::string msg;

public:

    Exception(const std::string& msg)
    {
        this->msg = msg;
    }

    std::string str() const
    {
        return msg;
    }
};

#endif // EXCEPTION_HPP
