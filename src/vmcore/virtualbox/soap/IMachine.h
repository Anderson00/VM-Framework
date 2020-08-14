#ifndef IMACHINE_H
#define IMACHINE_H

#include <iostream>
#include <vector>
#include <memory>

#include "IObject.h"
#include "VBox.h"
#include "exceptions/soap_exception.h"
#include "utils.h"
#include "IVirtualBoxErrorInfo.h"
#include "IGraphicsAdapter.h"
#include "IBIOSSettings.h"
#include "IRecordingSettings.h"
#include "IVRDEServer.h"
#include "IMediumAttachment.h"


/*! \brief 
    The IMachine interface represents a virtual machine, or guest, created in VirtualBox.
    This interface is used in two contexts. First of all, a collection of objects implementing this
    interface is stored in the IVirtualBox::machines[] attribute which lists all the virtual machines
    that are currently registered with this VirtualBox installation. Also, once a session has been
    opened for the given virtual machine (e.g. the virtual machine is running), the machine object
    associated with the open session can be queried from the session object; see ISession for details.
    The main role of this interface is to expose the settings of the virtual machine and provide
    methods to change various aspects of the virtual machine’s configuration. For machine objects
    stored in the IVirtualBox::machines[] collection, all attributes are read-only unless explicitly
    stated otherwise in individual attribute and method descriptions.
    In order to change a machine setting, a session for this machine must be opened using one
    of the lockMachine() or launchVMProcess() methods. After the machine has been successfully
    locked for a session, a mutable machine object needs to be queried from the session object and
    then the desired settings changes can be applied to the returned object using IMachine attributes
    and methods. See the ISession interface description for more information about sessions.
    Note that IMachine does not provide methods to control virtual machine execution (such as
    start the machine, or power it down) – these methods are grouped in a separate interface called
    IConsole.
    See also: ISession, IConsole
*
*/
class IMachine : public IObject{
public:
    IMachine(std::string key) : IObject(key){}

    const std::string& icon();
    const std::string& icon()const;

    bool accessible();
    bool accessible()const;

private:
    //! Associated parent object.
    //std::shared_ptr<IVirtualBox> parent;
    //! Overridden VM Icon details.
    std::string iconProp;
    //! Whether this virtual machine is currently accessible or not.
    bool accessibleProp;
    //! Error information describing the reason of machine inaccessibility.
    std::shared_ptr<IVirtualBoxErrorInfo> accessErrorProp;
    //! Error information describing the reason of machine inaccessibility.
    std::string nameProp;
    //! UUID of the virtual machine
    std::string idProp;
    //! Array of machine group names of which this machine is a member.
    std::vector<std::string> groupsProp;
    //! User-defined identifier of the Guest OS type.
    std::string OSTypeIdProp;
    //! Hardware version identifier. Internal use only for now
    std::string hardwareVersionProp;
    //! The UUID presented to the guest via memory tables, hardware and guest properties.
    std::string hardwareUUIDProp;
    //! Number of virtual CPUs in the VM.
    unsigned long CPUCountProp;
    //! This setting determines whether VirtualBox allows CPU hotplugging for this machine.
    bool CPUHotPlugEnabledProp;
    //! Means to limit the number of CPU cycles a guest can use.
    unsigned long CPUExecutionCapProp;
    //! Virtual CPUID portability level, the higher number the fewer newer or vendor specific CPU feature is reported to the guest (via the CPUID instruction).
    unsigned long CPUIDPortabilityLevelProp;
    //! System memory size in megabytes.
    unsigned long memorySizeProp;
    //! Memory balloon size in megabytes.
    unsigned long memoryBalloonSizeProp;
    //! This setting determines whether VirtualBox allows page fusion for this machine (64-bit hosts only).
    bool pageFusionEnabledProp;
    //! Graphics adapter object.
    std::shared_ptr<IGraphicsAdapter> graphicsAdapterProp;
    //! Object containing all BIOS settings.
    std::shared_ptr<IBIOSSettings> BIOSSettingsProp;
    //! Object containing all recording settings.
    std::shared_ptr<IRecordingSettings> recordingSettingsProp;
    //! Type of firmware (such as legacy BIOS or EFI), used for initial bootstrap in this VM.
    VBox::FirmwareType firmwareTypeProp;
    //! Type of pointing HID (such as mouse or tablet) used in this VM. The default is typically “PS2Mouse” but can vary depending on the requirements of the guest operating system
    VBox::PointingHIDType pointingHIDTypeProp;
    //! Type of keyboard HID used in this VM. The default is typically “PS2Keyboard” but can vary depending on the requirements of the guest operating system.
    VBox::KeyboardHIDType keyboardHIDTypeProp;
    //! This attribute controls if High Precision Event Timer (HPET) is enabled in this VM.
    bool HPETEnabledProp;
    //! Chipset type used in this VM.
    VBox::ChipsetType chipsetTypeProp;
    //! Full path to the directory used to store snapshot data (differencing media and saved state files) of this machine.
    std::string snapshotFolder;
    //! VirtualBox Remote Desktop Extension (VRDE) server object.
    std::shared_ptr<IVRDEServer> VRDEServerProp;
    //! 
    bool emulatedUSBCardReaderEnabledProp;
    //! Array of media attached to this machine.
    std::vector<std::shared_ptr<IMediumAttachment>> mediumAttachmentsProp;
};

#endif