#ifndef IBAND_WIDTH_CONTROL_H
#define IBAND_WIDTH_CONTROL_H

#include "IObject.h"

class IBandwidthControl : public IObject{
public:
    IBandwidthControl(std::string key) : IObject(key) {}
private:
};

#endif