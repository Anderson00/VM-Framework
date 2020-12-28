#ifndef ISYSTEM_PROPERTIES_H
#define ISYSTEM_PROPERTIES_H

#include "IObject.h"
#include "IMedium.h"
#include "VBox.h"

class ISystemProperties : public IObject{
public:
    ISystemProperties(std::string key) : IObject(key) {}

    /*! \brief Returns the default I/O cache setting for the given storage controller
     *
     *  \param[in] controllerType The storage controller type to get the setting for.
     */
    bool getDefaultIoCacheSettingForStorageController(VBox::StorageControllerType controllerType);

    /*! \brief Returns list of all the supported device types (DeviceType) for the given type of storage bus.
     *
     *  \param[in] bus The storage bus type to get the value for.
     */
    std::vector<VBox::DeviceType> getDeviceTypesForStorageBus(VBox::StorageBus bus);

    /*! \brief Returns the maximum number of devices which can be attached to a port for the given storage bus.
     *
     *  \param[in] bus The storage bus type to get the value for.
     */
    unsigned long getMaxDevicesPerPortForStorageBus(VBox::StorageBus bus);

    /*! \brief Returns the maximum number of storage bus instances which can be configured for each VM. This corresponds to the number of storage controllers one can have. Value may depend on chipset type used.
     *
     *  \param[in] chipset The chipset type to get the value for.
     *  \param[in] bus The storage bus type to get the value for.
     */
     unsigned long getMaxInstancesOfStorageBus(VBox::ChipsetType chipset, VBox::StorageBus bus);

     /*! \brief Returns the maximum number of USB controller instances which can be configured for each VM. This corresponds to the number of USB controllers one can have. Value may depend on chipset type used.
      *
      * \param[in] chipset The chipset type to get the value for.
      * \param[in] type The USB controller type to get the value for.
      */
     unsigned long getMaxInstancesOfUSBControllerType(VBox::ChipsetType chipset, VBox::USBControllerType type);

     /*! \brief Maximum total number of network adapters associated with every IMachine instance.
      *
      * \param[in] chipset The chipset type to get the value for.
      */
     unsigned long getMaxNetworkAdapters(VBox::ChipsetType type);

     /*! \brief Maximum number of network adapters of a given attachment type, associated with every IMachine instance.
      *
      *  \param[in] chipset The chipset type to get the value for.
      *  \param[in] type Type of attachment.
      */
     unsigned long getMaxNetworkAdaptersOfType(VBox::ChipsetType chipset, VBox::NetworkAttachmentType type);

     /*! \brief Returns the maximum number of ports the given storage bus supports.
      *
      *  \param[in] bus The storage bus type to get the value for.
      */
     unsigned long getMaxPortCountForStorageBus(VBox::StorageBus bus);

    /*! \brief Returns the minimum number of ports the given storage bus supports.
     *
     *  \param[in] bus The storage bus type to get the value for.
     */
    unsigned long getMinPortCountForStorageBus(VBox::StorageBus bus);

    /*! \brief Returns the StorageBus enum value for a given storage controller type.
     *
     *  \param[in] storageControllerType The storage controller type to get the value for.
     */
    VBox::StorageBus getStorageBusForStorageControllerType(VBox::StorageControllerType storageControllerType);

    /*! \brief Returns whether the given storage controller supports hot-plugging devices.
     *
     *  \param[in] controllerType The storage controller to check the setting for.
     */
     bool getStorageControllerHotplugCapable(VBox::StorageControllerType storageControllerType);

     /*! \brief Returns the possible StorageControllerType enum values for a given storage bus.
      *
      * \param[in] storageBus The storage bus type to get the values for.
      */
     std::vector<VBox::StorageControllerType> getStorageControllerTypesForStorageBus(VBox::StorageBus storageBus);

private:

    //! Minimum guest system memory in Megabytes.
    unsigned long minGuestRAM;

    //! Maximum guest system memory in Megabytes.
    unsigned long maxGuestRAM;

    //! Minimum guest video memory in Megabytes.
    unsigned long minGuestVRAM;

    //! Maximum guest video memory in Megabytes.
    unsigned long maxGuestVRAM;

    //! Minimum CPU count.
    unsigned long minGuestCPUCount;

    //! Maximum CPU count.
    unsigned long maxGuestCPUCount;

    //! Maximum of monitors which could be connected.
    unsigned long maxGuestMonitors;

    //! Maximum size of a virtual disk image in bytes. Informational value, does not reflect the limits of any virtual disk image format.
    long long infoVDSize;

    //! Maximum number of serial ports associated with every IMachine instance.
    unsigned long serialPortCount;

    //! Maximum number of parallel ports associated with every IMachine instance.
    unsigned long parallelPortCount;

    //! Maximum device position in the boot order. This value corresponds to the total number of devices a machine can boot from, to make it possible to include all possible devices to the boot list. See also: IMachine::setBootOrder()
    unsigned long maxBootPosition;

    //! Indicates whether VirtualBox was built with raw-mode support. When this reads as False, the Enabled setting will be ignored and assumed to be True.
    bool rawModeSupported;

    //! List of all medium storage formats supported by this VirtualBox installation.
    std::vector<std::shared_ptr<IMedium>> mediumFormats;

    //! This value hold the default audio driver for the current system.
    VBox::AudioDriverType defaultAudioDriver;

    //! Supported bitmap formats which can be used with takeScreenShot and takeScreenShotToArray methods.
    std::vector<VBox::BitmapFormat> screenShotFormats;

    //! Returns an array of officially supported values for enum ParavirtProvider, in the sense of what is e.g. worth offering in the VirtualBox GUI.
    std::vector<VBox::ParavirtProvider> supportedParavirtProviders;

    //! Returns an array of officially supported values for enum ClipboardMode, in the sense of what is e.g. worth offering in the VirtualBox GUI.
    std::vector<VBox::ClipboardMode> supportedClipboardModes;

    //! Returns an array of officially supported values for enum DnDMode, in the sense of what is e.g. worth offering in the VirtualBox GUI.
    std::vector<VBox::DnDMode> supportedDnDModes;

    //! Returns an array of officially supported values for enum FirmwareType, in the sense of what is e.g. worth offering in the VirtualBox GUI.
    std::vector<VBox::FirmwareType> supportedFirmwareTypes;

    //! Returns an array of officially supported values for enum PointingHIDType, in the sense of what is e.g. worth offering in the VirtualBox GUI.
    std::vector<VBox::PointingHIDType> supportedPointingHIDTypes;

    //! Returns an array of officially supported values for enum KeyboardHIDType, in the sense of what is e.g. worth offering in the VirtualBox GUI.
    std::vector<VBox::KeyboardHIDType> supportedKeyboardHIDTypes;

    //! Returns an array of officially supported values for enum VFSType, in the sense of what is e.g. worth offering in the VirtualBox GUI.
    std::vector<VBox::VFSType> supportedVFSTypes;

    //! Returns an array of officially supported values for enum ImportOptions, in the sense of what is e.g. worth offering in the VirtualBox GUI.
    std::vector<VBox::ImportOptions> supportedImportOptions;

    //! Returns an array of officially supported values for enum ExportOptions, in the sense of what is e.g. worth offering in the VirtualBox GUI.
    std::vector<VBox::ExportOptions> supportedExportOptions;

    //! Returns an array of officially supported values for enum RecordingAudioCodec, in the sense of what is e.g. worth offering in the VirtualBox GUI.
    std::vector<VBox::RecordingAudioCodec> supportedRecordingAudioCodecs;

    //! Returns an array of officially supported values for enum RecordingVideoCodec, in the sense of what is e.g. worth offering in the VirtualBox GUI.
    std::vector<VBox::RecordingVideoCodec> supportedRecordingVideoCodecs;

    //! Returns an array of officially supported values for enum RecordingVideoScalingMethod, in the sense of what is e.g. worth offering in the VirtualBox GUI.
    std::vector<VBox::RecordingVideoScalingMethod> supportedRecordingVSMethods;

    //! Returns an array of officially supported values for enum RecordingVideoRateControlMode, in the sense of what is e.g. worth offering in the VirtualBox GUI.
    std::vector<VBox::RecordingVideoRateControlMode> supportedRecordingVRCModes;

    //! Returns an array of officially supported values for enum GraphicsControllerType, in the sense of what is e.g. worth offering in the VirtualBox GUI.
    std::vector<VBox::GraphicsControllerType> supportedGraphicsControllerTypes;

    //! Returns an array of officially supported values for enum CloneOptions, in the sense of what is e.g. worth offering in the VirtualBox GUI.
    std::vector<VBox::CloneOptions> supportedCloneOptions;

    //! Returns an array of officially supported values for enum AutostopType, in the sense of what is e.g. worth offering in the VirtualBox GUI.
    std::vector<VBox::AutostopType> supportedAutostopTypes;

    //! Returns an array of officially supported values for enum VMProcPriority, in the sense of what is e.g. worth offering in the VirtualBox GUI.
    std::vector<VBox::VMProcPriority> supportedVMProcPriorities;

    //! Returns an array of officially supported values for enum NetworkAttachmentType, in the sense of what is e.g. worth offering in the VirtualBox GUI.
    std::vector<VBox::NetworkAttachmentType> supportedNetworkAttachmentTypes;

    //! Returns an array of officially supported values for enum NetworkAdapterType, in the sense of what is e.g. worth offering in the VirtualBox GUI.
    std::vector<VBox::NetworkAdapterType> supportedNetworkAdapterTypes;

    //! Returns an array of officially supported values for enum PortMode, in the sense of what is e.g. worth offering in the VirtualBox GUI.
    std::vector<VBox::PortMode> supportedPortModes;

    //! Returns an array of officially supported values for enum UartType, in the sense of what is e.g. worth offering in the VirtualBox GUI.
    std::vector<VBox::UartType> supportedUartTypes;

    //! Returns an array of officially supported values for enum USBControllerType, in the sense of what is e.g. worth offering in the VirtualBox GUI.
    std::vector<VBox::USBControllerType> supportedUSBControllerTypes;

    //! Returns an array of officially supported values for enum AudioDriverType, in the sense of what is e.g. worth offering in the VirtualBox GUI.
    std::vector<VBox::AudioDriverType> supportedAudioDriverTypes;

    //! Returns an array of officially supported values for enum AudioControllerType, in the sense of what is e.g. worth offering in the VirtualBox GUI.
    std::vector<VBox::AudioControllerType> supportedAudioControllerTypes;

    //! Returns an array of officially supported values for enum StorageBus, in the sense of what is e.g. worth offering in the VirtualBox GUI.
    std::vector<VBox::StorageBus> supportedStorageBuses;

    //! Returns an array of officially supported values for enum StorageControllerType, in the sense of what is e.g. worth offering in the VirtualBox GUI.
    std::vector<VBox::StorageControllerType> supportedStorageControllerTypes;

    //! Returns an array of officially supported values for enum ChipsetType, in the sense of what is e.g. worth offering in the VirtualBox GUI.
    std::vector<VBox::ChipsetType> supportedChipsetTypes;

    //Read-Write

    //! Exclusive use of hardware virtualization by VirtualBox. When enabled, VirtualBox assumes it can obtain full and exclusive access to the VT-x or AMD-V feature of the host. To share hardware virtualization with other hypervisors, this property must be disabled.
    bool exclusiveHwVirt;

    //! Full path to the default directory used to create new or open existing machines when a machine settings file name contains no path.
    std::string defaultMachineFolder;

    //! Specifies the logging level in current use by VirtualBox.
    std::string loggingLevel;

    //! Identifier of the default medium format used by VirtualBox.
    std::string defaultHardDiskFormat;

    //! Issue a warning if the free disk space is below (or in some disk intensive operation is expected to go below) the given size in bytes.
    long long freeDiskSpaceWarning;

    //! Issue a warning if the free disk space is below (or in some disk intensive operation is expected to go below) the given percentage.
    unsigned long freeDiskSpacePercentWarning;

    //! Issue an error if the free disk space is below (or in some disk intensive operation is expected to go below) the given size in bytes.
    long long freeDiskSpaceError;

    //! Issue an error if the free disk space is below (or in some disk intensive operation is expected to go below) the given percentage.
    unsigned long freeDiskSpacePercentError;

    //! Library that provides authentication for Remote Desktop clients. The library is used if a virtual machine’s authentication type is set to “external” in the VM RemoteDisplay configuration.
    std::string VRDEAuthLibrary;

    //! Library that provides authentication for webservice clients.
    std::string webServiceAuthLibrary;

    //! The name of the extension pack providing the default VRDE.
    std::string defaultVRDEExtPack;

    //! This value specifies how many old release log files are kept.
    unsigned long logHistoryCount;

    //! The path to the autostart database. Depending on the host this might be a filesystem path or something else.
    std::string autostartDatabasePath;

    //! The path to the default Guest Additions ISO image. Can be empty if the location is not known in this installation.
    std::string defaultAdditionsISO;

    //! Selects which VM frontend should be used by default when launching a VM through the IMachine::launchVMProcess() method.
    std::string defaultFrontend;

    //! The proxy mode setting: System, NoProxy or Manual.
    VBox::ProxyMode proxyMode;

    //! Proxy server URL for the Manual proxy mode. The format is: [{type}“://“][{userid}[@{password}]:]{server}[“:“{port}]
    std::string proxyURL;

};

#endif