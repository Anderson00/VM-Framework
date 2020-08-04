#include <iostream>

#include "soapH.h"
#include "vboxBinding.nsmap"

#include "gtest/gtest.h"
#include "SOAPClientSingleton.h"
#include "vmcore/virtualbox/soap/IWebSessionManagerTest.h"

using namespace std;

TEST(nada, nn){
    ASSERT_EQ(1,1);
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);

    SOAPClientSingleton* client = SOAPClientSingleton::getInstance();
    client->endpoint("127.0.0.1");

    return RUN_ALL_TESTS();
}