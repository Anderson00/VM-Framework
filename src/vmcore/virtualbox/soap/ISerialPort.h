#ifndef ISERIAL_PORT_H
#define ISERIAL_PORT_H

#include "IObject.h"

class ISerialPort : public IObject{
public:
    ISerialPort(std::string key) : IObject(key){}
private:
};

#endif