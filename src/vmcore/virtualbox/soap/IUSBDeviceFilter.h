#ifndef IUSB_DEVICE_FILTER_H
#define IUSB_DEVICE_FILTER_H

#include "IObject.h"

class IUSBDeviceFilter : public IObject{
public:
    IUSBDeviceFilter(std::string key) : IObject(key) {}
private:
};

#endif