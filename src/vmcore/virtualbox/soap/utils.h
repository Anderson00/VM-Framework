#ifndef UTILS_H
#define UTILS_H

#define prop_generator(RETURN, CLASSNAME, PROP, REQ)          \
    RETURN CLASSNAME::PROP(){                    \
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

#define prop_generator_shared_ptr(RETURN, CLASSNAME, PROP, SHAREDTYPE, REQ)          \
    RETURN CLASSNAME::PROP(){                  \
        REQ req;                                   \
        req._USCOREthis = this->key();             \
        REQ##Response resp;                        \
        int result = soap_call__##REQ(this->soapClient()->soap(), this->soapClient()->endpoint().c_str(), nullptr, &req, resp); \
        if(result == SOAP_OK){                     \
            this->PROP##Prop = std::shared_ptr<SHAREDTYPE>(new SHAREDTYPE(resp.returnval));     \
            return this->PROP##Prop;               \
        }                                          \
        else{                                      \
            exception_util::resolve_throw(result, this->soapClient()->soap());\
        }                                          \
        return this->PROP##Prop;                   \
    }

#define prop_generator_vector_shared_ptr(RETURN, CLASSNAME, PROP, PROPCLASS, REQ)          \
    RETURN CLASSNAME::PROP(){                                                   \
        REQ req;                                                                \
        req._USCOREthis = this->key();                                          \
        REQ##Response resp;                                                     \
        int result = soap_call__##REQ(this->soapClient()->soap(), this->soapClient()->endpoint().c_str(), nullptr, &req, resp); \
        if(result == SOAP_OK){                                                  \
            for(std::string key : resp.returnval){                              \
                this->PROP##Prop.push_back(new PROPCLASS(key));                 \
            }                                                                   \
        }                                                                       \
        else{                                                                   \
            exception_util::resolve_throw(result, this->soapClient()->soap());  \
        }                                                                       \
        return this->PROP##Prop;                                                \
    }

#define prop_generator_vector_string(RETURN, CLASSNAME, PROP, REQ)              \
    RETURN CLASSNAME::PROP(){                                                   \
        REQ req;                                                                \
        req._USCOREthis = this->key();                                          \
        REQ##Response resp;                                                     \
        int result = soap_call__##REQ(this->soapClient()->soap(), this->soapClient()->endpoint().c_str(), nullptr, &req, resp); \
        if(result == SOAP_OK){                                                  \
            for(std::string key : resp.returnval){                              \
                this->PROP##Prop.push_back(key);                                \
            }                                                                   \
            return this->PROP##Prop;                                            \
        }                                                                       \
        else{                                                                   \
            exception_util::resolve_throw(result, this->soapClient()->soap());  \
        }                                                                       \
        return this->PROP##Prop;                                                \
    }

#define prop_const_generator(RETURN, CLASSNAME, NAME, PROP)   \
    RETURN CLASSNAME::NAME() const {return this->PROP;}

namespace utils{

}

#endif