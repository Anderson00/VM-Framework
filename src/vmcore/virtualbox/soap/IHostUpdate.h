//
// Created by anderson on 26/12/2020.
//

#ifndef VM_FRAMEWORK_IHOSTUPDATE_H
#define VM_FRAMEWORK_IHOSTUPDATE_H

#include "IObject.h"

class IHostUpdate : public IObject{
public:
    IHostUpdate(std::string key) : IObject(key) {}
private:
};


#endif //VM_FRAMEWORK_IHOSTUPDATE_H
