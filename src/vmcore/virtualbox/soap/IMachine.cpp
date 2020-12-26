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
prop_generator(const std::string&, IMachine, name, _ns1__IMachine_USCOREgetName);
prop_generator(const std::string&, IMachine, id, _ns1__IMachine_USCOREgetId);
prop_generator_vector_string(const std::vector<std::string>&, IMachine, groups, _ns1__IMachine_USCOREgetGroups);
prop_generator(const std::string&, IMachine, OSTypeId, _ns1__IMachine_USCOREgetOSTypeId);
prop_generator(const std::string&, IMachine, hardwareVersion, _ns1__IMachine_USCOREgetHardwareVersion);
prop_generator(const std::string&, IMachine, hardwareUUID, _ns1__IMachine_USCOREgetHardwareUUID);
prop_generator(unsigned long, IMachine, CPUCount, _ns1__IMachine_USCOREgetCPUCount);
prop_generator(bool, IMachine, CPUHotPlugEnabled, _ns1__IMachine_USCOREgetCPUHotPlugEnabled);
prop_generator(unsigned long, IMachine, CPUExecutionCap, _ns1__IMachine_USCOREgetCPUExecutionCap);
prop_generator(unsigned long, IMachine, CPUIDPortabilityLevel, _ns1__IMachine_USCOREgetCPUIDPortabilityLevel);
prop_generator(unsigned long, IMachine, memorySize, _ns1__IMachine_USCOREgetMemorySize);
prop_generator(unsigned long, IMachine, memoryBalloonSize, _ns1__IMachine_USCOREgetMemoryBalloonSize);
prop_generator(bool, IMachine, pageFusionEnabled, _ns1__IMachine_USCOREgetPageFusionEnabled);
prop_generator_shared_ptr(const std::shared_ptr<IGraphicsAdapter>, IMachine, graphicsAdapter, IGraphicsAdapter, _ns1__IMachine_USCOREgetGraphicsAdapter); 
prop_generator_shared_ptr(const std::shared_ptr<IBIOSSettings>, IMachine, BIOSSettings, IBIOSSettings, _ns1__IMachine_USCOREgetBIOSSettings); 
prop_generator_shared_ptr(const std::shared_ptr<IRecordingSettings>, IMachine, recordingSettings, IRecordingSettings, _ns1__IMachine_USCOREgetRecordingSettings);
VBox::FirmwareType IMachine::firmwareType(){
    _ns1__IMachine_USCOREgetFirmwareType req;
    req._USCOREthis = this->key();
    _ns1__IMachine_USCOREgetFirmwareTypeResponse resp;
}
//prop_generator_shared_ptr(const std::shared_ptr<IRecordingSettings>, IMachine, recordingSettings, IRecordingSettings, _ns1__IMachine_USCOREgetRecordingSettings);

