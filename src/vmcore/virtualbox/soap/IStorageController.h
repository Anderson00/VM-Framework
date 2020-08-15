#ifndef ISTORAGE_CONTROLLER_H
#define ISTORAGE_CONTROLLER_H

#include "IObject.h"

class IStorageController : public IObject {
public:
    IStorageController(std::string key) : IObject(key){}
private:
};


#endif