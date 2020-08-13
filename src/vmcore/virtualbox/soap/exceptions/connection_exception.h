#ifndef CONNECTION_EXCEPTION_H
#define CONNECTION_EXCEPTION_H

#include <exception>
#include <stdexcept>

class connection_exception : public std::runtime_error {
public:
    connection_exception(const std::string& what) : runtime_error(what) {}
};

#endif