#include "IWebSessionManager.h"


std::shared_ptr<IVirtualBox>
IWebSessionManager::logon(std::string username, std::string password){
    _ns1__IWebsessionManager_USCORElogon req;
    req.username = username;
    req.password = password;
    _ns1__IWebsessionManager_USCORElogonResponse resp;
    std::cout << "Chegou aqui" << std::endl;
    int result = soap_call___ns1__IWebsessionManager_USCORElogon(this->soapClient()->soap(), this->soapClient()->endpoint().c_str(), nullptr, &req, resp);
    if(result == SOAP_OK){
        this->vbox = std::shared_ptr<IVirtualBox>(new IVirtualBox(resp.returnval));
    }else{
        soap_print_fault(this->soapClient()->soap(), nullptr);
        //TODO: Exception
    }
    return this->vbox;
}

void IWebSessionManager::logoff(){
    /*
    
    _ns1__IWebsessionManager_USCORElogoff req;
    req.refIVirtualBox = this->vbox->key();
    _ns1__IWebsessionManager_USCORElogoffResponse resp;
    int result = soap_call___ns1__IWebsessionManager_USCORElogoff(this->soap(), this->endpoint(), nullptr, &req, resp);
    if(result == SOAP_OK){
        //TODO: 
    }else{
        //TODO: Exception
    }
    */
}

std::shared_ptr<ISession> IWebSessionManager::getSessionObject(){
    /*
    _ns1__IWebsessionManager_USCOREgetSessionObject req;
    req.refIVirtualBox = this->vbox->key();
    _ns1__IWebsessionManager_USCOREgetSessionObjectResponse resp;
    int result = soap_call___ns1__IWebsessionManager_USCOREgetSessionObject(this->soap(), this->endpoint(), nullptr, &req, resp);
    if(result == SOAP_OK){
        //TODO: Criar o ISession;
        std::string objKeySession = resp.returnval;
    }else{
        //TODO: Exception
    }
    */
   return std::shared_ptr<ISession>(nullptr);
}