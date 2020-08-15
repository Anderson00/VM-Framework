#ifndef IPARALLEL_PORT_H
#define IPARALLEL_PORT_H

#include "IObject.h"

class IParallelPort : public IObject {
public:
    IParallelPort(std::string key) : IObject(key){}
private:
};

#endif