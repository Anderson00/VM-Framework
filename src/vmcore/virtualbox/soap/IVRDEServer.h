#ifndef IVRDE_SERVER_H
#define IVRDE_SERVER_H

#include "IObject.h"

class IVRDEServer : public IObject{
public:
    IVRDEServer(std::string key) : IObject(key){}
private:
};

#endif