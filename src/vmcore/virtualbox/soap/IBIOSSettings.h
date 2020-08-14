#ifndef IBIOS_SETTINGS_H
#define IBIOS_SETTINGS_H

#include "IObject.h"

class IBIOSSettings : public IObject{
public:
    IBIOSSettings(std::string key) : IObject(key){}
private:
};

#endif