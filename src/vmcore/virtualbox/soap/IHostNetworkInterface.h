//
// Created by anderson on 26/12/2020.
//

#ifndef VM_FRAMEWORK_IHOSTNETWORKINTERFACE_H
#define VM_FRAMEWORK_IHOSTNETWORKINTERFACE_H

#include "IObject.h"

class IHostNetworkInterface : public IObject {
public:
    IHostNetworkInterface(std::string key) : IObject(key) {}
private:
};


#endif //VM_FRAMEWORK_IHOSTNETWORKINTERFACE_H
