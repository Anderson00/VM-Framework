#ifndef IHOST_H
#define IHOST_H

#include "IObject.h"
#include "IMedium.h"
#include "IHostUSBDevice.h"
#include "IUSBDeviceFilter.h"
#include "IHostNetworkInterface.h"
#include "IHostVideoInputDevice.h"
#include "IHostUpdate.h"
#include "IProgress.h"
#include "IHostUSBDeviceFilter.h"
#include "VBox.h"
#include "utils.h"

#include <vector>
#include <memory>

class IHost : public IObject{
public:
    IHost(std::string key) : IObject(key) {}

    /*! \brief Adds a new USB device source.
     *
     *  \param[in] backend The backend to use as the new device source.
     *  \param[in] id Unique ID to identify the source.
     *  \param[in] address Address to use, the format is dependent on the backend. For USB/IP backends for example the notation is host[:port].
     *  \param[in] propertyNames Array of property names for more detailed configuration. Not used at the moment.
     *  \param[in] propertyValues Array of property values for more detailed configuration. Not used at the moment.
     */
    void addUSBDeviceSource(
            std::string backend,
            std::string id,
            std::string address,
            std::vector<std::string> propertyNames[],
            std::vector<std::string> propertyValues[]);

    /*! \brief Creates a new adapter for Host Only Networking. If this method fails, the following error codes may be reported:
     *
     *  \param[out] hostInterface Created host interface object.
     */
    std::shared_ptr<IProgress> createHostOnlyNetworkInterface(IHostNetworkInterface hostInterface);

    /*! \brief Creates a new USB device filter. All attributes except the filter name are set to empty (any
                match), active is false (the filter is not active).
                The created filter can be added to the list of filters using insertUSBDeviceFilter().
                See also: USBDeviceFilters[]
     *
     *  \param[in] name Filter name. See IUSBDeviceFilter::name for more information.
     */
    std::shared_ptr<IUSBDeviceFilter> createUSBDeviceFilter(std::string name);

    /*! \brief Searches for a host DVD drive with the given name. If this method fails, the following error codes may be reported:
     *
     *  \param[in] name Name of the host drive to search for
     */
    std::shared_ptr<IMedium> findHostDVDDrive(std::string name);

    /*! \brief Searches for a host floppy drive with the given name. If this method fails, the following error codes may be reported:
     *
     *  \param[in] Name of the host floppy drive to search for
     */
    std::shared_ptr<IMedium> findHostFloppyDrive(std::string name);

    /*! \brief Searches through all host network interfaces for an interface with the given GUID.
     *
     *  \param[in] id GUID of the host network interface to search for.
     */
    std::shared_ptr<IHostNetworkInterface> findHostNetworkInterfaceById(std::string id);

    /*! \brief Searches through all host network interfaces for an interface with the given name.
     *
     *  \param[in] name Name of the host network interface to search for.
     */
    std::shared_ptr<IHostNetworkInterface> findHostNetworkInterfaceByName(std::string name);

    /*! \brief Searches through all host network interfaces for an interface with the given name.
     *
     *  \param[in] type type of the host network interfaces to search for.
     */
    std::vector<std::shared_ptr<IHostNetworkInterface>> findHostNetworkInterfacesOfType(VBox::HostNetworkInterfaceType type);

    /*! \brief Searches for a USB device with the given host address. See also: IUSBDevice::address If this method fails, the following error codes may be reported:
     *
     * \param[in] name Address of the USB device (as assigned by the host) to search for.
     */
    std::shared_ptr<IHostUSBDevice> findUSBDeviceByAddress(std::string name);

    /*! \brief Searches for a USB device with the given UUID. See also: IUSBDevice::id If this method fails, the following error codes may be reported:
     *
     * \param[in] id UUID of the USB device to search for.
     */
    std::shared_ptr<IHostUSBDevice> findUSBDeviceById(std::string id);

    /*! \brief Generates a valid Ethernet MAC address, 12 hexadecimal characters.
     *
     */
    std::string generateMACAddress();

    /*! \brief Returns the CPU cpuid information for the specified leaf.
     *
     *  \param[in] cpuId Identifier of the CPU. The CPU most be online.
     *  \param[in] leaf CPUID leaf index (eax).
     *  \param[in] subLeaf CPUID leaf sub index (ecx). This currently only applies to cache information on Intel CPUs. Use 0 if retrieving values for IMachine::setCPUIDLeaf().
     *  \param[out] valEax CPUID leaf value for register eax.
     *  \param[out] valEbx CPUID leaf value for register ebx.
     *  \param[out] valEcx CPUID leaf value for register ecx.
     *  \param[out] valEdx CPUID leaf value for register edx.
     *
     */
    void getProcessorCPUIDLeaf(
            unsigned long cpuId,
            unsigned long leaf,
            unsigned long subLeaf,
            unsigned long* valEax,
            unsigned long* valEbx,
            unsigned long* valEcx,
            unsigned long* valEdx);

    /*! \brief Query the model string of a specified host CPU.
     *
     *  \param[in] cpuId Identifier of the CPU.
     */
    std::string getProcessorDescription(unsigned long cpuId);

    /*! \brief Query whether a CPU feature is supported or not.
     *
     *  \param[in] feature CPU Feature identifier.
     */
    bool getProcessorFeature(VBox::ProcessorFeature feature);

    /*! \brief Query the (approximate) maximum speed of a specified host CPU in Megahertz.
     *
     *  \param[in] cpuId Identifier of the CPU.
     */
    unsigned long getProcessorSpeed(unsigned long cpuId);

    /*! \brief Inserts the given USB device to the specified position in the list of filters. Positions are numbered starting from 0 . If the specified position is equal to or greater than the number of elements in the list, the filter is added at the end of the collection.
     *
     *  \param[in] position Position to insert the filter to.
     *  \param[in] filter USB device filter to insert.
     */
    void insertUSBDeviceFilter(unsigned long position, std::shared_ptr<IHostUSBDeviceFilter> filter);

    /*! \brief Removes the given Host Only Networking interface. If this method fails, the following error codes may be reported:
     *
     *  \param[in] id Adapter GUID.
     */
    std::shared_ptr<IProgress> removeHostOnlyNetworkInterface(std::string id);

    /*! \brief Removes a USB device filter from the specified position in the list of filters. Positions are numbered starting from 0 . Specifying a position equal to or greater than the number of elements in the list will produce an error.
     *
     *  \param[in] position Position to remove the filter from.
     */
    void removeUSBDeviceFilter(unsigned long position);

    /*! \brief Removes a previously added USB device source.
     *
     *  \param[in] id The identifier used when the source was added.
     */
    void removeUSBDeviceSource(std::string id);


    //Properties
    std::vector<std::shared_ptr<IMedium>> DVDDrives();
    std::vector<std::shared_ptr<IMedium>> DVDDrives()const;
    std::vector<std::shared_ptr<IMedium>> floppyDrives();
    std::vector<std::shared_ptr<IMedium>> floppyDrives()const;
    std::vector<std::shared_ptr<IHostUSBDevice>> USBDevices();
    std::vector<std::shared_ptr<IHostUSBDevice>> USBDevices()const;
    std::vector<std::shared_ptr<IUSBDeviceFilter>> USBDeviceFilters();
    std::vector<std::shared_ptr<IUSBDeviceFilter>> USBDeviceFilters()const;
    std::vector<std::shared_ptr<IHostNetworkInterface>> networkInterfaces();
    std::vector<std::shared_ptr<IHostNetworkInterface>> networkInterfaces()const;
    std::vector<std::string> nameServers();
    std::vector<std::string> nameServers()const;
    std::string& domainName();
    std::string& domainName()const;
    std::vector<std::string> searchStrings();
    std::vector<std::string> searchStrings()const;
    unsigned long processorCount();
    unsigned long processorCount()const;
    unsigned long processorOnlineCount();
    unsigned long processorOnlineCount()const;
    unsigned long processorCoreCount();
    unsigned long processorCoreCount()const;
    unsigned long processorOnlineCoreCount();
    unsigned long processorOnlineCoreCount()const;
    unsigned long memorySize();
    unsigned long memorySize()const;
    unsigned long memoryAvailable();
    unsigned long memoryAvailable()const;
    std::string& operatingSystem();
    std::string& operatingSystem()const;
    std::string& OSVersion();
    std::string& OSVersion()const;
    long long UTCTime();
    long long UTCTime()const;
    bool acceleration3DAvailable();
    bool acceleration3DAvailable()const;
    std::vector<std::shared_ptr<IHostVideoInputDevice>> videoInputDevices();
    std::vector<std::shared_ptr<IHostVideoInputDevice>> videoInputDevices()const;
    std::shared_ptr<IHostUpdate> update();
    std::shared_ptr<IHostUpdate> update()const;

private:
    //! List of DVD drives available on the host.
    std::vector<std::shared_ptr<IMedium>> DVDDrivesProp;

    //! List of floppy drives available on the host.
    std::vector<std::shared_ptr<IMedium>> floppyDrivesProp;

    //! List of USB devices currently attached to the host. Once a new device is physically attached to the host computer, it appears in this list and remains there until detached.
    std::vector<std::shared_ptr<IHostUSBDevice>> USBDevicesProp;

    //! List of USB device filters in action.
    std::vector<std::shared_ptr<IUSBDeviceFilter>> USBDeviceFiltersProp;

    //! List of host network interfaces currently defined on the host.
    std::vector<std::shared_ptr<IHostNetworkInterface>> networkInterfacesProp;

    //! The list of nameservers registered in host’s name resolving system.
    std::vector<std::string> nameServersProp;

    //! Domain name used for name resolving.
    std::string domainNameProp;

    //! Search string registered for name resolving.
    std::vector<std::string> searchStringsProp;

    //! Number of (logical) CPUs installed in the host system.
    unsigned long processorCountProp;

    //! Number of (logical) CPUs online in the host system.
    unsigned long processorOnlineCountProp;

    //! Number of physical processor cores installed in the host system.
    unsigned long processorCoreCountProp;

    //! Number of physical processor cores online in the host system.
    unsigned long processorOnlineCoreCountProp;

    //! Amount of system memory in megabytes installed in the host system.
    unsigned long memorySizeProp;

    //! Available system memory in the host system.
    unsigned long memoryAvailableProp;

    //! Name of the host system’s operating system.
    std::string operatingSystemProp;

    //! Host operating system’s version string.
    std::string OSVersionProp;

    //! Returns the current host time in milliseconds since 1970-01-01 UTC.
    long long UTCTimeProp;

    //! Returns true when the host supports 3D hardware acceleration.
    bool acceleration3DAvailableProp;

    //! List of currently available host video capture devices.
    std::vector<std::shared_ptr<IHostVideoInputDevice>> videoInputDevicesProp;

    //! List of floppy drives available on the host.
    std::shared_ptr<IHostUpdate> updateProp;
};


#endif