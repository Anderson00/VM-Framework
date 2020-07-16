#ifndef VBOX_H
#define VBOX_H

namespace VBox{

    enum FirmwareType{
        BIOS,   //! BIOS Firmware.
        EFI,    //! EFI Firmware, bitness detected basing on OS type
        EFI2,   //! EFI firmware, 32-bit.
        EFI64,  //! EFI firmware, 64-bit.
        EFIDUAL //! EFI firmware, combined 32 and 64-bit.
    };

    enum AccessMode{
        READONLY, READWRITE
    };

    enum DeviceType{
        NULL0,          //! Null value, may also mean “no device” (not allowed for IConsole::getDeviceActivity()).
        Floppy,         //! Floppy device.
        DVD,            //! CD/DVD-ROM device.
        HardDisk,       //! Hard disk device.
        Network,        //! Network device.
        USB,            //! USB device.
        SharedFolder,   //! Shared folder device.
        Graphics3D      //! Graphics device 3D activity.
    };

    enum MachineState{
        Null,                   //! Null value (never used by the API).
        PoweredOff,             //! The machine is not running and has no saved execution state; it has either never been started or been shut down successfully.
        Saved,                  //! The machine is not currently running, but the execution state of the machine has been saved to an external file when it was running, from where it can be resumed.
        Teleported,             //! The machine was teleported to a different host (or process) and then powered off. Take care when powering it on again may corrupt resources it shares with the teleportation target (e.g. disk and network).
        Aborted,                //! The process running the machine has terminated abnormally. This may indicate a crash of the VM process in host execution context, or the VM process has been terminated externally.
        Running,                //! The machine is currently being executed.
        Paused,                 //! Execution of the machine has been paused.
        Stuck,                  //! Execution of the machine has reached the “Guru Meditation” condition. This indicates a severe error in the hypervisor itself.
        Teleporting,            //! The machine is about to be teleported to a different host or process. It is possible to pause a machine in this state, but it will go to the TeleportingPausedVM state and it will not be possible to resume it again unless the teleportation fails.
        LiveSnapshotting,       //! A live snapshot is being taken. The machine is running normally, but some of the runtime configuration options are inaccessible. Also, if paused while in this state it will transition to OnlineSnapshotting and it will not be resume the execution until the snapshot operation has completed.
        Starting,               //! Machine is being started after powering it on from a zero execution state.
        Stopping,               //! Machine is being normally stopped powering it off, or after the guest OS has initiated a shutdown sequence.
        Saving,                 //! Machine is saving its execution state to a file.
        Restoring,              //! Execution state of the machine is being restored from a file after powering it on from the saved execution state.
        TeleportingPausedVM,    //! The machine is being teleported to another host or process, but it is not running. This is the paused variant of the Teleporting state.
        TeleportingIn,          //!Teleporting the machine state in from another host or process.
        DeletingSnapshotOnline, //! Like DeletingSnapshot, but the merging of media is ongoing in the background while the machine is running.
        DeletingSnapshotPaused, //! Like DeletingSnapshotOnline, but the machine was paused when the merging of differencing media was started.
        OnlineSnapshotting,     //! Like LiveSnapshotting, but the machine was paused when the merging of differencing media was started.
        RestoringSnapshot,      //! A machine snapshot is being restored; this typically does not take long.
        DeletingSnapshot,       //! A machine snapshot is being deleted; this can take a long time since this may require merging differencing media. This value indicates that the machine is not running while the snapshot is being deleted.
        SettingUp,              //! Lengthy setup operation is in progress.
        Snapshotting,           //! Taking an (offline) snapshot.
        FirstOnline,            //! Pseudo-state: first online state (for use in relational expressions).
        LastOnline,             //! Pseudo-state: last online state (for use in relational expressions).
        FirstTransient,         //! Pseudo-state: first transient state (for use in relational expressions).
        LastTransient           //! Pseudo-state: last transient state (for use in relational expressions).
    };
};

#include "IWebSessionManager.h"
#include "IHost.h"
#include "ISystemProperties.h"
#include "IMachine.h"
#include "IMedium.h"
#include "IProgress.h"
#include "IGuestOSType.h"
#include "ISharedFolder.h"
#include "IPerformanceCollector.h"
#include "IDHCPServer.h"
#include "INATNetwork.h"
#include "IEventSource.h"
#include "ICloudNetwork.h"
#include "ICloudProviderManager.h"
#include "ISession.h"
#include "IAppliance.h"
#include "IUnattended.h"
#include "IVirtualBox.h"

#endif