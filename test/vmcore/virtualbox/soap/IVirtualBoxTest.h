#ifndef IVIRTUAL_BOX_TEST_H
#define IVIRTUAL_BOX_TEST_H

#include "IWebSessionManager.h"
#include "IVirtualBox.h"
#include <memory>

class IVirtualBoxTest : public ::testing::Test{
protected:
    void SetUp() override {
        vbox = mn.logon("","");
    }

    void TearDown() override{
        mn.logoff();
    }
    IWebSessionManager mn;
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
    EXPECT_TRUE(!vbox->host()->key().empty());
    EXPECT_NO_THROW({
        EXPECT_TRUE(vbox->machines().size() >= 0);
    });
    EXPECT_NO_THROW({
        EXPECT_TRUE(vbox->machineGroups().size() >= 0);
    });
    EXPECT_NO_THROW({
        auto disks = vbox->hardDisks();
        if(disks.size() > 0){
            EXPECT_TRUE(!disks[0].get()->key().empty());
        }
    });
    EXPECT_NO_THROW({
        auto dvds = vbox->DVDImages();
        if(dvds.size() > 0){
            EXPECT_TRUE(!dvds[0].get()->key().empty());
        }
    });
    EXPECT_NO_THROW({
        auto floppys = vbox->floppyImages();
        if(floppys.size() > 0){
            EXPECT_TRUE(!floppys[0].get()->key().empty());
        }
    });
    EXPECT_NO_THROW({
        auto operations = vbox->progressOperations();
        if(operations.size() > 0){
            EXPECT_TRUE(!operations[0].get()->key().empty());
        }
    });
    EXPECT_NO_THROW({
        auto types = vbox->guestOSTypes();
        if(types.size() > 0){
            EXPECT_TRUE(!types[0].get()->key().empty());
        }
    });

    EXPECT_NO_THROW({
        auto folders = vbox->sharedFolders();
        if(folders.size() > 0){
            EXPECT_TRUE(!folders[0].get()->key().empty());
        }
    });

    EXPECT_TRUE(!vbox->performaceCollector()->key().empty());

    EXPECT_NO_THROW({
        auto servers = vbox->DHCPServers();
        if(servers.size() > 0){
            EXPECT_TRUE(!servers[0].get()->key().empty());
        }
    });

    EXPECT_NO_THROW({
        auto networks = vbox->NATNetworks();
        if(networks.size() > 0){
            EXPECT_TRUE(!networks[0].get()->key().empty());
        }
    });

    EXPECT_NO_THROW({
        auto networks = vbox->internalNetworks();
        if(networks.size() > 0){
            EXPECT_TRUE(!networks[0].empty());
        }
    });

    EXPECT_NO_THROW({
        auto drivers = vbox->genericNetworkDrivers();
        if(drivers.size() > 0){
            EXPECT_TRUE(!drivers[0].empty());
        }
    });

    EXPECT_NO_THROW({
        auto networks = vbox->cloudNetworks();
        if(networks.size() > 0){
            EXPECT_TRUE(!networks[0].get()->key().empty());
        }
    });

    EXPECT_TRUE(!vbox->cloudProviderManager()->key().empty());
}
#endif