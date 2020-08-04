#include "ISession.h"

void ISession::unlockMachine(){

}

VBox::SessionState ISession::state(){
    /*
    _ns1__ISession_USCOREgetState req;
    req._USCOREthis = this->key();
    _ns1__ISession_USCOREgetStateResponse resp;

    int result = soap_call___ns1__ISession_USCOREgetState(this->soapClient().soap(), this->endpoint().c_str(), nullptr, &req, resp);
    if(result == SOAP_OK){
        //TODO:
        return (VBox::SessionState) resp.returnval;
    }else{
        //TODO: Exception
    }
    */
   return VBox::SessionState::LOCKED;
}