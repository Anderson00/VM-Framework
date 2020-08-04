#ifndef IWEB_SESSION_MANAGER_TEST_H
#define IWEB_SESSION_MANAGER_TEST_H

#include "IWebSessionManager.h"
#include "VBox.h"



TEST(IWebSessionManager, logon){
    IWebSessionManager m;
    m.logon("","");
    auto vbox = m.logon("","");
    ASSERT_NE(vbox.get(), nullptr);
}

#endif