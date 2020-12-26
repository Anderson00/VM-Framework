//
// Created by anderson on 26/12/2020.
//

#ifndef VM_FRAMEWORK_IHOSTUSBDEVICEFILTER_H
#define VM_FRAMEWORK_IHOSTUSBDEVICEFILTER_H

#include "IObject.h"

class IHostUSBDeviceFilter : public IObject{
public:
    IHostUSBDeviceFilter(std::string key) : IObject(key){}
private:
};


#endif //VM_FRAMEWORK_IHOSTUSBDEVICEFILTER_H
