#ifndef IMEDIUM_ATTACHMENT_H
#define IMEDIUM_ATTACHMENT_H

#include "IObject.h"

class IMediumAttachment : public IObject{
public:
    IMediumAttachment(std::string key) : IObject(key){}
private:
};

#endif