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
prop_generator(bool, IMachine, HPETEnabled, _ns1__IMachine_USCOREgetHPETEnabled);
prop_generator(const std::string&, IMachine, snapshotFolder, _ns1__IMachine_USCOREgetSnapshotFolder);
prop_generator(bool, IMachine, emulatedUSBCardReaderEnabled, _ns1__IMachine_USCOREgetEmulatedUSBCardReaderEnabled);
prop_generator(const std::string&, IMachine, settingsFilePath, _ns1__IMachine_USCOREgetSettingsFilePath);
prop_generator(const std::string&, IMachine, settingsAuxFilePath, _ns1__IMachine_USCOREgetSettingsAuxFilePath);
prop_generator(bool, IMachine, settingsModified, _ns1__IMachine_USCOREgetSettingsModified);
prop_generator(const std::string&, IMachine, sessionName, _ns1__IMachine_USCOREgetSessionName);
prop_generator(unsigned long, IMachine, sessionPID, _ns1__IMachine_USCOREgetSessionPID);
prop_generator(long long, IMachine, lastStateChange, _ns1__IMachine_USCOREgetLastStateChange);
prop_generator(const std::string&, IMachine, stateFilePath, _ns1__IMachine_USCOREgetStateFilePath);
prop_generator(const std::string&, IMachine, logFolder, _ns1__IMachine_USCOREgetLogFolder);
prop_generator(unsigned long, IMachine, snapshotCount, _ns1__IMachine_USCOREgetSnapshotCount);
prop_generator(bool, IMachine, currentStateModified, _ns1__IMachine_USCOREgetCurrentStateModified);
prop_generator_vector_shared_ptr(const std::vector<std::shared_ptr<ISharedFolder>>, IMachine, sharedFolders, ISharedFolder, _ns1__IMachine_USCOREgetSharedFolders);
prop_generator(bool, IMachine, clipboardFileTransfersEnabled, _ns1__IMachine_USCOREgetClipboardFileTransfersEnabled);
prop_generator(bool, IMachine, teleporterEnabled, _ns1__IMachine_USCOREgetTeleporterEnabled);
prop_generator(unsigned long, IMachine, teleporterPort, _ns1__IMachine_USCOREgetTeleporterPort);
prop_generator(const std::string&, IMachine, teleporterAddress, _ns1__IMachine_USCOREgetTeleporterAddress);
prop_generator(const std::string&, IMachine, teleporterPassword, _ns1__IMachine_USCOREgetTeleporterPassword);
prop_generator(bool, IMachine, RTCUseUTC, _ns1__IMachine_USCOREgetRTCUseUTC);
prop_generator(bool, IMachine, IOCacheEnabled, _ns1__IMachine_USCOREgetIOCacheEnabled);
prop_generator(unsigned long, IMachine, IOCacheSize, _ns1__IMachine_USCOREgetIOCacheSize);
prop_generator(bool, IMachine, tracingEnabled, _ns1__IMachine_USCOREgetTracingEnabled);
prop_generator(const std::string&, IMachine, tracingConfig, _ns1__IMachine_USCOREgetTracingConfig);
prop_generator(bool, IMachine, allowTracingToAccessVM, _ns1__IMachine_USCOREgetAllowTracingToAccessVM);
prop_generator(bool, IMachine, autostartEnabled, _ns1__IMachine_USCOREgetAutostartEnabled);
prop_generator(unsigned long, IMachine, autostartDelay, _ns1__IMachine_USCOREgetAutostartDelay);
prop_generator(const std::string&, IMachine, defaultFrontend, _ns1__IMachine_USCOREgetDefaultFrontend);
prop_generator(bool, IMachine, USBProxyAvailable, _ns1__IMachine_USCOREgetUSBProxyAvailable);
prop_generator(const std::string&, IMachine, paravirtDebug, _ns1__IMachine_USCOREgetParavirtDebug);
prop_generator(const std::string&, IMachine, CPUProfile, _ns1__IMachine_USCOREgetCPUProfile);
prop_generator_shared_ptr(const std::shared_ptr<ISnapshot>, IMachine, currentSnapshot, ISnapshot, _ns1__IMachine_USCOREgetCurrentSnapshot);
prop_generator_shared_ptr(const std::shared_ptr<IGraphicsAdapter>, IMachine, graphicsAdapter, IGraphicsAdapter, _ns1__IMachine_USCOREgetGraphicsAdapter);
prop_generator_shared_ptr(const std::shared_ptr<IBIOSSettings>, IMachine, BIOSSettings, IBIOSSettings, _ns1__IMachine_USCOREgetBIOSSettings);
prop_generator_shared_ptr(const std::shared_ptr<IRecordingSettings>, IMachine, recordingSettings, IRecordingSettings, _ns1__IMachine_USCOREgetRecordingSettings);
prop_generator_shared_ptr(const std::shared_ptr<IVirtualBoxErrorInfo>, IMachine, accessError, IVirtualBoxErrorInfo, _ns1__IMachine_USCOREgetAccessError);
prop_generator_shared_ptr(const std::shared_ptr<IVRDEServer>, IMachine, VRDEServer, IVRDEServer, _ns1__IMachine_USCOREgetVRDEServer);
prop_generator_shared_ptr(const std::shared_ptr<IUSBDeviceFilter>, IMachine, USBDeviceFilters, IUSBDeviceFilter, _ns1__IMachine_USCOREgetUSBDeviceFilters);
prop_generator_shared_ptr(const std::shared_ptr<IAudioAdapter>, IMachine, audioAdapter, IAudioAdapter, _ns1__IMachine_USCOREgetAudioAdapter);
prop_generator_vector_shared_ptr(const std::vector<std::shared_ptr<IUSBController>>, IMachine, USBControllers, IUSBController, _ns1__IMachine_USCOREgetUSBControllers);
prop_generator_vector_string(const std::vector<std::string>, IMachine, groups, _ns1__IMachine_USCOREgetGroups);
//prop_generator_shared_ptr(const std::vector<std::shared_ptr<IStorageController>>, IMachine, storageControllers, IStorageController, _ns1__IMachine_USCOREgetStorageControllers);
//prop_generator_vector_shared_ptr(const std::vector<std::shared_ptr<IPCIDeviceAttachment>>, IMachine, PCIDeviceAssignments, _ns1__IMachine_USCOREgetPCIDeviceAssignments);
//prop_generator_shared_ptr(const std::shared_ptr<IBandwidthControl>, IMachine, bandwidthControl, _ns1__IMachine_USCOREgetBandwidthControl);

prop_const_generator(const std::string&, IMachine, icon, iconProp);
prop_const_generator(bool, IMachine, accessible, accessibleProp);
prop_const_generator(const std::string&, IMachine, name, nameProp);
prop_const_generator(const std::string&, IMachine, id, idProp);
prop_const_generator(const std::string&, IMachine, OSTypeId, OSTypeIdProp);
prop_const_generator(const std::string&, IMachine, hardwareVersion, hardwareVersionProp);
prop_const_generator(const std::string&, IMachine, hardwareUUID, hardwareUUIDProp);
prop_const_generator(unsigned long, IMachine, CPUCount, CPUCountProp);
prop_const_generator(bool, IMachine, CPUHotPlugEnabled, CPUHotPlugEnabledProp);
prop_const_generator(unsigned long, IMachine, CPUExecutionCap, CPUExecutionCapProp);
prop_const_generator(unsigned long, IMachine, CPUIDPortabilityLevel, CPUIDPortabilityLevelProp);
prop_const_generator(unsigned long, IMachine, memorySize, memorySizeProp);
prop_const_generator(unsigned long, IMachine, memoryBalloonSize, memoryBalloonSizeProp);
prop_const_generator(bool, IMachine, pageFusionEnabled, pageFusionEnabledProp);
prop_const_generator(bool, IMachine, HPETEnabled, HPETEnabledProp);
prop_const_generator(const std::string&, IMachine, snapshotFolder, snapshotFolderProp);
prop_const_generator(bool, IMachine, emulatedUSBCardReaderEnabled, emulatedUSBCardReaderEnabledProp);
prop_const_generator(const std::string&, IMachine, settingsFilePath, settingsFilePathProp);
prop_const_generator(const std::string&, IMachine, settingsAuxFilePath, settingsAuxFilePathProp);
prop_const_generator(bool, IMachine, settingsModified, settingsModifiedProp);
prop_const_generator(const std::string&, IMachine, sessionName, sessionNameProp);
prop_const_generator(unsigned long, IMachine, sessionPID, sessionPIDProp);
prop_const_generator(long long, IMachine, lastStateChange, lastStateChangeProp);
prop_const_generator(const std::string&, IMachine, stateFilePath, stateFilePathProp);
prop_const_generator(const std::string&, IMachine, logFolder, logFolderProp);
prop_const_generator(unsigned long, IMachine, snapshotCount, snapshotCountProp);
prop_const_generator(bool, IMachine, currentStateModified, currentStateModifiedProp);
prop_const_generator(const std::vector<std::shared_ptr<ISharedFolder>>, IMachine, sharedFolders, sharedFoldersProp);
prop_const_generator(bool, IMachine, clipboardFileTransfersEnabled, clipboardFileTransfersEnabledProp);
prop_const_generator(bool, IMachine, teleporterEnabled, teleporterEnabledProp);
prop_const_generator(unsigned long, IMachine, teleporterPort, teleporterPortProp);
prop_const_generator(const std::string&, IMachine, teleporterAddress, teleporterAddressProp);
prop_const_generator(const std::string&, IMachine, teleporterPassword, teleporterPasswordProp);
prop_const_generator(bool, IMachine, RTCUseUTC, RTCUseUTCProp);
prop_const_generator(bool, IMachine, IOCacheEnabled, IOCacheEnabledProp);
prop_const_generator(unsigned long, IMachine, IOCacheSize, IOCacheSizeProp);
prop_const_generator(bool, IMachine, tracingEnabled, tracingEnabledProp);
prop_const_generator(const std::string&, IMachine, tracingConfig, tracingConfigProp);
prop_const_generator(bool, IMachine, allowTracingToAccessVM, allowTracingToAccessVMProp);
prop_const_generator(bool, IMachine, autostartEnabled, autostartEnabledProp);
prop_const_generator(unsigned long, IMachine, autostartDelay, autostartDelayProp);
prop_const_generator(const std::string&, IMachine, defaultFrontend, defaultFrontendProp);
prop_const_generator(bool, IMachine, USBProxyAvailable, USBProxyAvailableProp);
prop_const_generator(const std::string&, IMachine, paravirtDebug, paravirtDebugProp);
prop_const_generator(const std::string&, IMachine, CPUProfile, CPUProfileProp);
prop_const_generator(const std::shared_ptr<ISnapshot>, IMachine, currentSnapshot, currentSnapshotProp);
prop_const_generator(const std::shared_ptr<IGraphicsAdapter>, IMachine, graphicsAdapter, graphicsAdapterProp);
prop_const_generator(const std::shared_ptr<IBIOSSettings>, IMachine, BIOSSettings, BIOSSettingsProp);
prop_const_generator(const std::shared_ptr<IRecordingSettings>, IMachine, recordingSettings, recordingSettingsProp);
prop_const_generator(const std::shared_ptr<IVirtualBoxErrorInfo>, IMachine, accessError, accessErrorProp);
prop_const_generator(const std::shared_ptr<IVRDEServer>, IMachine, VRDEServer, VRDEServerProp);
prop_const_generator(const std::shared_ptr<IUSBDeviceFilter>, IMachine, USBDeviceFilters, USBDeviceFiltersProp);
prop_const_generator(const std::shared_ptr<IAudioAdapter>, IMachine, audioAdapter, audioAdapterProp);
prop_const_generator(const std::vector<std::shared_ptr<IUSBController>>, IMachine, USBControllers, USBControllersProp);
prop_const_generator(const std::vector<std::string>, IMachine, groups, groupsProp);

VBox::FirmwareType IMachine::firmwareType(){
    _ns1__IMachine_USCOREgetFirmwareType req;
    req._USCOREthis = this->key();
    _ns1__IMachine_USCOREgetFirmwareTypeResponse resp;
}
//prop_generator_shared_ptr(const std::shared_ptr<IRecordingSettings>, IMachine, recordingSettings, IRecordingSettings, _ns1__IMachine_USCOREgetRecordingSettings);

