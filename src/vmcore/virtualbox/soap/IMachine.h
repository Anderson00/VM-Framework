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
#include "IUSBController.h"
#include "IAudioAdapter.h"
#include "IStorageController.h"
#include "ISnapshot.h"
#include "ISharedFolder.h"
#include "IPCIDeviceAttachment.h"
#include "IBandwidthControl.h"
#include "IUSBDeviceFilter.h"
#include "IMedium.h"
#include "IProgress.h"
#include "IAppliance.h"
#include "IVirtualSystemDescription.h"
#include "INetworkAdapter.h"
#include "IParallelPort.h"
#include "ISerialPort.h"
#include "ISession.h"
#include "IBandWidthGroup.h"


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

    /*! \brief 
        Adds a new storage controller (SCSI, SAS or SATA controller) to the machine and returns it as
        an instance of IStorageController.
        name identifies the controller for subsequent calls such as getStorageControllerByName(),
        getStorageControllerByInstance(), removeStorageController(), attachDevice() or mountMedium().
        After the controller has been added, you can set its exact type by setting the
        IStorageController::controllerType.
        If this method fails, the following error codes may be reported:
        Exceptions: //TODO: 
    *
    *   \param[in] name
    *   \param[in] connectionType
    */
    std::shared_ptr<IStorageController> addStorageController(std::string name, VBox::StorageBus connectionType);
    /*! \brief 
        Adds a new USB controller to the machine and returns it as an instance of IUSBController.
        If this method fails, the following error codes may be reported:
        //TODO: Exceptions
    *   
    *   \param[in] name
    *   \param[in] type
    */
    std::shared_ptr<IUSBController> addUSBController(std::string name, VBox::USBControllerType type);
    /*! \brief
        Associates the given saved state file to the virtual machine.
        On success, the machine will go to the Saved state. Next time it is powered up, it will be
        restored from the adopted saved state and continue execution from the place where the saved
        state file was created.
        The specified saved state file path may be absolute or relative to the folder the VM normally
        saves the state to (usually, snapshotFolder). Note: It’s a caller’s responsibility to make sure the given saved state file is compatible
        with the settings of this virtual machine that represent its virtual hardware (memory
        size, storage disk configuration etc.). If there is a mismatch, the behavior of the virtual
        machine is undefined.
        If this method fails, the following error codes may be reported:
        //TODO: Exceptions
    *
    *   \param[in] savedStateFile Path to the saved state file to adopt.
    */
    void adoptSavedState(std::string savedStateFile);
    /*! \brief
        Applies the defaults for the configured guest OS type. This is primarily for getting sane settings
        straight after creating a new VM, but it can also be applied later.
        Note: This is primarily a shortcut, centralizing the tedious job of getting the recommended settings and translating them into settings updates. The settings are made at
        the end of the call, but not saved.
        If this method fails, the following error codes may be reported:
        //TODO: Exceptions
    *
    *   \brief[in] flags Additional flags, to be defined later.
    */
    void applyDefaults(std::string flags);
    /*! \brief
        Attaches a device and optionally mounts a medium to the given storage controller
        (IStorageController, identified by name), at the indicated port and device.
        This method is intended for managing storage devices in general while a machine is powered
        off. It can be used to attach and detach fixed and removable media. The following kind of media
        can be attached to a machine:
    *
    *   \param[in] name Name of the storage controller to attach the device to.
    *   \param[in] controllerPort Port to attach the device to. For an IDE controller, 0 specifies the primary controller and 1 specifies the secondary controller. For a SCSI controller, this must range from 0 to 15; for a SATA controller, from 0 to 29; for an SAS controller, from 0 to 7.
    *   \param[in] device Device slot in the given port to attach the device to. This is only relevant for IDE controllers, for which 0 specifies the master device and 1 specifies the slave device. For all other controller types, this must be 0.
    *   \param[in] type Device type of the attached device. For media opened by IVirtualBox::openMedium(), this must match the device type specified there.
    *   \param[in] medium Medium to mount or null for an empty drive.
    * 
    *   <ul>
    *       <li>
    *           For fixed and removable media, you can pass in a medium that was previously opened using IVirtualBox::openMedium().
    *       </li>
    *       <li>
    *           Only for storage devices supporting removable media (such as DVDs and floppies), you can also specify a null pointer to indicate an empty drive or one of the medium objects listed in the IHost::DVDDrives[] and IHost::floppyDrives[] arrays to indicate a host drive. For removable devices, you can also use mountMedium() to change the media while the machine is running.
    *       </li>
    *   </ul>
    *   In a VM’s default configuration of virtual machines, the secondary master of the IDE controller
        is used for a CD/DVD drive.
        After calling this returns successfully, a new instance of IMediumAttachment will appear in the
        machine’s list of medium attachments (see mediumAttachments[]).
        See IMedium and IMediumAttachment for more information about attaching media.
        The specified device slot must not have a device attached to it, or this method will fail.
    */
    void attachDevice(
        std::string name, 
        long controllerPort, 
        long device, 
        VBox::DeviceType type, 
        std::shared_ptr<IMedium> medium);
    /*! //TODO: documentation
    *
    */
    void attachDeviceWithoutMedium(
        std::string name,
        long controllerPort,
        long device,
        VBox::DeviceType type);
    /*! //TODO: documentation
    *
    */
    void attachHostPCIDevice(
        long hostAddress,
        long desiredGuestAddress,
        bool tryToUnbind);
    /*! //TODO: documentation
    *
    */
    std::shared_ptr<IProgress> cloneTo(
        std::shared_ptr<IMachine> target,
        VBox::CloneMode mode,
        std::vector<VBox::CloneOptions> options
    );
    /*! //TODO: documentation
    *
    */
    void createSharedFolder(
        std::string name,
        std::string hostPath,
        bool writable,
        bool automount,
        std::string autoMountPoint
    );
    /*! //TODO: documentation
    *
    */
    std::shared_ptr<IProgress> deleteConfig(
        std::vector<std::shared_ptr<IMedium>> media
    );
    /*! //TODO: documentation
    *
    */
    void deleteGuestProperty(
        std::string name
    );
    /*! //TODO: documentation
    *
    */
    std::shared_ptr<IProgress> deleteSnapshot(
        std::string id
    );
    /*! //TODO: documentation
    *
    */
    std::shared_ptr<IProgress> deleteSnapshotAndAllChildren(
        std::string id
    );
    /*! //TODO: documentation
    *
    */
    std::shared_ptr<IProgress> deleteSnapshotRange(
        std::string startId,
        std::string endId
    );
    /*! //TODO: documentation
    *
    */    
    void detachDevice(
        std::string name,
        long controllerPort,
        long device
    );
    /*! //TODO: documentation
    *
    */
    void detachHostPCIDevice(
        long hostAddress
    );
    /*! //TODO: documentation
    *
    */
    void discardSavedState(
        bool fRemoveFile
    );
    /*! //TODO: documentation
    *
    */
    void discardSettings();
    /*! \brief Return a list of the guest properties matching a set of patterns along with their values, timestamps and flags.
    *
    *   \param[in] patterns     The patterns to match the properties against, separated by ’|’ characters. If this is empty or null, all properties will match.
    *   \param[out] names       The names of the properties returned.
    *   \param[out] values      The values of the properties returned. The array entries match the corresponding entries in the name array.
    *   \param[out] timestamps  The timestamps of the properties returned. The array entries match the corresponding entries in the name array.
    *   \param[out] flags       The flags of the properties returned. The array entries match the corresponding entries in the name array.
    */
    void enumerateGuestProperties(
        std::string patterns,
        std::vector<std::string>& names,
        std::vector<std::string>& values,
        std::vector<long long>& timestamps,
        std::vector<std::string>& flags
    );
    /*! \brief Exports the machine to an OVF appliance. See IAppliance for the steps required to export VirtualBox machines to OVF.
    *   
    *   \param[in] appliance Appliance to export this machine to.
    *   \param[in] location The target location.
    */
    std::shared_ptr<IVirtualSystemDescription> exportTo(
        IAppliance appliance,
        std::string location
    );
    /*! \brief 
        Returns a snapshot of this machine with the given name or UUID.
        Returns a snapshot of this machine with the given UUID. A null argument can be used to
        obtain the first snapshot taken on this machine. To traverse the whole tree of snapshots starting
        from the root, inspect the root snapshot’s ISnapshot::children[] attribute and recurse over those
        children.
        If this method fails, the following error codes may be reported:
        //TODO: Exceptions 
    *
    *   \param[in] nameOrId What to search for. Name or UUID of the snapshot to find
    */
    std::shared_ptr<ISnapshot> findSnapshot(
        std::string nameOrId
    );
    /*! \brief
        Returns the device type that occupies the specified position in the boot order.
        @todo [remove?] If the machine can have more than one device of the returned type (such
        as hard disks), then a separate method should be used to retrieve the individual device that
        occupies the given position.
        If here are no devices at the given position, then Null is returned.
        @todo getHardDiskBootOrder(), getNetworkBootOrder()
        If this method fails, the following error codes may be reported: //TODO: Exceptions
    *
    *   \param[in] position Position in the boot order (1 to the total number of devices the machine can boot from, as returned by ISystemProperties::maxBootPosition).
    */
    VBox::DeviceType getBootOrder(
        unsigned long position
    );
    /*! \brief
        Returns the virtual CPU cpuid information for the specified leaf.
        Currently supported index values for cpuid: Standard CPUID leaves: 0 - 0x1f Extended CPUID
        leaves: 0x80000000 - 0x8000001f VIA CPUID leaves: 0xc0000000 - 0xc000000f
        See the Intel, AMD and VIA programmer’s manuals for detailed information about the CPUID
        instruction and its leaves.
        If this method fails, the following error codes may be reported: //TODO: Exceptions
    *  
    * \param[in] idx      CPUID leaf index.
    *   \param[in] idxSub   CPUID leaf sub-index (ECX). Set to 0xffffffff (or 0) if not applicable.
    *   \param[out] valEax  CPUID leaf value for register eax.
    *   \param[out] valEbx  CPUID leaf value for register ebx.
    *   \param[out] valEcx  CPUID leaf value for register ecx.
    *   \param[out] valEdx  CPUID leaf value for register edx.
    */
    void getCPUIDLeaf(
        unsigned long idx,
        unsigned long idxSub,
        unsigned long *valEax,
        unsigned long *valEbx,
        unsigned long *valEcx,
        unsigned long *valEdx
    );
    /*! \brief
        Used to enumerate CPUID information override values.
        If this method fails, the following error codes may be reported:
        //TODO: Exceptions
    *
    *   \param[in] ordinal  The ordinal number of the leaf to get.
    *   \param[out] idx     CPUID leaf index.
    *   \param[out] idxSub  CPUID leaf sub-index.
    *   \param[out] valEax  CPUID leaf value for register eax.
    *   \param[out] valEbx  CPUID leaf value for register ebx.
    *   \param[out] valEcx  CPUID leaf value for register ecx.
    *   \param[out] valEdx  CPUID leaf value for register edx.
    */
    void getCPUIDLeafByOrdinal(
        unsigned long ordinal,
        unsigned long idx,
        unsigned long idxSub,
        unsigned long valEax,
        unsigned long valEbx,
        unsigned long valEcx,
        unsigned long valEdx
    );
    /*! \brief Returns the virtual CPU boolean value of the specified property. If this method fails, the following error codes may be reported: //TODO: Exceptions
    *
    *   \param[in] property Property type to query.
    */
    bool getCPUProperty(
        VBox::CPUPropertyType property
    );
    /*! \brief Returns the current status of the given CPU.
    *
    *   \param[in] cpu The CPU id to check for.
    */
    bool getCPUStatus(
        unsigned long cpu
    );
    /*! \brief Returns the effective paravirtualization provider for this VM.
    *
    */
    VBox::ParavirtProvider getEffectiveParavirtProvider();
    /*! \brief
        Returns associated machine-specific extra data.
        If the requested data key does not exist, this function will succeed and return an empty string
        in the value argument.
        If this method fails, the following error codes may be reported: //TODO: Exceptions
    *
    *   \param[in] key Name of the data key to get.
    */
    std::string getExtraData(
        std::string key
    );
    /*! \brief Returns an array representing the machine-specific extra data keys which currently have values defined.
    *
    */
    std::vector<std::string> getExtraDataKeys();
    /*! \brief Reads an entry from the machine’s guest property store. If this method fails, the following error codes may be reported: //TODO: Exceptions
    *   
    *   \param[in] name The name of the property to read.
    *   \param[out] value The value of the property. If the property does not exist then this will be empty.
    *   \param[out] timestamp The time at which the property was last modified, as seen by the server process.
    *   \param[out] flags Additional property parameters, passed as a comma-separated list of “name=value” type entries.
    */
    void getGuestProperty(
        std::string name,
        std::string value,
        long long timestamp,
        std::string flags
    );
    /*! \brief Reads a property timestamp from the machine’s guest property store. If this method fails, the following error codes may be reported: //TODO: Exceptions
    *
    *   \param[in] property The name of the property to read.
    */
    long long getGuestPropertyTimestamp(
        std::string property
    );
    /*! \brief Reads a value from the machine’s guest property store. If this method fails, the following error codes may be reported: //TODO: Exceptions
    *
    *   \param[in] property The name of the property to read.
    */
    std::string getGuestPropertyValue(
        std::string property
    );
    /*! \brief Returns the value of the specified hardware virtualization boolean property. If this method fails, the following error codes may be reported: //TODO: Exceptions
    *   
    *   \param[in] property Property type to query.
    */
    bool getHWVirtExProperty(
        VBox::HWVirtExPropertyType property
    );
    /*! \brief 
        Returns the virtual medium attached to a device slot of the specified bus.
        Note that if the medium was indirectly attached by mountMedium() to the given device slot
        then this method will return not the same object as passed to the mountMedium() call. See
        IMedium for more detailed information about mounting a medium.
        If this method fails, the following error codes may be reported: //TODO: Exceptions
    *   
    *   \param[in] name Name of the storage controller the medium is attached to.
    *   \param[in] controllerPort Port to query.
    *   \param[in] device Device slot in the given port to query.
    */
    std::shared_ptr<IMedium> getMedium(
        std::string name,
        long controllerPort,
        long device
    );
    /*! \brief
        Returns a medium attachment which corresponds to the controller with the given name, on
        the given port and device slot.
        If this method fails, the following error codes may be reported: //TODO: Exceptions
    *
    *   \param[in] name
    *   \param[in] controllerPort
    *   \param[in] device
    */
    std::shared_ptr<IMediumAttachment> getMediumAttachment(
        std::string name,
        long controllerPort,
        long device
    );
    /*! \brief 
        Returns an array of medium attachments which are attached to the the controller with the given name.
        If this method fails, the following error codes may be reported: //TODO: Exceptions
    *
    *   \param[in] name
    */
    std::vector<std::shared_ptr<IMediumAttachment>> getMediumAttachmentsOfController(
        std::string name
    );
    /*! \brief 
        Returns the network adapter associated with the given slot. Slots are numbered sequentially, starting with zero. The total number of adapters per machine is defined by the
        ISystemProperties::getMaxNetworkAdapters() property, so the maximum slot number is one less
        than that property’s value.
        If this method fails, the following error codes may be reported: //TODO: Exceptions
    *
    *   \param[in] slot
    */
    std::shared_ptr<INetworkAdapter> getNetworkAdapter(
        unsigned long slot
    );
    /*! \brief
        Returns the parallel port associated with the given slot. Slots are numbered sequentially, starting with zero. The total number of parallel ports per machine is defined by the
        ISystemProperties::parallelPortCount property, so the maximum slot number is one less than
        that property’s value.
        If this method fails, the following error codes may be reported: //TODO: Exceptions
    *
    *   \param[in] slot
    */
    std::shared_ptr<IParallelPort> getParallelPort(
        unsigned long slot
    );
    /*! \brief
        Returns the serial port associated with the given slot. Slots are numbered sequentially, starting with zero. The total number of serial ports per machine is defined by the
        ISystemProperties::serialPortCount property, so the maximum slot number is one less than that
        property’s value.
        If this method fails, the following error codes may be reported: //TODO: Excptions
    *
    *   \param[in] slot
    */
    std::shared_ptr<ISerialPort> getSerialPort(
        unsigned long slot
    );
    /*! \brief
        Returns a storage controller of a specific storage bus with the given instance number.
        If this method fails, the following error codes may be reported: //TODO: Exceptions
    *
    *   \param[in] connectionType
    *   \param[in] instance
    */
    std::shared_ptr<IStorageController> getStorageControllerByInstance(
        VBox::StorageBus connectionType,
        unsigned long instance
    );
    /*! \brief Returns a storage controller with the given name. If this method fails, the following error codes may be reported: //TODO: Exceptions
    *
    *   \param[in] name
    */
    std::shared_ptr<IUSBController> getUSBControllerByName(
        std::string name
    );
    /*! \brief Returns the number of USB controllers of the given type attached to the VM.
    *
    *   \param[in] type
    */
    unsigned long getUSBControllerCountByType(
        VBox::USBControllerType type
    );
    /*! \brief Plugs a CPU into the machine.
    *
    *   \param[in] cpu The CPU id to insert.
    */
    void hotPlugCPU(unsigned long cpu);
    /*! \brief Removes a CPU from the machine.
    *
    *   \param[in] cpu The CPU to remove.
    */
    void hotUnplugCPU(
        unsigned long cpu
    );
    /*! \brief
        Spawns a new process that will execute the virtual machine and obtains a shared lock on the
        machine for the calling session.
        If launching the VM succeeds, the new VM process will create its own session and write-lock
        the machine for it, preventing conflicting changes from other processes. If the machine is already
        locked (because it is already running or because another session has a write lock), launching the
        VM process will therefore fail. Reversely, future attempts to obtain a write lock will also fail
        while the machine is running.
        The caller’s session object remains separate from the session opened by the new VM process.
        It receives its own IConsole object which can be used to control machine execution, but it cannot
        be used to change all VM settings which would be available after a lockMachine() call.
        The caller must eventually release the session’s shared lock by calling
        ISession::unlockMachine() on the local session object once this call has returned. However, the session’s state (see ISession::state) will not return to “Unlocked” until the remote
        session has also unlocked the machine (i.e. the machine has stopped running).
        Launching a VM process can take some time (a new VM is started in a new process, for which
        memory and other resources need to be set up). Because of this, an IProgress object is returned to
        allow the caller to wait for this asynchronous operation to be completed. Until then, the caller’s
        session object remains in the “Unlocked” state, and its ISession::machine and ISession::console
        attributes cannot be accessed. It is recommended to use IProgress::waitForCompletion() or similar calls to wait for completion. Completion is signalled when the VM is powered on. If launching
        the VM fails, error messages can be queried via the progress object, if available.
        The progress object will have at least 2 sub-operations. The first operation covers the
        period up to the new VM process calls powerUp. The subsequent operations mirror the
        IConsole::powerUp() progress object. Because IConsole::powerUp() may require some extra
        sub-operations, the IProgress::operationCount may change at the completion of operation.
        For details on the teleportation progress operation, see IConsole::powerUp().
        The environmentChanges argument is a list of strings where every string contains environment variable in the putenv style, i.e. “VAR=VALUE” for setting/replacing and “VAR” for unsetting. These environment variables will be applied to the environment of the VirtualBox server
        process. If an environment variable exists both in the server process and in this list, the value
        from this list takes precedence over the server’s variable. If the value of the environment variable
        is omitted, this variable will be removed from the resulting environment. If the list is empty, the
        server environment is inherited by the started process as is.
        If this method fails, the following error codes may be reported: //TODO: Exceptions
    *
    *   \param[in] session Client session object to which the VM process will be connected (this must be in “Unlocked” state).
    *   \param[in] name Front-end to use for the new VM process. The following are currently supported:
    *       <ul>
    *           <li>"gui": VirtualBox Qt GUI front-end</li>
    *           <li>"headless": VBoxHeadless (VRDE Server) front-end</li>
    *           <li>"sdl": VirtualBox SDL front-end</li>
    *           <li>"emergencystop": reserved value, used for aborting the currently running VM or
                    session owner. In this case the session parameter may be null (if it is non-null
                    it isn’t used in any way), and the progress return value will be always null. The
                    operation completes immediately.
                </li>
                <li>
                    "": use the per-VM default frontend if set, otherwise the global default defined in
                    the system properties. If neither are set, the API will launch a "gui" session, which
                    may fail if there is no windowing environment available. See defaultFrontend and
                    ISystemProperties::defaultFrontend.
                </li>
    *       </ul>
    *   \param[in] environmentChanges The list of putenv-style changes to the VM process environment.
    */
    std::shared_ptr<IProgress> launchVMProcess(
        std::shared_ptr<ISession> session,
        std::string name,
        std::vector<std::string> environmentChanges 
    );
    /*! \brief
        Locks the machine for the given session to enable the caller to make changes to the machine
        or start the VM or control VM execution.
        There are two ways to lock a machine for such uses:
        <ul>
            <li>
                If you want to make changes to the machine settings, you must obtain an exclusive write
                lock on the machine by setting lockType to Write.
                This will only succeed if no other process has locked the machine to prevent conflicting
                changes. Only after an exclusive write lock has been obtained using this method, one
                can change all VM settings or execute the VM in the process space of the session object.
                (Note that the latter is only of interest if you actually want to write a new front-end for
                virtual machines; but this API gets called internally by the existing front-ends such as
                VBoxHeadless and the VirtualBox GUI to acquire a write lock on the machine that they are
                running.)
                On success, write-locking the machine for a session creates a second copy of the IMachine
                object. It is this second object upon which changes can be made; in VirtualBox terminology,
                the second copy is “mutable”. It is only this second, mutable machine object upon which
                you can call methods that change the machine state. After having called this method, you
                can obtain this second, mutable machine object using the ISession::machine attribute.
            </li>
            <li>
                If you only want to check the machine state or control machine execution without actually
                changing machine settings (e.g. to get access to VM statistics or take a snapshot or save
                the machine state), then set the lockType argument to Shared.
                If no other session has obtained a lock, you will obtain an exclusive write lock as described
                above. However, if another session has already obtained such a lock, then a link to that
                existing session will be established which allows you to control that existing session.
                To find out which type of lock was obtained, you can inspect ISession::type, which will
                have been set to either WriteLock or Shared.
            </li>
        </ul>
        In either case, you can get access to the IConsole object which controls VM execution.
        Also in all of the above cases, one must always call ISession::unlockMachine() to release the
        lock on the machine, or the machine’s state will eventually be set to “Aborted”.
        To change settings on a machine, the following sequence is typically performed:
        <ol>
            <li>Call this method to obtain an exclusive write lock for the current session.</li>
            <li>Obtain a mutable IMachine object from ISession::machine.</li>
            <li>Change the settings of the machine by invoking IMachine methods.</li>
            <li>Call saveSettings().</li>
            <li>Release the write lock by calling ISession::unlockMachine().</li>
        </ol>
        If this method fails, the following error codes may be reported: //TODO: Exceptions
    *
    *   \param[in] session Session object for which the machine will be locked.
    *   \param[in] lockType If set to Write, then attempt to acquire an exclusive write lock or fail. If set to Shared, then either acquire an exclusive write lock or establish a link to an existing session.
    */
    void lockMachine(
        std::shared_ptr<ISession> session,
        VBox::LockType lockType
    );
    /*! \brief 
        Mounts a medium (IMedium, identified by the given UUID id) to the given storage controller
        (IStorageController, identified by name), at the indicated port and device. The device must
        already exist; see attachDevice() for how to attach a new device.
        This method is intended only for managing removable media, where the device is fixed but
        media is changeable at runtime (such as DVDs and floppies). It cannot be used for fixed media
        such as hard disks.
        The controllerPort and device parameters specify the device slot and have have the same
        meaning as with attachDevice().
        The specified device slot can have a medium mounted, which will be unmounted first. Specifying a zero UUID (or an empty string) for medium does just an unmount.
        See IMedium for more detailed information about attaching media.
        If this method fails, the following error codes may be reported: //TODO: Exceptions
    *
    *   \param[in] name Name of the storage controller to attach the medium to.
    *   \param[in] controllerPort Port to attach the medium to.
    *   \param[in] device Device slot in the given port to attach the medium to.
    *   \param[in] medium Medium to mount or null for an empty drive.
    *   \param[in] force Allows to force unmount/mount of a medium which is locked by the device slot in the given port to attach the medium to.
    */
    void mountMedium(
        std::string name,
        long controllerPort,
        long device,
        std::shared_ptr<IMedium> medium,
        bool force
    );
    /*! \brief Move machine on to new place/folder If this method fails, the following error codes may be reported: //TODO: Exceptions
    *   
    *   \param[in] folder Target folder where machine is moved.
    *   \param[in] type Type of moving. Possible values: basic - Only the files which belong solely to this machine are moved from the original machine’s folder to a new folder.
    */
    std::shared_ptr<IProgress> moveTo(
        std::string folder,
        std::string type
    );
    /*! \brief 
        Sets a flag in the device information which indicates that the medium is not based on rotational
        technology, i.e. that the access times are more or less independent of the position on the medium.
        This may or may not be supported by a particular drive, and is silently ignored in the latter
        case. At the moment only hard disks (which is a misnomer in this context) accept this setting.
        Changing the setting while the VM is running is forbidden. The device must already exist; see
        attachDevice() for how to attach a new device.
        The controllerPort and device parameters specify the device slot and have have the same
        meaning as with attachDevice().
        If this method fails, the following error codes may be reported: //TODO: Exceptions
    *
    *   \param[in] name Name of the storage controller.
    *   \param[in] controllerPort Storage controller port.
    *   \param[in] device Device slot in the given port.
    *   \param[in] nonRotational New value for the non-rotational device flag.
    */
    void nonRotationalDevice(
        std::string name,
        long controllerPort,
        long device,
        bool nonRotational
    );
    /*! \brief 
        Sets the passthrough mode of an existing DVD device. Changing the setting while the VM is
        running is forbidden. The setting is only used if at VM start the device is configured as a host
        DVD drive, in all other cases it is ignored. The device must already exist; see attachDevice() for
        how to attach a new device.
        The controllerPort and device parameters specify the device slot and have have the same
        meaning as with attachDevice().
        If this method fails, the following error codes may be reported: //TODO: Exceptions
    *
    *   \param[in] name Name of the storage controller.
    *   \param[in] controllerPort Storage controller port.
    *   \param[in] device Device slot in the given port.
    *   \param[in] passthrough New value for the passthrough setting.
    */
    void passthroughDevice(
        std::string name,
        long controllerPort,
        long device,
        bool passthrough
    );
    /*! \brief 
        Queries for the VM log file name of an given index. Returns an empty string if a log file with that index doesn’t exists.
    *
    *   \param[in] idx Which log file name to query. 0=current log file.
    */
    std::string queryLogFilename(
        unsigned long idx
    );
    /*! \brief enabled Whether the monitor is enabled in the guest.
    *
    *   \param[in] screenId Saved guest screen to query info from.
    *   \param[in] originX The X position of the guest monitor top left corner.
    *   \param[in] originY The Y position of the guest monitor top left corner
    *   \param[in] width Guest width at the time of the saved state was taken.
    *   \param[in] height Guest height at the time of the saved state was taken.
    *   \param[in] enabled Whether the monitor is enabled in the guest.
    */
    void querySavedGuestScreenInfo(
        unsigned long screenId,
        unsigned long originX,
        unsigned long originY,
        unsigned long width,
        unsigned long height,
        bool enabled
    );
    /*! \brief
        Removes the permanent shared folder with the given name previously created by
        createSharedFolder() from the collection of shared folders and stops sharing it.
        If this method fails, the following error codes may be reported: //TODO: Exceptions 
    *
    *   \param[in] name Logical name of the shared folder to remove.
    */
    void removeSharedFolder(std::string name);
    /*! \brief
        Removes a storage controller from the machine with all devices attached to it. If this method fails, the following error codes may be reported: //TODO: Exceptions
    *
    *   \param[in] name
    */
    void removeStorageController(
        std::string name
    );
    /*! \brief 
        Removes a USB controller from the machine. If this method fails, the following error codes may be reported: //TODO: Exceptions
    *
    *   \param name
    */
    void removeUSBController(
        std::string name
    );
    /*! \brief 
        Starts resetting the machine’s current state to the state contained in the given snapshot, asynchronously. All current settings of the machine will be reset and changes stored in differencing
        media will be lost. See ISnapshot for an introduction to snapshots.
        After this operation is successfully completed, new empty differencing media are created for
        all normal media of the machine.
        If the given snapshot is an online snapshot, the machine will go to the Saved, so that the next
        time it is powered on, the execution state will be restored from the state of the snapshot.
        If this method fails, the following error codes may be reported: //TODO: Exceptions
    *
    *   \param[in] snapshot The snapshot to restore the VM state from.
    */
    std::shared_ptr<IProgress> restoreSnapshot(
        std::shared_ptr<ISnapshot> snapshot
    );
    /*! \brief 
        Saves any changes to machine settings made since the session has been opened or a new machine has been created, or since the last call to saveSettings() or discardSettings(). For registered
        machines, new settings become visible to all other VirtualBox clients after successful invocation
        of this method.
        If this method fails, the following error codes may be reported: //TODO: Exceptions
    *
    */
    void saveSettings();
    /*! \brief 
        Saves the current execution state of a running virtual machine and stops its execution.
        After this operation completes, the machine will go to the Saved state. Next time it is powered
        up, this state will be restored and the machine will continue its execution from the place where
        it was saved.
        This operation differs from taking a snapshot to the effect that it doesn’t create new differencing media. Also, once the machine is powered up from the state saved using this method, the
        saved state is deleted, so it will be impossible to return to this state later.
        See also: takeSnapshot()
        If this method fails, the following error codes may be reported: //TODO: Exceptions
    *
    */
    std::shared_ptr<IProgress> saveState();
    /*! \brief
        Sets a flag in the device information which indicates that the medium supports discarding
        unused blocks (called trimming for SATA or unmap for SCSI devices) .This may or may not be
        supported by a particular drive, and is silently ignored in the latter case. At the moment only
        hard disks (which is a misnomer in this context) accept this setting. Changing the setting while
        the VM is running is forbidden. The device must already exist; see attachDevice() for how to
        attach a new device.
        The controllerPort and device parameters specify the device slot and have have the same
        meaning as with attachDevice().
        If this method fails, the following error codes may be reported: //TODO: Exceptions
    *
    *   \param[in] name Name of the storage controller.
    *   \param[in] controllerPort Storage controller port.
    *   \param[in] device Device slot in the given port.
    *   \param[in] discard New value for the discard device flag.
    */
    void setAutoDiscardForDevice(
        std::string name,
        long controllerPort,
        long device,
        bool discard
    );
    /*! \brief
        Sets the bandwidth group of an existing storage device. The device must already exist; see
        attachDevice() for how to attach a new device.
        The controllerPort and device parameters specify the device slot and have have the same
        meaning as with attachDevice().
        If this method fails, the following error codes may be reported: //TODO: Exceptions
    *
    *   \param[in] name Name of the storage controller.
    *   \param[in] controllerPort Storage controller port.
    *   \param[in] device Device slot in the given port.
    *   \param[in] bandwidthGroup New value for the bandwidth group or null for no group.
    */
    void setBandwidthGroupForDevice(
        std::string name,
        long controllerPort,
        long device,
        std::shared_ptr<IBandWidthGroup> bandwidthGroup
    );
    /*! \brief
        Puts the given device to the specified position in the boot order.
        To indicate that no device is associated with the given position, Null should be used.
        @todo setHardDiskBootOrder(), setNetworkBootOrder()
        If this method fails, the following error codes may be reported: //TODO: Exceptions
    *
    *   \param[in] position Position in the boot order (1 to the total number of devices the machine can boot from, as returned by ISystemProperties::maxBootPosition)
    *   \param[in] device The type of the device used to boot at the given position.
    */
    void setBootOrder(
        unsigned long position,
        VBox::DeviceType device
    );
    /*! \brief
        Sets the virtual CPU cpuid information for the specified leaf. Note that these values are not
        passed unmodified. VirtualBox clears features that it doesn’t support.
        Currently supported index values for cpuid: Standard CPUID leaves: 0 - 0x1f Extended CPUID
        leaves: 0x80000000 - 0x8000001f VIA CPUID leaves: 0xc0000000 - 0xc000000f
        The subleaf index is only applicable to certain leaves (see manuals as this is subject to change).
        See the Intel, AMD and VIA programmer’s manuals for detailed information about the cpuid
        instruction and its leaves.
        Do not use this method unless you know exactly what you’re doing. Misuse can lead to random
        crashes inside VMs.
        If this method fails, the following error codes may be reported: //TODO: Exceptions
    *   
    *   \param[in] idx CPUID leaf index.
    *   \param[in] idxSub CPUID leaf sub-index (ECX). Set to 0xffffffff (or 0) if not applicable. The 0xffffffff causes it to remove all other subleaves before adding one with sub-index 0.
    *   \param[in] valEax CPUID leaf value for register eax.
    *   \param[in] valEbx CPUID leaf value for register ebx.
    *   \param[in] valEcx CPUID leaf value for register ecx.
    *   \param[in] valEdx CPUID leaf value for register edx.
    */
    void setCPUIDLeaf(
        unsigned long idx,
        unsigned long idxSub,
        unsigned long valEax,
        unsigned long valEbx,
        unsigned long valEcx,
        unsigned long valEdx
    );
    /*! \brief 
        Sets the virtual CPU boolean value of the specified property. If this method fails, the following error codes may be reported:
        //TODO: Exceptions
    *
    *   \param[in] property Property type to query.
    *   \param[in] value Property value.
    */
    void setCPUProperty(
        VBox::CPUPropertyType property,
        bool value
    );
    /*! \brief
        Sets associated machine-specific extra data. If you pass null or an empty string as a key value, the given key will be deleted.
        If this method fails, the following error codes may be reported:
        //TODO: Exceptions
    *
    *   \param[in] key Name of the data key to set.
    *   \param[in] value Value to assign to the key.
    */
    void setExtraData(
        std::string key,
        std::string value
    );
    /*! \brief
        Sets, changes or deletes an entry in the machine’s guest property store. If this method fails, the following error codes may be reported:
        //TODO: Exceptions 
    *
    *   \param[in] property The name of the property to set, change or delete.
    *   \param[in] value The new value of the property to set, change or delete. If the property does not yet exist and value is non-empty, it will be created. If the value is null or empty, the property will be deleted if it exists.
    *   \param[in] flags Additional property parameters, passed as a comma-separated list of “name=value” type entries.
    */
    void setGuestProperty(
        std::string property,
        std::string value,
        std::string flags
    );
    /*! \brief
        Sets or changes a value in the machine’s guest property store. The flags field will be left
        unchanged or created empty for a new property.
        If this method fails, the following error codes may be reported: //TODO: Exceptions
    *
    *   \param[in] property The name of the property to set or change.
    *   \param[in] value The new value of the property to set or change. If the property does not yet exist and value is non-empty, it will be created.
    */
    void setGuestPropertyValue(
        std::string property,
        std::string value
    );
    /*! \brief
        Sets a new value for the specified hardware virtualization boolean property.
        If this method fails, the following error codes may be reported: //TODO: Exceptions
    *
    *   \param[in] property Property type to set.
    *   \param[in] value New property value.
    */
    void setHWVirtExProperty(
        VBox::HWVirtExPropertyType property,
        bool value
    );
    /*! \brief
        Sets a flag in the device information which indicates that the attached device is hot pluggable
        or not. This may or may not be supported by a particular controller and/or drive, and is silently
        ignored in the latter case. Changing the setting while the VM is running is forbidden. The device
        must already exist; see attachDevice() for how to attach a new device.
        The controllerPort and device parameters specify the device slot and have have the same
        meaning as with attachDevice().
        If this method fails, the following error codes may be reported: //TODO: Exceptions
    *
    *   \param[in] name Name of the storage controller.
    *   \param[in] controllerPort Storage controller port.
    *   \param[in] device Device slot in the given port.
    *   \param[in] hotPluggable New value for the hot-pluggable device flag.
    */
    void setHotPluggableForDevice(
        std::string name,
        long controllerPort,
        long device,
        bool hotPluggable
    );
    /*! \brief
        Sets no bandwidth group for an existing storage device. The device must already exist; see
        attachDevice() for how to attach a new device. The controllerPort and device parameters
        specify the device slot and have have the same meaning as with attachDevice().
        If this method fails, the following error codes may be reported: //TODO: Exceptions
    *
    *   \param[in] name Name of the storage controller.
    *   \param[in] controllerPort Storage controller port.
    *   \param[in] device Device slot in the given port.
    */
    void setNoBandwidthGroupForDevice(
        std::string name,
        long controllerPort,
        long device
    );
    /*! \brief
        Currently, it is an error to change this property on any machine. Later this will allow setting a
        new path for the settings file, with automatic relocation of all files (including snapshots and disk
        images) which are inside the base directory. This operation is only allowed when there are no
        pending unsaved settings.
        If this method fails, the following error codes may be reported: //TODO: Exceptions
    *
    *   \param[in] settingsFilePath New settings file path, will be used to determine the new location for the attached media if it is in the same directory or below as the original settings file. 
    */
    std::shared_ptr<IProgress> setSettingsFilePath(
        std::string settingsFilePath
    );
    /*! \brief
        Sets the bootable flag of the storage controller with the given name.
        If this method fails, the following error codes may be reported: //TODO: Exceptions
    *
    *   \param[in] name
    *   \param[in] bootable
    */
    void setStorageControllerBootable(
        std::string name,
        bool bootable
    );
    /*! \brief
        Activates the console window and brings it to foreground on the desktop of the host PC. Many
        modern window managers on many platforms implement some sort of focus stealing prevention
        logic, so that it may be impossible to activate a window without the help of the currently active
        application. In this case, this method will return a non-zero identifier that represents the toplevel window of the VM console process. The caller, if it represents a currently active process,
        is responsible to use this identifier (in a platform-dependent manner) to perform actual window
        activation. If this method fails, the following error codes may be reported:
        //TODO: Exceptions
    *
    */
    long long showConsoleWindow();
    /*! \brief
        Saves the current execution state and all settings of the machine and creates differencing
        images for all normal (non-independent) media. See ISnapshot for an introduction to snapshots.
        This method can be called for a PoweredOff, Saved (see saveState()), Running or Paused
        virtual machine. When the machine is PoweredOff, an offline snapshot is created. When the
        machine is Running a live snapshot is created, and an online snapshot is created when Paused.
        The taken snapshot is always based on the current snapshot of the associated virtual machine
        and becomes a new current snapshot. If this method fails, the following error codes may be reported:
        //TODO: Exceptions
    *
    *   \param[in] name Short name for the snapshot.
    *   \param[in] description Optional description of the snapshot.
    *   \param[in] pause Whether the VM should be paused while taking the snapshot. Only relevant when the VM is running, and distinguishes between online (true) and live (false) snapshots. When the VM is not running the result is always an offline snapshot.
    *   \param[out] id UUID of the snapshot which will be created. Useful for follow-up operations after the snapshot has been created.
    */
    std::shared_ptr<IProgress> takeSnapshot(
        std::string name,
        std::string description,
        bool pause,
        std::string& id
    );
    /*! \brief
        Sets the behavior for guest-triggered medium eject. In some situations it is desirable that such
        ejects update the VM configuration, and in others the eject should keep the VM configuration.
        The device must already exist; see attachDevice() for how to attach a new device.
        The controllerPort and device parameters specify the device slot and have have the same
        meaning as with attachDevice().
        If this method fails, the following error codes may be reported: //TODO: Exceptions
    *
    *   \param[in] name Name of the storage controller.
    *   \param[in] controllerPort Storage controller port.
    *   \param[in] device Device slot in the given port.
    *   \param[in] temporaryEject New value for the eject behavior.
    */
    void temporaryEjectDevice(
        std::string name,
        long controllerPort,
        long device,
        bool temporaryEject
    );
    /*! \brief
        Unmounts any currently mounted medium (IMedium, identified by the given UUID id) to
        the given storage controller (IStorageController, identified by name), at the indicated port and
        device. The device must already exist;
        This method is intended only for managing removable media, where the device is fixed but
        media is changeable at runtime (such as DVDs and floppies). It cannot be used for fixed media
        such as hard disks.
        The controllerPort and device parameters specify the device slot and have have the same
        meaning as with attachDevice().
        The specified device slot must have a medium mounted, which will be unmounted. If there
        is no mounted medium it will do nothing. See IMedium for more detailed information about
        attaching/unmounting media.
        If this method fails, the following error codes may be reported:
        //TODO: Exceptions
    *
    *   \param[in] name Name of the storage controller to unmount the medium from.
    *   \param[in] controllerPort Port to unmount the medium from.
    *   \param[in] device Device slot in the given port to unmount the medium from.
    *   \param[in] force Allows to force unmount of a medium which is locked by the device slot in the given port medium is attached to.
    */
    void unmountMedium(
        std::string name,
        long controllerPort,
        long device,
        bool force
    );
    /*! \brief
        Unregisters a machine previously registered with IVirtualBox::registerMachine() and optionally do additional cleanup before the machine is unregistered.
        This method does not delete any files. It only changes the machine configuration and the
        list of registered machines in the VirtualBox object. To delete the files which belonged to the
        machine, including the XML file of the machine itself, call deleteConfig(), optionally with the
        array of IMedium objects which was returned from this method.
        How thoroughly this method cleans up the machine configuration before unregistering the
        machine depends on the cleanupMode argument.
        <ul>
            <li>
                With “UnregisterOnly”, the machine will only be unregistered, but no additional cleanup
                will be performed. The call will fail if the machine is in “Saved” state or has any snapshots
                or any media attached (see IMediumAttachment). It is the responsibility of the caller to
                delete all such configuration in this mode. In this mode, the API behaves like the former
                IVirtualBox::unregisterMachine() API which it replaces.
            </li>
            <li>
                With “DetachAllReturnNone”, the call will succeed even if the machine is in “Saved” state
                or if it has snapshots or media attached. All media attached to the current machine state
                or in snapshots will be detached. No medium objects will be returned; all of the machine’s
                media will remain open.
            </li>
            <li>
                With “DetachAllReturnHardDisksOnly”, the call will behave like with “DetachAllReturnNone”, except that all the hard disk medium objects which were detached from the machine
                will be returned as an array. This allows for quickly passing them to the deleteConfig() API
                for closing and deletion.
            </li>
            <li>
                With “Full”, the call will behave like with “DetachAllReturnHardDisksOnly”, except that all
                media will be returned in the array, including removable media like DVDs and floppies.
                This might be useful if the user wants to inspect in detail which media were attached to the
                machine. Be careful when passing the media array to deleteConfig() in that case because
                users will typically want to preserve ISO and RAW image files.
            </li>
        </ul>
        A typical implementation will use “DetachAllReturnHardDisksOnly” and then pass the resulting IMedium array to deleteConfig(). This way, the machine is completely deleted with all its
        saved states and hard disk images, but images for removable drives (such as ISO and RAW files)
        will remain on disk.
        This API does not verify whether the media files returned in the array are still attached to
        other machines (i.e. shared between several machines). If such a shared image is passed to
        deleteConfig() however, closing the image will fail there and the image will be silently skipped.
        This API may, however, move media from this machine’s media registry to other media registries (see IMedium for details on media registries). For machines created with VirtualBox 4.0 or
        later, if media from this machine’s media registry are also attached to another machine (shared
        attachments), each such medium will be moved to another machine’s registry. This is because
        without this machine’s media registry, the other machine cannot find its media any more and
        would become inaccessible.
        This API implicitly calls saveSettings() to save all current machine settings before unregistering it. It may also silently call saveSettings() on other machines if media are moved to other
        machines’ media registries.
        After successful method invocation, the IMachineRegisteredEvent event is fired.
        The call will fail if the machine is currently locked (see ISession).
        If this method fails, the following error codes may be reported: //TODO: Exceptions
    *
    *  \param[in] cleanupMode How to clean up after the machine has been unregistered.
    */
    std::vector<std::shared_ptr<IMedium>> unregister(
        VBox::CleanupMode cleanupMode
    );

    const std::string& icon();
    const std::string& icon()const;
    bool accessible();
    bool accessible()const;
    const std::shared_ptr<IVirtualBoxErrorInfo> accessError();
    const std::shared_ptr<IVirtualBoxErrorInfo> accessError()const;
    const std::string& name();
    const std::string& name() const;
    const std::string& id();
    const std::string& id()const;
    const std::vector<std::string> groups();
    const std::vector<std::string> groups()const;
    const std::string& OSTypeId();
    const std::string& OSTypeId()const;
    const std::string& hardwareVersion();
    const std::string& hardwareVersion()const;
    const std::string& hardwareUUID();
    const std::string& hardwareUUID()const;
    unsigned long CPUCount();
    unsigned long CPUCount()const;
    bool CPUHotPlugEnabled();
    bool CPUHotPlugEnabled()const;
    unsigned long CPUExecutionCap();
    unsigned long CPUExecutionCap()const;
    unsigned long CPUIDPortabilityLevel();
    unsigned long CPUIDPortabilityLevel()const;
    unsigned long memorySize();
    unsigned long memorySize()const;
    unsigned long memoryBalloonSize();
    unsigned long memoryBalloonSize()const;
    bool pageFusionEnabled();
    bool pageFusionEnabled()const;
    const std::shared_ptr<IGraphicsAdapter> graphicsAdapter();
    const std::shared_ptr<IGraphicsAdapter> graphicsAdapter()const;
    const std::shared_ptr<IBIOSSettings> BIOSSettings();
    const std::shared_ptr<IBIOSSettings> BIOSSettings()const;
    const std::shared_ptr<IRecordingSettings> recordingSettings();  
    const std::shared_ptr<IRecordingSettings> recordingSettings()const;
    VBox::FirmwareType firmwareType();
    VBox::FirmwareType firmwareType()const;

    VBox::PointingHIDType pointingHIDType();
    VBox::PointingHIDType pointingHIDType()const;

    VBox::KeyboardHIDType keyboardHIDType();
    VBox::KeyboardHIDType keyboardHIDType()const;

    bool HPETEnabled();
    bool HPETEnabled()const;

    VBox::ChipsetType chipsetType();
    VBox::ChipsetType chipsetType()const;

    const std::string& snapshotFolder();
    const std::string& snapshotFolder()const;
    const std::shared_ptr<IVRDEServer> VRDEServer();
    const std::shared_ptr<IVRDEServer> VRDEServer()const;
    bool emulatedUSBCardReaderEnabled();
    bool emulatedUSBCardReaderEnabled()const;

    //TODO: Caso especial IMediumAttachment é um struct
    const std::vector<std::shared_ptr<IMediumAttachment>>& mediumAttachments();
    const std::vector<std::shared_ptr<IMediumAttachment>>& mediumAttachments()const;

    const std::vector<std::shared_ptr<IUSBController>> USBControllers();
    const std::vector<std::shared_ptr<IUSBController>> USBControllers()const;
    const std::shared_ptr<IUSBDeviceFilter> USBDeviceFilters();
    const std::shared_ptr<IUSBDeviceFilter> USBDeviceFilters()const;
    const std::shared_ptr<IAudioAdapter> audioAdapter();
    const std::shared_ptr<IAudioAdapter> audioAdapter()const;

    //TODO: Caso especial.
    const std::vector<std::shared_ptr<IStorageController>> storageControllers();
    const std::vector<std::shared_ptr<IStorageController>> storageControllers()const;

    const std::string& settingsFilePath();
    const std::string& settingsFilePath()const;
    const std::string& settingsAuxFilePath();
    const std::string& settingsAuxFilePath()const;
    bool settingsModified();
    bool settingsModified()const;

    VBox::SessionState sessionState();
    VBox::SessionState sessionState()const;

    const std::string& sessionName();
    const std::string& sessionName()const;

    unsigned long sessionPID();
    unsigned long sessionPID()const;

    VBox::MachineState state();
    VBox::MachineState state()const;

    long long lastStateChange();
    long long lastStateChange()const;

    const std::string& stateFilePath();
    const std::string& stateFilePath()const;

    const std::string& logFolder();
    const std::string& logFolder()const;

    const std::shared_ptr<ISnapshot> currentSnapshot();
    const std::shared_ptr<ISnapshot> currentSnapshot()const;

    unsigned long snapshotCount();
    unsigned long snapshotCount()const;
    
    bool currentStateModified();
    bool currentStateModified()const;

    const std::vector<std::shared_ptr<ISharedFolder>> sharedFolders();
    const std::vector<std::shared_ptr<ISharedFolder>> sharedFolders()const;

    VBox::ClipboardMode clipboardMode();
    VBox::ClipboardMode clipboardMode()const;

    bool clipboardFileTransfersEnabled();
    bool clipboardFileTransfersEnabled()const;

    VBox::DnDMode dnDMode();
    VBox::DnDMode dnDMode()const;

    bool teleporterEnabled();
    bool teleporterEnabled()const;
    unsigned long teleporterPort();
    unsigned long teleporterPort()const;
    const std::string& teleporterAddress();
    const std::string& teleporterAddress()const;

    const std::string& teleporterPassword();
    const std::string& teleporterPassword()const;

    VBox::ParavirtProvider paravirtProvider();
    VBox::ParavirtProvider paravirtProvider()const;

    bool RTCUseUTC();
    bool RTCUseUTC()const;

    bool IOCacheEnabled();
    bool IOCacheEnabled()const;

    unsigned long IOCacheSize();
    unsigned long IOCacheSize()const;

    //TODO: caso especial.
    const std::vector<std::shared_ptr<IPCIDeviceAttachment>> PCIDeviceAssignments();
    const std::vector<std::shared_ptr<IPCIDeviceAttachment>> PCIDeviceAssignments()const;
    //TODO: caso especial.
    const std::shared_ptr<IBandwidthControl> bandwidthControl();
    const std::shared_ptr<IBandwidthControl> bandwidthControl()const;

    bool tracingEnabled();
    bool tracingEnabled()const;

    const std::string& tracingConfig();
    const std::string& tracingConfig()const;

    bool allowTracingToAccessVM();
    bool allowTracingToAccessVM()const;
    bool autostartEnabled();
    bool autostartEnabled()const;
    unsigned long autostartDelay();
    unsigned long autostartDelay()const;

    VBox::AutostopType autostopType();
    VBox::AutostopType autostopType()const;

    const std::string& defaultFrontend();
    const std::string& defaultFrontend()const;

    bool USBProxyAvailable();
    bool USBProxyAvailable()const;

    VBox::VMProcPriority VMProcessPriority();
    VBox::VMProcPriority VMProcessPriority()const;

    const std::string& paravirtDebug();
    const std::string& paravirtDebug()const;

    const std::string& CPUProfile();
    const std::string& CPUProfile()const;

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
    std::string snapshotFolderProp;
    //! VirtualBox Remote Desktop Extension (VRDE) server object.
    std::shared_ptr<IVRDEServer> VRDEServerProp;
    //! 
    bool emulatedUSBCardReaderEnabledProp;
    //! Array of media attached to this machine.
    std::vector<std::shared_ptr<IMediumAttachment>> mediumAttachmentsProp;
    //! Array of USB controllers attached to this machine.
    std::vector<std::shared_ptr<IUSBController>> USBControllersProp;
    //! Associated USB device filters object.
    std::shared_ptr<IUSBDeviceFilter> USBDeviceFiltersProp;
    //! Associated audio adapter, always present.
    std::shared_ptr<IAudioAdapter> audioAdapterProp;
    //! Array of storage controllers attached to this machine.
    std::vector<std::shared_ptr<IStorageController>> storageControllersProp;
    //! Full name of the file containing machine settings data.
    std::string settingsFilePathProp;
    //! Full name of the file containing auxiliary machine settings data.
    std::string settingsAuxFilePathProp;
    //! Whether the settings of this machine have been modified (but neither yet saved nor discarded).
    bool settingsModifiedProp;
    //! Current session state for this machine.
    VBox::SessionState sessionStateProp;
    //! Name of the session.
    std::string sessionNameProp;
    //! Identifier of the session process.
    unsigned long sessionPIDProp;
    //! Current execution state of this machine.
    VBox::MachineState stateProp;
    //! Timestamp of the last execution state change, in milliseconds since 1970-01-01 UTC.
    long long lastStateChangeProp;
    //! Full path to the file that stores the execution state of the machine when it is in the Saved state.
    std::string stateFilePathProp;
    //! Full path to the folder that stores a set of rotated log files recorded during machine execution.
    std::string logFolderProp;
    //! Current snapshot of this machine. 
    std::shared_ptr<ISnapshot> currentSnapshotProp;
    //! Number of snapshots taken on this machine. Zero means the machine doesn’t have any snapshots.
    unsigned long snapshotCountProp;
    //! Returns true if the current state of the machine is not identical to the state stored in the current snapshot.
    bool currentStateModifiedProp;
    //! Collection of shared folders for this machine (permanent shared folders).
    std::vector<std::shared_ptr<ISharedFolder>> sharedFoldersProp;
    //! Synchronization mode between the host OS clipboard and the guest OS clipboard.
    VBox::ClipboardMode clipboardModeProp;
    //! Sets or retrieves whether clipboard file transfers are allowed or not.
    bool clipboardFileTransfersEnabledProp;
    //! Sets or retrieves the current drag’n drop mode.
    VBox::DnDMode dnDModeProp;
    //! When set to true, the virtual machine becomes a target teleporter the next time it is powered on.
    bool teleporterEnabledProp;
    //! The TCP port the target teleporter will listen for incoming teleportations on.
    unsigned long teleporterPortProp; 
    //! The address the target teleporter will listen on. If set to an empty string, it will listen on all addresses.
    std::string teleporterAddressProp;
    //! The password to check for on the target teleporter.
    std::string teleporterPasswordProp;
    //! The paravirtualized guest interface provider.
    VBox::ParavirtProvider paravirtProviderProp;
    //! When set to true, the RTC device of the virtual machine will run in UTC time, otherwise in local time. Especially Unix guests prefer the time in UTC.
    bool RTCUseUTCProp;
    //! When set to true, the builtin I/O cache of the virtual machine will be enabled.
    bool IOCacheEnabledProp;
    //! Maximum size of the I/O cache in MB.
    unsigned long IOCacheSizeProp;
    //! Array of PCI devices assigned to this machine, to get list of all PCI devices attached to the machine use IConsole::attachedPCIDevices[] attribute, as this attribute is intended to list only devices additional to what described in virtual hardware config.
    std::vector<std::shared_ptr<IPCIDeviceAttachment>> PCIDeviceAssignmentsProp;
    //! Bandwidth control manager.
    std::shared_ptr<IBandwidthControl> bandwidthControlProp;
    //! Enables the tracing facility in the VMM (including PDM devices + drivers).
    bool tracingEnabledProp;
    //! Tracepoint configuration to apply at startup when tracingEnabled is true. 
    std::string tracingConfigProp;
    //! Enables tracepoints in PDM devices and drivers to use the VMCPU or VM structures when firing off trace points.
    bool allowTracingToAccessVMProp;
    //! Enables autostart of the VM during system boot.
    bool autostartEnabledProp;
    //! Number of seconds to wait until the VM should be started during system boot.
    unsigned long autostartDelayProp;
    //! Action type to do when the system is shutting down.
    VBox::AutostopType autostopTypeProp;
    //! Selects which VM frontend should be used by default when launching this VM through the launchVMProcess() method.
    std::string defaultFrontendProp;
    //! Returns whether there is an USB proxy available.
    bool USBProxyAvailableProp;
    //! Sets the priority of the VM process.
    VBox::VMProcPriority VMProcessPriorityProp;
    //! Debug parameters for the paravirtualized guest interface provider.
    std::string paravirtDebugProp;
    //! Experimental feature to select the guest CPU profile. The default is “host”, which indicates the host CPU.
    std::string CPUProfileProp;
};

#endif