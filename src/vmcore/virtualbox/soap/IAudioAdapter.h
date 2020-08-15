#ifndef IAUDIO_ADAPTER_H
#define IAUDIO_ADAPTER_H

#include "IObject.h"

class IAudioAdapter : public IObject {
public:
    IAudioAdapter(std::string key) : IObject(key) {}
private:
};

#endif