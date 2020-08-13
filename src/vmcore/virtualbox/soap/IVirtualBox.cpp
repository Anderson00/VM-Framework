#include "IVirtualBox.h"


#define prop_generator(RETURN, PROP, REQ)          \
    RETURN IVirtualBox::PROP(){                    \
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

#define prop_const_generator(RETURN, NAME, PROP)   \
    RETURN IVirtualBox::NAME() const {return this->PROP;}

prop_generator(const std::string&, version, _ns1__IVirtualBox_USCOREgetVersion);
prop_generator(const std::string&, versionNormalized, _ns1__IVirtualBox_USCOREgetVersionNormalized);
prop_generator(unsigned long, revision, _ns1__IVirtualBox_USCOREgetRevision);
prop_generator(const std::string&, packageType, _ns1__IVirtualBox_USCOREgetPackageType);
prop_generator(const std::string&, APIVersion, _ns1__IVirtualBox_USCOREgetAPIVersion);
prop_generator(LONG64, APIRevision, _ns1__IVirtualBox_USCOREgetAPIRevision);
prop_generator(const std::string&, homeFolder, _ns1__IVirtualBox_USCOREgetHomeFolder);
prop_generator(const std::string&, settingsFilePath, _ns1__IVirtualBox_USCOREgetSettingsFilePath);

//TODO: casos especiais, tem que criar recursivamente os objetos por returnval retorna so a ID
// prop_generator(const std::shared_ptr<IHost>, host, _ns1__IVirtualBox_USCOREgetHost);
// prop_generator(const std::shared_ptr<IHost>, host, hostProp);
// prop_generator(const std::shared_ptr<ISystemProperties>, systemProperties, systemPropertiesProp);
// prop_generator(const std::vector<std::shared_ptr<IMachine>>&, machines, machinesProp);

prop_const_generator(const std::string&, version, versionProp);
prop_const_generator(const std::string&, versionNormalized, versionNormalizedProp);
prop_const_generator(unsigned long, revision, revisionProp);
prop_const_generator(const std::string&, packageType, packageTypeProp);
prop_const_generator(const std::string&, APIVersion, APIVersionProp);
prop_const_generator(LONG64, APIRevision, APIRevisionProp);
prop_const_generator(const std::string&, homeFolder, homeFolderProp);
prop_const_generator(const std::string&, settingsFilePath, settingsFilePathProp);
prop_const_generator(const std::shared_ptr<IHost>, host, hostProp);
prop_const_generator(const std::shared_ptr<ISystemProperties>, systemProperties, systemPropertiesProp);
prop_const_generator(const std::vector<std::shared_ptr<IMachine>>&, machines, machinesProp);


const std::vector<std::shared_ptr<IMachine>>& IVirtualBox::machines(){
    _ns1__IVirtualBox_USCOREgetMachines req;
    req._USCOREthis = this->key();
    _ns1__IVirtualBox_USCOREgetMachinesResponse resp;

    int result = soap_call___ns1__IVirtualBox_USCOREgetMachines(this->soapClient()->soap(), this->soapClient()->endpoint().c_str(), nullptr, &req, resp);
    if(result == SOAP_OK){
        std::vector<std::string> machines = resp.returnval;
        for(std::string m : machines){
            this->machinesProp.push_back(std::shared_ptr<IMachine>(new IMachine(m)));
        }
    }else{
        exception_util::resolve_throw(result, this->soapClient()->soap());
    }
    return this->machinesProp;
}