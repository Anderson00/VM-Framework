#ifndef IRECORDING_SETTINGS_H
#define IRECORDING_SETTINGS_H

#include "IObject.h"

class IRecordingSettings : public IObject{
public:
    IRecordingSettings(std::string key) : IObject(key) {}
private:
};

#endif