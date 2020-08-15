#ifndef IUSB_DEVICE_FILTERS_H
#define IUSB_DEVICE_FILTERS_H

#include "IObject.h"

class IUSBDeviceFilters : public IObject{
public:
    IUSBDeviceFilters(std::string key) : IObject(key) {}
private:
};

#endif