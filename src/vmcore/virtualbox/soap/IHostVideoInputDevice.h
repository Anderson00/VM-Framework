//
// Created by anderson on 26/12/2020.
//

#ifndef VM_FRAMEWORK_IHOSTVIDEOINPUTDEVICE_H
#define VM_FRAMEWORK_IHOSTVIDEOINPUTDEVICE_H

#include "IObject.h"

class IHostVideoInputDevice : public IObject{
public:
    IHostVideoInputDevice(std::string key) : IObject(key) {}
private:
};


#endif //VM_FRAMEWORK_IHOSTVIDEOINPUTDEVICE_H
