#ifndef UTILS_H
#define UTILS_H

#define prop_generator(RETURN, CLASSNAME, PROP, REQ)          \
    RETURN CLASSNAME##::##PROP(){                    \
        REQ req;                                   \
        req._USCOREthis = this->key();             \
        REQ##Response resp;                        \
        int result = soap_call__##REQ(this->soapClient()->soap(), this->soapClient()->endpoint().c_str(), nullptr, &req, resp); \
        if(result == SOAP_OK){                     \
            this->PROP##Prop = resp.returnval;     \
            return this->PROP##Prop;               \
        }                                          \
        else{                                      \
            exception_util::resolve_throw(result, this->soapClient()->soap());\
        }                                          \
        return this->PROP##Prop;                   \
    }

#define prop_const_generator(RETURN, CLASSNAME, NAME, PROP)   \
    RETURN CLASSNAME::NAME() const {return this->PROP;}

namespace utils{

}

#endif