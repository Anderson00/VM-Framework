#include "IVirtualBox.h"

prop_generator(const std::string&, IVirtualBox, version, _ns1__IVirtualBox_USCOREgetVersion);
prop_generator(const std::string&, IVirtualBox, versionNormalized, _ns1__IVirtualBox_USCOREgetVersionNormalized);
prop_generator(unsigned long, IVirtualBox,revision, _ns1__IVirtualBox_USCOREgetRevision);
prop_generator(const std::string&, IVirtualBox, packageType, _ns1__IVirtualBox_USCOREgetPackageType);
prop_generator(const std::string&, IVirtualBox, APIVersion, _ns1__IVirtualBox_USCOREgetAPIVersion);
prop_generator(LONG64, IVirtualBox, APIRevision, _ns1__IVirtualBox_USCOREgetAPIRevision);
prop_generator(const std::string&, IVirtualBox, homeFolder, _ns1__IVirtualBox_USCOREgetHomeFolder);
prop_generator(const std::string&, IVirtualBox, settingsFilePath, _ns1__IVirtualBox_USCOREgetSettingsFilePath);
prop_generator_shared_ptr(const std::shared_ptr<IHost>, IVirtualBox, host, IHost, _ns1__IVirtualBox_USCOREgetHost);
prop_generator_shared_ptr(const std::shared_ptr<ISystemProperties>, IVirtualBox, systemProperties, ISystemProperties, _ns1__IVirtualBox_USCOREgetSystemProperties);
prop_generator_shared_ptr(const std::shared_ptr<IPerformanceCollector>, IVirtualBox, performaceCollector, IPerformanceCollector, _ns1__IVirtualBox_USCOREgetPerformanceCollector);
prop_generator_vector_shared_ptr(const std::vector<std::shared_ptr<IMachine>>, IVirtualBox, machines, IMachine, _ns1__IVirtualBox_USCOREgetMachines);
prop_generator_vector_string(const std::vector<std::string>, IVirtualBox, machineGroups, _ns1__IVirtualBox_USCOREgetMachineGroups);
prop_generator_vector_shared_ptr(const std::vector<std::shared_ptr<IMedium>>, IVirtualBox, hardDisks, IMedium, _ns1__IVirtualBox_USCOREgetHardDisks);
prop_generator_vector_shared_ptr(const std::vector<std::shared_ptr<IMedium>>, IVirtualBox, DVDImages, IMedium, _ns1__IVirtualBox_USCOREgetDVDImages);
prop_generator_vector_shared_ptr(const std::vector<std::shared_ptr<IMedium>>, IVirtualBox, floppyImages, IMedium, _ns1__IVirtualBox_USCOREgetFloppyImages);
prop_generator_vector_shared_ptr(const std::vector<std::shared_ptr<IProgress>>, IVirtualBox, progressOperations, IProgress, _ns1__IVirtualBox_USCOREgetProgressOperations);
prop_generator_vector_shared_ptr(const std::vector<std::shared_ptr<ISharedFolder>>, IVirtualBox, sharedFolders, ISharedFolder, _ns1__IVirtualBox_USCOREgetSharedFolders)
prop_generator_vector_shared_ptr(const std::vector<std::shared_ptr<IDHCPServer>>, IVirtualBox, DHCPServers, IDHCPServer, _ns1__IVirtualBox_USCOREgetDHCPServers);
prop_generator_vector_shared_ptr(const std::vector<std::shared_ptr<INATNetwork>>, IVirtualBox, NATNetworks, INATNetwork, _ns1__IVirtualBox_USCOREgetNATNetworks);
prop_generator_vector_shared_ptr(const std::vector<std::shared_ptr<ICloudNetwork>>, IVirtualBox, cloudNetworks, ICloudNetwork , _ns1__IVirtualBox_USCOREgetCloudNetworks);
prop_generator_vector_string(const std::vector<std::string>, IVirtualBox, internalNetworks, _ns1__IVirtualBox_USCOREgetInternalNetworks);
prop_generator_vector_string(const std::vector<std::string>, IVirtualBox, genericNetworkDrivers, _ns1__IVirtualBox_USCOREgetGenericNetworkDrivers);
prop_generator_shared_ptr(const std::shared_ptr<ICloudProviderManager>, IVirtualBox, cloudProviderManager, ICloudProviderManager, _ns1__IVirtualBox_USCOREgetCloudProviderManager);

/* //TODO: Caso epecial, returnval é uma struct propria.
prop_generator_vector_shared_ptr(const std::vector<std::shared_ptr<IGuestOSType>>, IVirtualBox, guestOSTypes, IGuestOSType, _ns1__IVirtualBox_USCOREgetGuestOSType);

const std::vector<std::shared_ptr<IGuestOSType> IVirtualBox::guestOSTypes() {
    _ns1__IVirtualBox_USCOREgetGuestOSTypes req;
    req._USCOREthis = this->key();
    _ns1__IVirtualBox_USCOREgetGuestOSTypesResponse resp;

    int result = soap_call___ns1__IVirtualBox_USCOREgetGuestOSTypes(this->soapClient()->soap(), this->soapClient()->endpoint().c_str(), nullptr, &req, resp);
    if(result == SOAP_OK){
        //resp.
    }else{

    }
}
*/

//Const Properties
prop_const_generator(const std::string&, IVirtualBox, version, versionProp);
prop_const_generator(const std::string&, IVirtualBox, versionNormalized, versionNormalizedProp);
prop_const_generator(unsigned long, IVirtualBox, revision, revisionProp);
prop_const_generator(const std::string&, IVirtualBox, packageType, packageTypeProp);
prop_const_generator(const std::string&, IVirtualBox, APIVersion, APIVersionProp);
prop_const_generator(LONG64, IVirtualBox, APIRevision, APIRevisionProp);
prop_const_generator(const std::string&, IVirtualBox, homeFolder, homeFolderProp);
prop_const_generator(const std::string&, IVirtualBox, settingsFilePath, settingsFilePathProp);
prop_const_generator(const std::shared_ptr<IHost>, IVirtualBox, host, hostProp);
prop_const_generator(const std::shared_ptr<ISystemProperties>, IVirtualBox, systemProperties, systemPropertiesProp);
prop_const_generator(const std::vector<std::shared_ptr<IMachine>>, IVirtualBox, machines, machinesProp);
prop_const_generator(const std::vector<std::string>, IVirtualBox, machineGroups, machineGroupsProp);
prop_const_generator(const std::vector<std::shared_ptr<IMedium>>, IVirtualBox, hardDisks, hardDisksProp);
prop_const_generator(const std::vector<std::shared_ptr<IMedium>>, IVirtualBox, DVDImages, DVDImagesProp);
prop_const_generator(const std::vector<std::shared_ptr<IMedium>>, IVirtualBox, floppyImages, floppyImagesProp);
prop_const_generator(const std::vector<std::shared_ptr<IProgress>>, IVirtualBox, progressOperations, progressOperationsProp);
prop_const_generator(const std::vector<std::shared_ptr<ISharedFolder>>, IVirtualBox, sharedFolders, sharedFoldersProp);
prop_const_generator(const std::shared_ptr<IPerformanceCollector>, IVirtualBox, performaceCollector, performaceCollectorProp);
prop_const_generator(const std::vector<std::shared_ptr<IDHCPServer>>, IVirtualBox, DHCPServers, DHCPServersProp);
prop_const_generator(const std::vector<std::shared_ptr<INATNetwork>>, IVirtualBox, NATNetworks, NATNetworksProp);
prop_const_generator(const std::vector<std::string>, IVirtualBox, internalNetworks, internalNetworksProp);
prop_const_generator(const std::vector<std::string>, IVirtualBox, genericNetworkDrivers, genericNetworkDriversProp);
prop_const_generator(const std::vector<std::shared_ptr<ICloudNetwork>>, IVirtualBox, cloudNetworks, cloudNetworksProp);
prop_const_generator(const std::shared_ptr<ICloudProviderManager>, IVirtualBox, cloudProviderManager, cloudProviderManagerProp);