#include "SOAPClientSingleton.h"

SOAPClientSingleton* SOAPClientSingleton::instance = nullptr;


SOAPClientSingleton* SOAPClientSingleton::getInstance(){
    if(!SOAPClientSingleton::instance){
        instance = new SOAPClientSingleton;
    }
    return instance;
}

struct soap* SOAPClientSingleton::soap(struct soap* obj){
    if(this->soapObj != nullptr){
        soap_destroy(this->soapObj);
        soap_end(this->soapObj);
        soap_free(this->soapObj);
    }

    this->soapObj = obj;
    return this->soapObj;
}