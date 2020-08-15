#ifndef IVIRTUAL_SYSTEM_DESCRIPTION_H
#define IVIRTUAL_SYSTEM_DESCRIPTION_H

#include "IObject.h"

class IVirtualSystemDescription : public IObject{
public:
    IVirtualSystemDescription(std::string key) : IObject(key){}
private:
};

#endif