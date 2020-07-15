#ifndef IWEB_SESSION_MANAGER_H
#define IWEB_SESSION_MANAGER_H

#include "IVirtualBox.h"
#include "VBox.h"
#include "ISession.h"
#include <iostream>
#include <string>

namespace VBox{
    class IWebSessionManager{

    public:
        IWebSessionManager();

        IVirtualBox logon(std::wstring username, std::wstring password);
        void logoff(IVirtualBox &refIVirtualBox);
        ISession getSessionObject(IVirtualBox &refIVirtualBox);

    private:
        //void
    };
};


#endif