#ifndef IGRAPHICS_ADAPTER_H
#define IGRAPHICS_ADAPTER_H

#include "IObject.h"

class IGraphicsAdapter : public IObject {
public:
    IGraphicsAdapter(std::string key) : IObject(key){}
private:
};

#endif