#ifndef IVIRTUAL_BOX_H
#define IVIRTUAL_BOX_H

#include "exceptions/soap_exception.h"
#include "utils.h"
#include "VBox.h"
#include "IObject.h"
#include "IAppliance.h"
#include "ICloudNetwork.h"
#include "IDHCPServer.h"
#include "IMachine.h"
#include "IMedium.h"
#include "INATNetwork.h"
#include "IUnattended.h"
#include "IGuestOSType.h"
#include "IHost.h"
#include "ISystemProperties.h"
#include "IProgress.h"
#include "ISharedFolder.h"
#include "IPerformanceCollector.h"
#include "IEventSource.h"
#include "ICloudProviderManager.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>

class IVirtualBox : public IObject{
public:
    IVirtualBox(std::string vBoxKey) : IObject(vBoxKey) {}

    /*! \brief Check if this VirtualBox installation has a firmware of the given type available, either systemwide or per-user. Optionally, this may return a hint where this firmware can be downloaded from.
        
        \param[in]  firmwareType Type of firmware to check
        \param[in]  version      Expected version number, usually empty string (presently ignored).
        \param[out] url          Suggested URL to download this firmware from.
        \param[out] file         Filename of firmware, only valid if result == TRUE
    */    
    bool checkFirmwarePresent(
            VBox::FirmwareType firmwareType, 
            std::string version,
            std::string url,
            std::string file);

    /*! \brief
        Returns a recommended full path of the settings file name for a new virtual machine.
        This API serves two purposes:
        <ul>
            <li>
                It gets called by createMachine() if null or empty string (which is recommended) is specified for the settingsFile argument there, which means that API should use a recommended default file name.
            </li>
            <li>
                It can be called manually by a client software before creating a machine, e.g. if that client
                wants to pre-create the machine directory to create virtual hard disks in that directory
                together with the new machine settings file. In that case, the file name should be stripped
                from the full settings file path returned by this function to obtain the machine directory.
            </li>
        </ul>
        See IMachine::name and createMachine() for more details about the machine name.
        groupName defines which additional subdirectory levels should be included. It must be either a
        valid group name or null or empty string which designates that the machine will not be related
        to a machine group.
        If baseFolder is a null or empty string (which is recommended), the default machine settings folder (see ISystemProperties::defaultMachineFolder) will be used as a base folder for the
        created machine, resulting in a file name like “/home/user/VirtualBox VMs/name/name.vbox”.
        Otherwise the given base folder will be used.
        This method does not access the host disks. In particular, it does not check for whether a
        machine with this name already exists.
    *   
    *   \param[in] name         Suggested machine name.
    *   \param[in] group        Machine group name for the new machine or machine group. It is used to determine the right subdirectory
    *   \param[in] createFlags  Machine creation flags, see createMachine() (optional).
    *   \param[in] baseFolder   Base machine folder (optional).
    */
    std::string composeMachineFilename(
            std::string name,
            std::string group,
            std::string createFlags,
            std::string baseFolder);

    /*!
    *   \brief 
        Creates a new appliance object, which represents an appliance in the Open Virtual Machine
        Format (OVF). This can then be used to import an OVF appliance into VirtualBox or to export
        machines as an OVF appliance; see the documentation for IAppliance for details.
    */
    IAppliance createAppliance();

    /*!
    *   \param[in] networkName Network name
    */ 
    ICloudNetwork createCloudNetwork(std::string networkName);

    /*! \brief Creates a DHCP server settings to be used for the given internal network name If this method fails, the following error codes may be reported: • E_INVALIDARG: Host network interface name already exists.
    *
    *   \param[in] name server name
    */
    IDHCPServer createDHCPServer(std::string name);

    /*! \brief 
        Creates a new virtual machine by creating a machine settings file at the given location.
        VirtualBox machine settings files use a custom XML dialect. Starting with VirtualBox 4.0,
        a “.vbox” extension is recommended, but not enforced, and machine files can be created at
        arbitrary locations.
        However, it is recommended that machines are created in the default
        machine folder (e.g. “/home/user/VirtualBox VMs/name/name.vbox”; see
        ISystemProperties::defaultMachineFolder). If you specify null or empty string (which is
        recommended) for the settingsFile argument, composeMachineFilename() is called automatically to have such a recommended name composed based on the machine name given in
        the name argument and the primary group.
        If the resulting settings file already exists, this method will fail, unless the forceOverwrite flag
        is set.
        The new machine is created unregistered, with the initial configuration set according to the
        specified guest OS type. A typical sequence of actions to create a new virtual machine is as
        follows:
        <ol>
            <li>
                Call this method to have a new machine created. The returned machine object will be “mutable” allowing to change any machine property.
            </li>
            <li>
                Configure the machine using the appropriate attributes and methods.
            </li>
            <li>
                Call IMachine::saveSettings() to write the settings to the machine’s XML settings file. The configuration of the newly created machine will not be saved to disk until this method is called.
            </li>
            <li>
                Call registerMachine() to add the machine to the list of machines known to VirtualBox.
            </li>
        </ol>
        The specified guest OS type identifier must match an ID of one of known guest OS types listed in the guestOSTypes[] array.
    *
    *   \param[in] settingsFile Fully qualified path where the settings file should be created, empty string or null for a default folder and file based on the name argument and the primary group. (see composeMachineFilename()).
    *   \param[in] name         Machine name.
    *   \param[in] groups       Array of group names. null or an empty array have the same meaning as an array with just the empty string or "/", i.e. create a machine without group association.
    *   \param[in] osTypeId     Guest OS Type ID.
    *   \param[in] flags        Additional property parameters, passed as a comma-separated list of “name=value” type entries. The following ones are recognized: forceOverwrite=1 to overwrite an existing machine settings file, UUID=<uuid> to specify a machine UUID and directoryIncludesUUID=1 to switch to a special VM directory naming scheme which should not be used unless necessary.
    */
    std::shared_ptr<IMachine> createMachine(
        std::string settingsFile,
        std::string name,
        std::vector<std::string> groups,
        std::string osTypeId,
        std::string flags);

    /*! \brief 
        Creates a new base medium object that will use the given storage format and location for
        medium data.
        The actual storage unit is not created by this method. In order to do it, and before you are able
        to attach the created medium to virtual machines, you must call one of the following methods to
        allocate a format-specific storage unit at the specified location:
        <ul>
            <li>
                IMedium::createBaseStorage()
            </li>
            <li>
                IMedium::createDiffStorage()
            </li>
        </ul>
        Some medium attributes, such as IMedium::id, may remain uninitialized until the medium
        storage unit is successfully created by one of the above methods.
        Depending on the given device type, the file at the storage location must be in one of the media
        formats understood by VirtualBox:
        <ul>
            <li>
                With a “HardDisk” device type, the file must be a hard disk image in one of the formats
                supported by VirtualBox (see ISystemProperties::mediumFormats[]). After the storage unit
                is successfully created and this method succeeds, if the medium is a base medium, it will
                be added to the hardDisks[] array attribute.
            </li>
            <li>
                With a “DVD” device type, the file must be an ISO 9960 CD/DVD image. After this method
                succeeds, the medium will be added to the DVDImages[] array attribute.
            </li>
            <li>
                With a “Floppy” device type, the file must be an RAW floppy image. After this method
                succeeds, the medium will be added to the floppyImages[] array attribute.
            </li>
        </ul>
        The list of all storage formats supported by this VirtualBox installation can be obtained using
        ISystemProperties::mediumFormats[]. If the format attribute is empty or null then the default
        storage format specified by ISystemProperties::defaultHardDiskFormat will be used for disks r
        creating a storage unit of the medium.
        Note that the format of the location string is storage format specific. See IMedium::location
        and IMedium for more details.
        If this method fails, the following error codes may be reported:
        <ul>
            <li>
                VBOX_E_OBJECT_NOT_FOUND: format identifier is invalid. See ISystemProperties::mediumFormats[].
            </li>
            <li>
                VBOX_E_FILE_ERROR: location is a not valid file name (for file-based formats only).
            </li>
        </ul>
    *
    *   \param[in] format           Identifier of the storage format to use for the new medium.
    *   \param[in] location         Location of the storage unit for the new medium.
    *   \param[in] accessMode       Whether to open the image in read/write or read-only mode. For a “DVD” device type, this is ignored and read-only mode is always assumed.
    *   \param[in] aDeviceTypeType  Must be one of “HardDisk”, “DVD” or “Floppy”.
    */
    IMedium createMedium(
        std::string format,
        std::string location,
        VBox::AccessMode accessMode,
        VBox::DeviceType aDeviceTypeType
    );

    /*!
    *   \param[in] networkName
    */
    INATNetwork createNATNetwork(std::string networkName);

    /*! \brief
        Creates a new global shared folder by associating the given logical name with the given host
        path, adds it to the collection of shared folders and starts sharing it. Refer to the description of
        ISharedFolder to read more about logical names. Note: In the current implementation, this operation is not implemented.
    *
    *   \param[in] name           Unique logical name of the shared folder.
    *   \param[in] hostPath       Full path to the shared folder in the host file system.
    *   \param[in] writable       Whether the share is writable or readonly
    *   \param[in] automount      Whether the share gets automatically mounted by the guest or not.
    *   \param[in] autoMountPoint Where the guest should automatically mount the folder, if possible. For Windows and OS/2 guests this should be a drive letter, while other guests it should be a absolute directory.
    */
    void createSharedFolder(
        std::string name,
        std::string hostPath,
        bool writable,
        bool automount,
        std::string autoMountPoint
    );

    /*! \brief
        Creates a new IUnattended guest installation object. This can be used to analyze an installation
        ISO to create and configure a new machine for it to be installed on. It can also be used to
        (re)install an existing machine.
    *
    */
    IUnattended createUnattendedInstaller();

    /*!
    *   \param[in] networkName
    */
    ICloudNetwork findCloudNetworkByName(std::string networkName);

    /*! \brief
        Searches a DHCP server settings to be used for the given internal network name
        If this method fails, the following error codes may be reported:
        <ul>
            <li>
                E_INVALIDARG: Host network interface name already exists.
            </li>
        </ul>
    *   \param[in] name
    */
    IDHCPServer findDHCPServerByNetworkName(std::string name);

    /*! \brief
        Attempts to find a virtual machine given its name or UUID.
        <b>Note:</b> Inaccessible machines cannot be found by name, only by UUID, because their
        name cannot safely be determined.
        If this method fails, the following error codes may be reported:
        <ul>
            <li>
                VBOX_E_OBJECT_NOT_FOUND: Could not find registered machine matching nameOrId.
            </li>
        </ul>
    *   \param[in] nameOrId What to search for. This can either be the UUID or the name of a virtual machine.
    */
    std::shared_ptr<IMachine> findMachine(std::wstring nameOrId);

    /*!
    *   \param[in] networkName
    */
    INATNetwork findNATNetworkByName(std::wstring networkName);
        
    /*! \brief
        eturns associated global extra data.
        If the requested data key does not exist, this function will succeed and return an empty string
        in the value argument.
        If this method fails, the following error codes may be reported:
        <ul>
            <li>
                VBOX_E_FILE_ERROR: Settings file not accessible.
            </li>
            <li>
                VBOX_E_XML_ERROR: Could not parse the settings file.
            </li>
        </ul>
    *   \param[in] key Name of the data key to get.
    */
    std::wstring getExtraData(std::wstring key);

    /*! \brief Returns an array representing the global extra data keys which currently have values defined.
    */
    std::vector<std::wstring> getExtraDataKeys();

    /*! \brief 
        Returns an object describing the specified guest OS type.
        The requested guest OS type is specified using a string which is a mnemonic identifier of the
        guest operating system, such as "win31" or "ubuntu". The guest OS type ID of a particular
        virtual machine can be read or set using the IMachine::OSTypeId attribute.
        The guestOSTypes[] collection contains all available guest OS type objects. Each object has an
        IGuestOSType::id attribute which contains an identifier of the guest OS this object describes.
        While this function returns an error for unknown guest OS types, they can be still used without
        serious problems (if one accepts the fact that there is no default VM config information).
        If this method fails, the following error codes may be reported:
        <ul>
            <li>
                E_INVALIDARG: id is not a valid Guest OS type.
            </li>
        </ul>
    *
    *   \param[in] id Guest OS type ID string
    */
    IGuestOSType getGuestOSType(std::wstring id);

    /*! \brief Gets the state of several machines in a single operation.
    *   
    *   \param[in] machines Array with the machine references.
    */
    std::vector<VBox::MachineState> getMachineStates(std::vector<std::shared_ptr<IMachine>> machines);

    /*! \brief Gets all machine references which are in one of the specified groups.
    *
    *   \param[in] groups What groups to match. The usual group list rules apply, i.e. passing an empty list will match VMs in the toplevel group, likewise the empty string.
    */
    std::vector<std::shared_ptr<IMachine>> getMachinesByGroups(std::vector<std::wstring> groups);

    /*! \brief 
        Opens a virtual machine from the existing settings file. The opened machine remains unregistered until you call registerMachine().
        The specified settings file name must be fully qualified. The file must exist and be a valid
        machine XML settings file whose contents will be used to construct the machine object.
    *
    *   \param settingsFile Name of the machine settings file.
    */
    std::shared_ptr<IMachine> openMachine(std::wstring settinsFile);

    /*! \brief
        Finds existing media or opens a medium from an existing storage location.
        Once a medium has been opened, it can be passed to other VirtualBox methods, in particular
        to IMachine::attachDevice().
        Depending on the given device type, the file at the storage location must be in one of the media
        formats understood by VirtualBox:
        <ul>
            <li>
                With a “HardDisk” device type, the file must be a hard disk image in one of the formats
                supported by VirtualBox (see ISystemProperties::mediumFormats[]). After this method
                succeeds, if the medium is a base medium, it will be added to the hardDisks[] array attribute.
            </li>
            <li>
                With a “DVD” device type, the file must be an ISO 9960 CD/DVD image. After this method
                succeeds, the medium will be added to the DVDImages[] array attribute.
            </li>
            <li>
                With a “Floppy” device type, the file must be an RAW floppy image. After this method
                succeeds, the medium will be added to the floppyImages[] array attribute.
            </li>
        </ul>

        After having been opened, the medium can be re-found by this method and can be attached to
        virtual machines. See IMedium for more details.
        The UUID of the newly opened medium will either be retrieved from the storage location, if
        the format supports it (e.g. for hard disk images), or a new UUID will be randomly generated
        (e.g. for ISO and RAW files). If for some reason you need to change the medium’s UUID, use
        IMedium::setIds().
        If a differencing hard disk medium is to be opened by this method, the operation will succeed only if its parent medium and all ancestors, if any, are already known to this VirtualBox
        installation (for example, were opened by this method before).
        This method attempts to guess the storage format of the specified medium by reading medium
        data at the specified location.
        If accessMode is ReadWrite (which it should be for hard disks and floppies), the image is
        opened for read/write access and must have according permissions, as VirtualBox may actually
        write status information into the disk’s metadata sections.
        Note that write access is required for all typical hard disk usage in VirtualBox, since VirtualBox
        may need to write metadata such as a UUID into the image. The only exception is opening a
        source image temporarily for copying and cloning (see IMedium::cloneTo() when the image will
        be closed again soon.
        The format of the location string is storage format specific. See IMedium::location and
        IMedium for more details.
        If this method fails, the following error codes may be reported:
        <ul>
            <li>
                VBOX_E_FILE_ERROR: Invalid medium storage file location or could not find the medium at the specified location.
            </li>
            <li>
                VBOX_E_IPRT_ERROR: Could not get medium storage format.
            </li>
            <li>
                E_INVALIDARG: Invalid medium storage format.
            </li>
            <li>
                VBOX_E_INVALID_OBJECT_STATE: Medium has already been added to a media registry.
            </li>
        </ul>
    *
    *   \param[in] location     Location of the storage unit that contains medium data in one of the supported storage formats.
    *   \param[in] deviceType   Must be one of “HardDisk”, “DVD” or “Floppy”.
    *   \param[in] accessMode   Whether to open the image in read/write or read-only mode. For a “DVD” device type, this is ignored and read-only mode is always assumed.
    *   \param[in] forceNewUuid Allows the caller to request a completely new medium UUID for the image which is to be opened. Useful if one intends to open an exact copy of a previously opened image, as this would normally fail due to the duplicate UUID.
    */
    IMedium openMedium(
        std::wstring location,
        VBox::DeviceType deviceType,
        VBox::AccessMode accessMode,
        bool forceNewUuid
    );

    /*! \brief
        Registers the machine previously created using createMachine() or opened using
        openMachine() within this VirtualBox installation. After successful method invocation, the
        IMachineRegisteredEvent event is fired. Note: This method implicitly calls IMachine::saveSettings() to save all current machine
        settings before registering it. If this method fails, the following error codes may be reported:
        <ul>
            <li>
                VBOX_E_OBJECT_NOT_FOUND: No matching virtual machine found.
            </li>
            <li>
                VBOX_E_INVALID_OBJECT_STATE: Virtual machine was not created within this VirtualBox instance.
            </li>
        </ul>
    *
    *   \param machine
    */
    void registerMachine(std::shared_ptr<IMachine> machine);

    /*! \brief
    *
    *   \param network
    */
    void removeCloudNetwork(ICloudNetwork network);

    /*! \brief Removes the DHCP server settings If this method fails, the following error codes may be reported:
        //TODO: Exceptions: E_INVALIDARG: Host network interface name already exists. 
    *
    *   \param server DHCP server settings to be removed.
    */
    void removeDHCPServer(IDHCPServer server);

    /*! \brief
    *
    *   \param network
    */
    void removeNATNetwork(INATNetwork network);

    /*! \brief Removes the global shared folder with the given name previously created by createSharedFolder() from the collection of shared folders and stops sharing it.
    *   \param name Logical name of the shared folder to remove.
    */
    void removeSharedFolder(std::wstring name);

    /*! \brief 
        Sets associated global extra data. If you pass null or an empty string as a key value, the given key will be deleted.
        Note: Key must contain printable (non-control) UTF-8 characters only.
        If this method fails, the following error codes may be reported:
        //TODO: Exceptions:
        <ul>
            <li>
                VBOX_E_FILE_ERROR: Settings file not accessible.
            </li>
            <li>
                VBOX_E_XML_ERROR: Could not parse the settings file.
            </li>
            <li>
                E_ACCESSDENIED: Modification request refused.
            </li>
            <li>
                E_INVALIDARG: Key contains invalid characters.
            </li>
        </ul>
    *
    *   \param key Name of the data key to set.
    *   \param value Value to assign to the key.
    */
    void setExtraData(std::wstring key, std::wstring value);

    /*! \brief 
        Unlocks the secret data by passing the unlock password to the server. The server will cache
        the password for that machine.
        If this method fails, the following error codes may be reported:
        //TODO: Exceptions:
        <ul>
            <li>
                VBOX_E_INVALID_VM_STATE: Virtual machine is not mutable.
            </li>
        </ul>
    *
    *   \param password The cipher key.
    */
    void setSettingsSecret(std::wstring password);

    //Properties
    const std::string& version();
    const std::string& version()const;
    const std::string& versionNormalized();
    const std::string& versionNormalized()const;
    unsigned long revision();
    unsigned long revision()const;
    const std::string& packageType();
    const std::string& packageType()const;
    const std::string& APIVersion();
    const std::string& APIVersion()const;
    LONG64 APIRevision();
    LONG64 APIRevision()const;
    const std::string& homeFolder();
    const std::string& homeFolder()const;
    const std::string& settingsFilePath();
    const std::string& settingsFilePath()const;
    const std::shared_ptr<IHost> host();
    const std::shared_ptr<IHost> host()const;
    const std::shared_ptr<ISystemProperties> systemProperties();
    const std::shared_ptr<ISystemProperties> systemProperties()const;
    const std::vector<std::shared_ptr<IMachine>> machines();
    const std::vector<std::shared_ptr<IMachine>> machines()const;

    const std::vector<std::string> machineGroups();
    const std::vector<std::string> machineGroups()const;

    const std::vector<std::shared_ptr<IMedium>> hardDisks();
    const std::vector<std::shared_ptr<IMedium>> hardDisks()const;

    const std::vector<std::shared_ptr<IMedium>> DVDImages();
    const std::vector<std::shared_ptr<IMedium>> DVDImages()const;

    const std::vector<std::shared_ptr<IMedium>> floppyImages();
    const std::vector<std::shared_ptr<IMedium>> floppyImages()const;

    const std::vector<std::shared_ptr<IProgress>> progressOperations();
    const std::vector<std::shared_ptr<IProgress>> progressOperations()const;

    const std::vector<std::shared_ptr<IGuestOSType>> guestOSTypes();
    const std::vector<std::shared_ptr<IGuestOSType>> guestOSTypes()const;

    const std::vector<std::shared_ptr<ISharedFolder>> sharedFolders();
    const std::vector<std::shared_ptr<ISharedFolder>> sharedFolders()const;

    const std::shared_ptr<IPerformanceCollector> performaceCollector();
    const std::shared_ptr<IPerformanceCollector> performaceCollector()const;

    const std::vector<std::shared_ptr<IDHCPServer>> DHCPServers();
    const std::vector<std::shared_ptr<IDHCPServer>> DHCPServers()const;

    const std::vector<std::shared_ptr<INATNetwork>> NATNetworks();
    const std::vector<std::shared_ptr<INATNetwork>> NATNetworks()const;

    const std::vector<std::string> internalNetworks();
    const std::vector<std::string> internalNetworks()const;

    const std::vector<std::string> genericNetworkDrivers();
    const std::vector<std::string> genericNetworkDrivers()const;

    const std::vector<std::shared_ptr<ICloudNetwork>> cloudNetworks();
    const std::vector<std::shared_ptr<ICloudNetwork>> cloudNetworks()const;

    const std::shared_ptr<ICloudProviderManager> cloudProviderManager();
    const std::shared_ptr<ICloudProviderManager> cloudProviderManager()const;

private:
    std::string versionProp;
    std::string versionNormalizedProp;
    unsigned long revisionProp;
    std::string packageTypeProp;
    std::string APIVersionProp;
    LONG64 APIRevisionProp;
    std::string homeFolderProp;
    std::string settingsFilePathProp;
    std::shared_ptr<IHost> hostProp;
    std::shared_ptr<ISystemProperties> systemPropertiesProp;
    std::shared_ptr<IPerformanceCollector> performaceCollectorProp;
    std::vector<std::shared_ptr<IMachine>> machinesProp;
    std::vector<std::string> machineGroupsProp;
    std::vector<std::shared_ptr<IMedium>> hardDisksProp;
    std::vector<std::shared_ptr<IMedium>> DVDImagesProp;
    std::vector<std::shared_ptr<IMedium>> floppyImagesProp;
    std::vector<std::shared_ptr<IProgress>> progressOperationsProp;
    std::vector<std::shared_ptr<IGuestOSType>> guestOSTypesProp;
    std::vector<std::shared_ptr<ISharedFolder>> sharedFoldersProp;
    std::vector<std::shared_ptr<IDHCPServer>> DHCPServersProp;
    std::vector<std::shared_ptr<INATNetwork>> NATNetworksProp;
    IEventSource eventSourceProp;
    std::vector<std::string> internalNetworksProp;
    std::vector<std::string> genericNetworkDriversProp;
    std::vector<std::shared_ptr<ICloudNetwork>> cloudNetworksProp;
    std::shared_ptr<ICloudProviderManager> cloudProviderManagerProp;
};

#endif