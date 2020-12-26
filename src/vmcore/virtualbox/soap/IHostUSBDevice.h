//
// Created by anderson on 26/12/2020.
//

#ifndef VM_FRAMEWORK_IHOSTUSBDEVICE_H
#define VM_FRAMEWORK_IHOSTUSBDEVICE_H

#include "IObject.h"

class IHostUSBDevice : public IObject{
public:
    IHostUSBDevice(std::string key) : IObject(key) {}
private:
};

#endif //VM_FRAMEWORK_IHOSTUSBDEVICE_H
