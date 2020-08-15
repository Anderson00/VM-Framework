#ifndef ISNAPSHOT_H
#define ISNAPSHOT_H

#include "IObject.h"

class ISnapshot : public IObject{
public:
    ISnapshot(std::string key) : IObject(key) {}
private:
};

#endif