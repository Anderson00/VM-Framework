#include <iostream>

#include "soapH.h"
#include "vboxBinding.nsmap"

#include "gtest/gtest.h"
#include "SOAPClientSingleton.h"
#include "vmcore/virtualbox/soap/IWebSessionManagerTest.h"
#include "vmcore/virtualbox/soap/IVirtualBoxTest.h"
#include "vmcore/virtualbox/soap/IMachineTest.h"

using namespace std;

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);

    SOAPClientSingleton* client = SOAPClientSingleton::getInstance();
    client->endpoint("127.0.0.1:18083");

    return RUN_ALL_TESTS();
}