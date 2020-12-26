#include <iostream>
#include <cxxopts.hpp>
#include "soapH.h"
#include "vboxBinding.nsmap"
#include "vmcore/virtualbox/soap/SOAPClientSingleton.h"
#include "vmcore/virtualbox/soap/IWebSessionManager.h"


int main(int argc, char **argv){
    cxxopts::Options options("VM-Framework", "Framework");

    SOAPClientSingleton *client = SOAPClientSingleton::getInstance();

    //TODO: cxxopts command line

    return 0;
}