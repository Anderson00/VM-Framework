#ifndef SOAPClient_SINGLETON_H
#define SOAPClient_SINGLEON_H

#include "VBox.h"

namespace VBox{
    class SOAPClientSingleton{
    public:
        SOAPClientSingleton(const SOAPClientSingleton& client) = delete;
        SOAPClientSingleton(SOAPClientSingleton&& client) = delete;

        SOAPClientSingleton operator =(const SOAPClientSingleton& client) = delete;
        SOAPClientSingleton operator =(SOAPClientSingleton&& client) = delete;

        static SOAPClientSingleton* getInstance();

        VBox::SoapObject* soap(){return this->soapObj;}
        const std::string& endpoint() const {return this->endpointStr;}

    private:
        SOAPClientSingleton(){

        }

        SOAPClientSingleton* instance;
        VBox::SoapObject *soapObj;
        std::string endpointStr;
    };
}

#endif