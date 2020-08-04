#ifndef SOAPCLIENT_SINGLETON_TEST_H
#define SOAPCLIENT_SINGLETON_TEST_H

#include "SOAPClientSingleton.h"

TEST(SOAPClientSingleton, SoapClient){
    SOAPClientSingleton* client = SOAPClientSingleton::getInstance();
    ASSERT_NE(client->soap(), nullptr);
    ASSERT_STREQ(client->endpoint().c_str(), "127.0.0.1");
}

#endif