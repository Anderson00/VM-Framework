#ifndef IWEB_SESSION_MANAGER_H
#define IWEB_SESSION_MANAGER_H

#include "IObject.h"
#include "IVirtualBox.h"
#include "VBox.h"
#include "ISession.h"
#include <iostream>
#include <string>
#include <memory>

namespace VBox{
    class IWebSessionManager : public IObject{

    public:
        IWebSessionManager(VBox::SoapObject *soap, std::string endpoint) : IObject(soap, endpoint) {}

        std::shared_ptr<VBox::IVirtualBox> logon(std::string username, std::string password);
        void logoff(const VBox::IVirtualBox &refIVirtualBox);
        std::shared_ptr<ISession> getSessionObject(const VBox::IVirtualBox &refIVirtualBox);

    private:
        std::shared_ptr<VBox::IVirtualBox> vbox;
    };
};


#endif