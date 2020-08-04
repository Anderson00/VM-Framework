#ifndef SOAPCLIENT_SINGLETON_H
#define SOAPCLIENT_SINGLETON_H

#include <iostream>
#include "soapH.h"

class SOAPClientSingleton{
public:
    SOAPClientSingleton(const SOAPClientSingleton& client) = delete;
    SOAPClientSingleton(SOAPClientSingleton&& client) = delete;

    ~SOAPClientSingleton(){
        soap_destroy(soapObj);
        soap_end(soapObj);
        soap_free(soapObj);
        std::cout << "Singleton Destruido!" << std::endl;
    }

    SOAPClientSingleton& operator =(const SOAPClientSingleton& client) = delete;
    SOAPClientSingleton& operator =(SOAPClientSingleton&& client) = delete;

        
    static SOAPClientSingleton* getInstance();

    struct soap* soap(){return this->soapObj;}

    /*! \brief this method set soapObj, if soapObj is not null then destroy and replace
    *
    *   \param obj new soapObj instantiated with soap_init() 
    */
    struct soap* soap(struct soap* obj);
    const std::string& endpoint() const {return this->endpointStr;}
    void endpoint(const std::string address){this->endpointStr = address;}

private:
    SOAPClientSingleton() : soapObj{soap_new()}{
        
    }

    static SOAPClientSingleton* instance;
    
    struct soap* soapObj;
    std::string endpointStr;
};
#endif