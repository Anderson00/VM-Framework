#ifndef IDHCP_SERVER_H
#define IDHCP_SERVER_H

#include "IObject.h"

class IDHCPServer : public IObject{
public:
    IDHCPServer(std::string) : IObject(key) {}
private:

};

#endif