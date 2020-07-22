#include "IWebSessionManager.h"
#include "soapH.h"
#include "vboxBinding.nsmap"

std::shared_ptr<VBox::IVirtualBox>
VBox::IWebSessionManager::logon(std::string username, std::string password){
    _ns1__IWebsessionManager_USCORElogon req;
    req.username = username;
    req.password = password;
    _ns1__IWebsessionManager_USCORElogonResponse resp;
    int result = soap_call___ns1__IWebsessionManager_USCORElogon(this->soap(), this->endpoint(), nullptr, &req, resp);
    if(result == SOAP_OK){
        this->vbox = std::shared_ptr<VBox::IVirtualBox>(new VBox::IVirtualBox(
            this->soap(), this->endpoint(), resp.returnval));

        return this->vbox;
    }else{
        //TODO: Exception
    }
}

void VBox::IWebSessionManager::logoff(){
    
    _ns1__IWebsessionManager_USCORElogoff req;
    req.refIVirtualBox = this->vbox->key();
    _ns1__IWebsessionManager_USCORElogoffResponse resp;
    int result = soap_call___ns1__IWebsessionManager_USCORElogoff(this->soap(), this->endpoint(), nullptr, &req, resp);
    if(result == SOAP_OK){
        //TODO: construir logica para liberar a memoria do shared_ptr
    }else{
        //TODO: Exception
    }

}

std::shared_ptr<ISession> getSessionObject(){
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
}