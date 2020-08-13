#ifndef LOGON_EXCEPTION_H
#define LOGON_EXCEPTION_H

#include <exception>
#include <stdexcept>

class logon_exception : std::runtime_error{
public:
    logon_exception(const std::string& what) : std::runtime_error(what) {}
};


#endif