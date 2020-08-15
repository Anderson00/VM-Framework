#ifndef IUSB_CONTROLLER_H
#define IUSB_CONTROLLER_H

#include "IObject.h"

class IUSBController : public IObject {
public:
    IUSBController(std::string key) : IObject(key) {}
private:
};

#endif