#ifndef ICLOUD_PROVIDER_MANAGER_H
#define ICLOUD_PROVIDER_MANAGER_H

#include "IObject.h"

class ICloudProviderManager : public IObject{
public:
    ICloudProviderManager(std::string key) : IObject(key){}
private:
    
};

#endif