#ifndef IOBJECT_H
#define IOBJECT_H

#include "soapH.h"
#include "VBox.h"
#include <iostream>
#include <string>

class IObject{

public:
    IObject(std::string objKey = "") : objKey{objKey} { }
    IObject(const IObject &obj) = delete;
    IObject(IObject &&obj) = delete;

    IObject& operator =(const IObject &obj) = delete;
    IObject& operator =(IObject &&obj) = delete;

    const std::string& key() const {
        return this->objKey;
    }

private:
    std::string objKey;
};

#endif