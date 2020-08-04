#ifndef IWEB_SESSION_MANAGER_H
#define IWEB_SESSION_MANAGER_H

#include "IObject.h"
#include "IVirtualBox.h"
#include "VBox.h"
#include "ISession.h"
#include <iostream>
#include <string>
#include <memory>

class IWebSessionManager : public IObject{

public:
    IWebSessionManager(){}

    std::shared_ptr<IVirtualBox> logon(std::string username, std::string password);
    void logoff();
    std::shared_ptr<ISession> getSessionObject();

private:
    std::shared_ptr<IVirtualBox> vbox;
};


#endif