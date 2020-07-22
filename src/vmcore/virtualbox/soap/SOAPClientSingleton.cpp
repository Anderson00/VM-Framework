#include "SOAPClientSingleton.h"

SOAPClientSingleton::getInstance(){
    if(instance == nullptr){
        instance = new SOAPClientSingleton();
    }
    return this->instance;
}