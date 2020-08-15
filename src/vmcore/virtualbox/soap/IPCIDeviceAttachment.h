#ifndef IPCI_DEVICE_ATTACHMENT_H
#define IPCI_DEVICE_ATTACHMENT_H

#include "IObject.h"

class IPCIDeviceAttachment : public IObject{
public:
    IPCIDeviceAttachment(std::string key) : IObject(key) {}
private:
};

#endif