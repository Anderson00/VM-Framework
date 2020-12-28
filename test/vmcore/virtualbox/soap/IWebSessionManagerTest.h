#ifndef IWEB_SESSION_MANAGER_TEST_H
#define IWEB_SESSION_MANAGER_TEST_H

#include "IWebSessionManager.h"
#include "VBox.h"

class IWebSessionManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        webSess.logon("","");
    }
    IWebSessionManager webSess;
};


TEST(IWebSessionManager, logon){
    ASSERT_NO_THROW({
        IWebSessionManager m;
        auto vbox = m.logon("","");
    });
}

TEST_F(IWebSessionManagerTest, logoff){
    ASSERT_NO_THROW({
        webSess.logoff();
    });
}

#endif