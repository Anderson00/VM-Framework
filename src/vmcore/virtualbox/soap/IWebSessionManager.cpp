#include "IWebSessionManager.h"


std::shared_ptr<IVirtualBox>
IWebSessionManager::logon(std::string username, std::string password){
    _ns1__IWebsessionManager_USCORElogon req;
    req.username = username;
    req.password = password;
    _ns1__IWebsessionManager_USCORElogonResponse resp;
    int result = soap_call___ns1__IWebsessionManager_USCORElogon(this->soapClient()->soap(), this->soapClient()->endpoint().c_str(), nullptr, &req, resp);
    if(result == SOAP_OK){        
        this->vbox = std::shared_ptr<IVirtualBox>(new IVirtualBox(resp.returnval));
    }else{
        if(result == SOAP_CLI_FAULT){
            throw logon_exception("Login or Pass is incorrect!");
        }else{
            exception_util::resolve_throw(result, this->soapClient()->soap());
        }        
    }
    return this->vbox;
}

void IWebSessionManager::logoff(){
    if(this->vbox.get() == nullptr) return;
    _ns1__IWebsessionManager_USCORElogoff req;
    req.refIVirtualBox = this->vbox->key();
    _ns1__IWebsessionManager_USCORElogoffResponse resp;
    int result = soap_call___ns1__IWebsessionManager_USCORElogoff(this->soapClient()->soap(), this->soapClient()->endpoint().c_str(), nullptr, &req, resp);
    if(result == SOAP_OK){
        //TODO: 
    }else{
        exception_util::resolve_throw(result, this->soapClient()->soap());
    }
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