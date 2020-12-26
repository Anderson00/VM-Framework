#ifndef IVIRTUAL_BOX_TEST_H
#define IVIRTUAL_BOX_TEST_H

#include "IWebSessionManager.h"
#include "IVirtualBox.h"
#include <memory>

class IVirtualBoxTest : public ::testing::Test{
protected:
    void SetUp() override {
        IWebSessionManager mn;
        vbox = mn.logon("","");
    }

    std::shared_ptr<IVirtualBox> vbox;
    std::shared_ptr<const IVirtualBox> vboxConst;
};


TEST_F(IVirtualBoxTest, Properties){
    std::string version = vbox->version();
    std::string versionNormalized = vbox->versionNormalized();
    unsigned long revision = vbox->revision();
    std::string packageType = vbox->packageType();
    std::string APIVersion = vbox->APIVersion();
    long long APIRevision = vbox->APIRevision();
    std::string homeFolder = vbox->homeFolder();
    std::string settingsFilePath = vbox->settingsFilePath();

    EXPECT_TRUE(version != "");
    EXPECT_TRUE(versionNormalized != "");
    EXPECT_TRUE(revision != 0);
    EXPECT_TRUE(packageType != "");
    EXPECT_TRUE(APIVersion != "");
    EXPECT_TRUE(APIRevision != 0);
    EXPECT_TRUE(homeFolder != "");
    EXPECT_TRUE(settingsFilePath != "");
}

TEST_F(IVirtualBoxTest, machines){
    ASSERT_NO_THROW({
        auto machines = vbox->machines();

        ASSERT_TRUE(machines.size() >= 0);
    });



}

#endif