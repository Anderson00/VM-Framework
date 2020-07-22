#include "ISession.h"

void VBox::ISession::unlockMachine(){

}

VBox::SessionState VBox::ISession::state(){
    _ns1__ISession_USCOREgetState req;
    req._USCOREthis = this->key();
    _ns1__ISession_USCOREgetStateResponse resp;

    int result = soap_call___ns1__ISession_USCOREgetState(this->soap(), this->endpoint(), nullptr, &req, resp);
    if(result == SOAP_OK){
        //TODO:
        return (VBox::SessionState) resp.returnval;
    }else{
        //TODO: Exception
    }

}