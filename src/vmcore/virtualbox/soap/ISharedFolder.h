#ifndef ISHARED_FOLDER_H
#define ISHARED_FOLDER_H

#include "IObject.h"

class ISharedFolder : public IObject{
public:
    ISharedFolder(std::string key) : IObject(key){}
private:

};

#endif