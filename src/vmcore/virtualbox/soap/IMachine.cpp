#include "IMachine.h"

/* std::string IMachine::icon(){
    _ns1__IMachine_USCOREgetIcon req;
    req._USCOREthis = this->key();
    _ns1__IMachine_USCOREgetIconResponse resp;

    int result = soap_call___ns1__IMachine_USCOREgetIcon(this->soapClient()->soap(), this->soapClient()->endpoint().c_str(), nullptr, &req, resp);
    if(result == SOAP_OK){
        this->iconProp = resp.returnval;
    }else{
        exception_util::resolve_throw(result, this->soapClient()->soap());
    }
    return this->iconProp;
} */

prop_generator(const std::string&, IMachine, icon, _ns1__IMachine_USCOREgetIcon);
prop_generator(bool, IMachine, accessible, _ns1__IMachine_USCOREgetAccessible);
