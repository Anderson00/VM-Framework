#ifndef IOBJECT_H
#define IOBJECT_H

#include "SOAPClientSingleton.h"
#include <iostream>
#include <string>

class IObject{

public:
    IObject(std::string objKey = std::string("")) : objKey{objKey} {}
    IObject(const IObject &obj) = delete;
    IObject(IObject &&obj) = delete;

    IObject& operator =(const IObject &obj) = delete;
    IObject& operator =(IObject &&obj) = delete;

    const std::string& key() const {
        return this->objKey;
    }

    SOAPClientSingleton* soapClient(){
        return SOAPClientSingleton::getInstance();
    }

private:
    std::string objKey;
};

#endif