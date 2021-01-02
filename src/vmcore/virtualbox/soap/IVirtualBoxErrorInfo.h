#ifndef IVIRTUAL_BOX_ERROR_INFO_H
#define IVIRTUAL_BOX_ERROR_INFO_H

#include "IObject.h"

class IVirtualBoxErrorInfo : public IObject
{
private:

public:
    IVirtualBoxErrorInfo(std::string key) : IObject(key){}
};

#endif