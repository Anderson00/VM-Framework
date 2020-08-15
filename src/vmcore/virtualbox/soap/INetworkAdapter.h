#ifndef INETWORK_ADAPTER_H
#define INETWORK_ADAPTER_H

#include "IObject.h"

class INetworkAdapter : public IObject {
public:
    INetworkAdapter(std::string key) : IObject(key){}
private:
};

#endif