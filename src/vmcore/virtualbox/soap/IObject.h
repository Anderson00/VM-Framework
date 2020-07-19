#ifndef IOBJECT_H
#define IOBJECT_H

#include "soapH.h"
#include "VBox.h"
#include <iostream>
#include <string>

class IObject{

public:
    IObject(VBox::SoapObject *soapObj, std::string address) : soapObj{soapObj}, address{address} { }
    IObject(const IObject &obj) = delete;
    IObject(IObject &&obj) = delete;

    IObject& operator =(const IObject &obj) = delete;
    IObject& operator =(IObject &&obj) = delete;

    VBox::SoapObject* soap() const {
        return this->soapObj;
    }

    const std::string& endpoint() const {
        return this->address;
    }

private:
    VBox::SoapObject *soapObj;
    std::string address;
};

#endif