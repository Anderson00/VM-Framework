#ifndef IPROGRESS_H
#define IPROGRESS_H

#include "IObject.h"

class IProgress : public IObject{
public:
    IProgress(std::string key) : IObject(key) {}
private:
    
};

#endif