#include "IVirtualBox.h"

/*
#define prop_generator(METHOD, REQ) \
    const std::string& IVirtualBox::METHOD(){    
        REQ req;
        req._USCOREthis = this->key();
        REQResponse resp;
        
        int result = soap_call__REQ(this->soapClient().soap(), this->soapClient().endpoint(), nullptr, &req, resp);
        if(result == SOAP_OK){
            this->versionProp = resp.returnval;
        }else{
            //TODO: Exceptions
        }
        return this->versionProp;
    }
    */

//#define prop_const_generator(NAME, PROP) \
//    const std::string& NAME() const {return this->PROP;}

const std::string& IVirtualBox::version(){    
    /* _ns1__IVirtualBox_USCOREgetVersion req;
    req._USCOREthis = this->key();
    _ns1__IVirtualBox_USCOREgetVersionResponse resp;
    
    int result = soap_call___ns1__IVirtualBox_USCOREgetVersion(this->soapClient().soap(), this->soapClient().endpoint().c_str(), nullptr, &req, resp);
    if(result == SOAP_OK){
        this->versionProp = resp.returnval;
    }else{
        //TODO: Exceptions
    }*/
    return this->versionProp;
}

/*
prop_const_generator(version, versionProp);
prop_const_generator(versionNormalized, versionNormalizedProp);
prop_const_generator(revision, revisionProp);
prop_const_generator(packageType, packageTypeProp);
prop_const_generator(APIVersion, APIVersionProp);
prop_const_generator(APIRevision, APIRevisionProp);
prop_const_generator(homeFolder, homeFolderProp);
prop_const_generator(settingsFilePath, settingsFilePathProp);
prop_const_generator(host, hostProp);
prop_const_generator(systemProperties, systemPropertiesProp);
prop_const_generator(machines, machinesProp);
*/

const std::string& IVirtualBox::versionNormalized(){    
    /* _ns1__IVirtualBox_USCOREgetVersionNormalized req;
    req._USCOREthis = this->key();
    _ns1__IVirtualBox_USCOREgetVersionNormalizedResponse resp;
    
    int result = soap_call___ns1__IVirtualBox_USCOREgetVersionNormalized(this->soapClient().soap(), this->soapClient().endpoint().c_str(), nullptr, &req, resp);
    if(result == SOAP_OK){
        this->versionNormalizedProp = resp.returnval;
    }else{
        //TODO: Exceptions
    }*/
    return this->versionNormalizedProp;
}

const std::string& IVirtualBox::revision(){    
    /* _ns1__IVirtualBox_USCOREgetRevision req;
    req._USCOREthis = this->key();
    _ns1__IVirtualBox_USCOREgetRevisionResponse resp;
    
    int result = soap_call___ns1__IVirtualBox_USCOREgetRevision(this->soapClient().soap(), this->soapClient().endpoint().c_str(), nullptr, &req, resp);
    if(result == SOAP_OK){
        this->revisionProp = resp.returnval;
    }else{
        //TODO: Exceptions
    }*/
    return this->revisionProp;
}

const std::string& IVirtualBox::APIVersion(){    
    /* _ns1__IVirtualBox_USCOREgetAPIVersion req;
    req._USCOREthis = this->key();
    _ns1__IVirtualBox_USCOREgetAPIVersionResponse resp;
    
    int result = soap_call___ns1__IVirtualBox_USCOREgetAPIVersion(this->soapClient().soap(), this->soapClient().endpoint().c_str(), nullptr, &req, resp);
    if(result == SOAP_OK){
        this->APIVersionProp = resp.returnval;
    }else{
        //TODO: Exceptions
    }*/
    return this->APIVersionProp;
}

const std::string& IVirtualBox::APIRevision(){    
    /* _ns1__IVirtualBox_USCOREgetAPIRevision req;
    req._USCOREthis = this->key();
    _ns1__IVirtualBox_USCOREgetAPIRevisionResponse resp;
    
    int result = soap_call___ns1__IVirtualBox_USCOREgetAPIRevision(this->soapClient().soap(), this->soapClient().endpoint().c_str(), nullptr, &req, resp);
    if(result == SOAP_OK){
        this->APIRevisionProp = resp.returnval;
    }else{
        //TODO: Exceptions
    }*/
    return this->APIRevisionProp;
}

const std::string& IVirtualBox::homeFolder(){
    /*  if(!this->homeFolderProp.empty())
        return this->homeFolderProp;
    
    _ns1__IVirtualBox_USCOREgetHomeFolder req;
    req._USCOREthis = this->key();
    _ns1__IVirtualBox_USCOREgetHomeFolderResponse resp;
    
    int result = soap_call___ns1__IVirtualBox_USCOREgetHomeFolder(this->soapClient().soap(), this->soapClient().endpoint().c_str(), nullptr, &req, resp);
    if(result == SOAP_OK){
        this->homeFolderProp = resp.returnval;
    }else{
        //TODO: Exceptions
    }*/
    return this->homeFolderProp;
}

const std::string& IVirtualBox::settingsFilePath(){    
    /* _ns1__IVirtualBox_USCOREgetSettingsFilePath req;
    req._USCOREthis = this->key();
    _ns1__IVirtualBox_USCOREgetSettingsFilePathResponse resp;
    
    int result = soap_call___ns1__IVirtualBox_USCOREgetSettingsFilePath(this->soapClient().soap(), this->soapClient().endpoint().c_str(), nullptr, &req, resp);
    if(result == SOAP_OK){
        this->settingsFilePathProp = resp.returnval;
    }else{
        //TODO: Exceptions
    }*/
    return this->settingsFilePathProp;
}