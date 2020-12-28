#ifndef IMEDIUM_H
#define IMEDIUM_H

#include "IObject.h"

class IMedium : public IObject{
public:
    IMedium(std::string key) : IObject(key) {}
private:
};

#endif