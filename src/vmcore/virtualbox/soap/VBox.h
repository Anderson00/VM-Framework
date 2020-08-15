#ifndef VBOX_H
#define VBOX_H

#include <iostream>
#include <string>


namespace VBox{
    
    using SoapObject = struct soap;

    enum class SessionState{
        Null,       //! Null value (never used by the API).
        UNLOKED,    //! In IMachine::sessionState, this means that the machine is not locked for any sessions.
        LOCKED,     //! In IMachine::sessionState, this means that the machine is currently locked for a session, whose process identifier can then be found in the IMachine::sessionPID attribut
        SPAWNING,   //! A new process is being spawned for the machine as a result of IMachine::launchVMProcess() call.
        UNLOCKING   //! The session is being unlocked.
    };

    enum class SessionType{
        Null,       //! Null value (never used by the API).
        WRITE_LOCK, //! Session has acquired an exclusive write lock on a machine using IMachine::lockMachine().
        REMOTE,     //! Session has launched a VM process using IMachine::launchVMProcess().
        SHARED      //! Session has obtained a link to another session using IMachine::lockMachine().
    };

    enum FirmwareType{
        BIOS,   //! BIOS Firmware.
        EFI,    //! EFI Firmware, bitness detected basing on OS type
        EFI2,   //! EFI firmware, 32-bit.
        EFI64,  //! EFI firmware, 64-bit.
        EFIDUAL //! EFI firmware, combined 32 and 64-bit.
    };

    enum AccessMode{
        READ_ONLY, READ_WRITE
    };

    enum DeviceType{
        NULL0,          //! Null value, may also mean “no device” (not allowed for IConsole::getDeviceActivity()).
        FLOPPY,         //! Floppy device.
        DVD,            //! CD/DVD-ROM device.
        HARD_DISK,      //! Hard disk device.
        NETWORK,        //! Network device.
        USB,            //! USB device.
        SHARED_FOLDER,  //! Shared folder device.
        GRAPHICS3D      //! Graphics device 3D activity.
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

    enum PointingHIDType{
        NONE,              //! No mouse.
        PS2Mouse,          //! PS/2 auxiliary device, a.k.a. mouse.
        USBMouse,          //! USB mouse (relative pointer)
        USBTablet,          //! USB tablet (absolute pointer). Also enables a relative USB mouse in addition.
        ComboMouse,        //! Combined device, working as PS/2 or USB mouse, depending on guest behavior. Using this device can have negative performance implications.
        USBMultiTouch      //! USB multi-touch device. Also enables the USB tablet and mouse devices.
    };

    enum KeyboardHIDType{
        None,              //! No keyboard.
        PS2Keyboard,       //! PS/2 keyboard.
        USBKeyboard,       //! USB keyboard.
        ComboKeyboard      //! Combined device, working as PS/2 or USB keyboard, depending on guest behavior. Using of such device can have negative performance implications.
    };

    enum class ChipsetType{
        Null,              //! null value. Never used by the API.
        PIIX3,             //! A PIIX3 (PCI IDE ISA Xcelerator) chipset.
        ICH9               //! A ICH9 (I/O Controller Hub) chipset.
    };

    enum class ClipboardMode{
        Disabled,
        HostToGuest,
        GuestToHost,
        Bidirectional
    };

    enum class DnDMode{
        Disabled,
        HostToGuest,
        GuestToHost,
        Bidirectional
    };

    enum class ParavirtProvider{
        None,           //! No provider is used.
        Default,        //! A default provider is automatically chosen according to the guest OS type.
        Legacy,         //! Used for VMs which didn’t used to have any provider settings. Usually interpreted as None for most VMs.
        Minimal,        //! A minimal set of features to expose to the paravirtualized guest.
        HyperV,         //! Microsoft Hyper-V.
        KVM             //! Linux KVM.
    };
    
    enum class AutostopType{
        Disabled,       //! Stopping the VM during system shutdown is disabled.
        SaveState,      //! The state of the VM will be saved when the system shuts down.
        PowerOff,       //! The VM is powered off when the system shuts down.
        AcpiShutdown    //! An ACPI shutdown event is generated.
    };

    enum class VMProcPriority{
        Invalid,        //! Invalid priority, do not use.
        Default,        //! Default process priority determined by the OS.
        Flat,           //! Assumes a scheduling policy which puts the process at the default priority and with all thread at the same priority
        Low,            //! Assumes a scheduling policy which puts the process mostly below the default priority of the host OS.
        Normal,         //! Assume a scheduling policy which shares the CPU resources fairly with other processes running with the default priority of the host OS.
        High            //! Assumes a scheduling policy which puts the task above the default priority of the host OS. This policy might easily cause other tasks in the system to starve.
    };

    enum class StorageBus{
        Null,
        IDE,
        SATA,
        SCSI,
        Floppy,
        SAS,
        USB,
        PCIe,
        VirtioSCSI
    };

    enum class USBControllerType{
        Null,
        OHCI,
        EHCI,
        XHCI,
        Last
    };

    enum class CloneMode{
        MachineState,           //! Clone the state of the selected machine.
        MachineAndChildStates,  //! Clone the state of the selected machine and its child snapshots if present.
        AllStates               //! Clone all states (including all snapshots) of the machine, regardless of the machine object used.
    };

    enum class CloneOptions{
        Link,               //! Create a clone VM where all virtual disks are linked to the original VM.
        KeepAllMACs,        //! Don’t generate new MAC addresses of the attached network adapters.
        KeepNATMACs,        //! Don’t generate new MAC addresses of the attached network adapters when they are using NAT.
        KeepDiskNames,      //! Don’t change the disk names.
        KeepHwUUIDs         //! Don’t change UUID of the machine hardware.
    };

    enum class CPUPropertyType{
        Null,                   //! Null value (never used by the API).
        PAE,                    //! This setting determines whether VirtualBox will expose the Physical Address Extension (PAE) feature of the host CPU to the guest. Note that in case PAE is not available, it will not be reported.
        LongMode,               //! This setting determines whether VirtualBox will advertise long mode (i.e. 64-bit guest support) and let the guest enter it.
        TripleFaultReset,       //! This setting determines whether a triple fault within a guest will trigger an internal error condition and stop the VM (default) or reset the virtual CPU/VM and continue execution. 
        APIC,                   //! This setting determines whether an APIC is part of the virtual CPU. This feature can only be turned off when the X2APIC feature is off.
        X2APIC,                 //! This setting determines whether an x2APIC is part of the virtual CPU. Since this feature implies that the APIC feature is present, it automatically enables the APIC feature when set.
        IBPBOnVMExit,           //! If set, force an indirect branch prediction barrier on VM exits if the host CPU supports it. This setting will significantly slow down workloads causing many VM exits, so it is only recommended for situation where there is a real need to be paranoid.
        IBPBOnVMEntry,          //! If set, force an indirect branch prediction barrier on VM entry if the host CPU supports it. This setting will significantly slow down workloads causing many VM exits, so it is only recommended for situation where there is a real need to be paranoid.
        HWVirt,                 //! Enabled the hardware virtualization (AMD-V/VT-x) feature on the guest CPU. This requires hardware virtualization on the host CPU.
        SpecCtrl,               //! If set, the speculation control CPUID bits and MSRs, when available on the host, are exposed to the guest. Depending on the host CPU and operating system, this may significantly slow down workloads causing many VM exits.
        SpecCtrlByHost,         //! If set, the speculation controls are managed by the host. This is intended for guests which do not set the speculation controls themselves. Note! This has not yet been implemented beyond leaving everything to the host OS.
        L1DFlushOnEMTScheduling,//! If set and the host is affected by CVE-2018-3646, flushes the level 1 data cache when the EMT is scheduled to do ring-0 guest execution. There could be a small performance penalty for certain typs of workloads. For security reasons this setting will be enabled by default.
        L1DFlushOnVMEntry,      //! If set and the host is affected by CVE-2018-3646, flushes the level 1 data on every VM entry. This setting may significantly slow down workloads causing many VM exits, so it is only recommended for situation where there is a real need to be paranoid.  
        MDSClearOnEMTScheduling,//! If set and the host is affected by CVE-2018-12126, CVE-2018- 12127, or CVE-2018-12130, clears the relevant MDS buffers when the EMT is scheduled to do ring-0 guest execution. There could be a small performance penalty for certain typs of workloads. For security reasons this setting will be enabled by default.
        MDSClearOnVMEntry,      //! If set and the host is affected by CVE-2018-12126, CVE-2018-12127, or CVE-2018-12130, clears the relevant MDS buffers on every VM entry. This setting may slow down workloads causing many VM exits, so it is only recommended for situation where there is a real need to be paranoid.

    };

    enum class ParavirtProvider{
        None,       //! No provider is used.
        Default,    //! A default provider is automatically chosen according to the guest OS type. 
        Legancy,    //! Used for VMs which didn’t used to have any provider settings. Usually interpreted as None for most VMs.
        Minimal,    //! A minimal set of features to expose to the paravirtualized guest.
        HyperV,     //! Microsoft Hyper-V.
        KVM         //! Linux KVM.
    };

    enum class HWVirtExPropertyType{
        Null,                   //! Null value (never used by the API).
        Enabled,                //! Whether hardware virtualization (VT-x/AMD-V) is enabled at all. If such extensions are not available, they will not be used.
        VPID,                   //! Whether VT-x VPID is enabled. If this extension is not available, it will not be used.
        NestedPaging,           //! Whether Nested Paging is enabled. If this extension is not available, it will not be used.
        UnrestrictedExecution,  //! Whether VT-x unrestricted execution is enabled. If this feature is not available, it will not be used.
        LargePages,             //! Whether large page allocation is enabled; requires nested paging and a 64-bit host.  
        Force,                  //! Whether the VM should fail to start if hardware virtualization (VT-x/AMD-V) cannot be used. If not set, there will be an automatic fallback to software virtualization.
        UseNativeApi            //! Use the native hypervisor API instead of the VirtualBox one (HM) for VT-X/AMDV. This is ignored if Enabled isn’t set.  
    };

    enum class LockType{
        Null,
        Shared,
        Write,
        VM
    };
};


#endif