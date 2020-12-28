#ifndef VBOX_H
#define VBOX_H

#include <iostream>
#include <string>


namespace VBox{
    
    using SoapObject = struct soap;

    enum class HostNetworkInterfaceType{
        Bridged,
        HostOnly
    };

    enum class ProcessorFeature{
        HWVirtEx,
        PAE,
        LongMode,
        NestedPaging,
        UnrestrictedGuest,
        NestedHWVirt
    };

    enum class AudioDriverType{
        Null,         //! Null value, also means “dummy audio driver”.
        WinMM,        //! Windows multimedia (Windows hosts only, not supported at the moment).
        OSS,          //! Open Sound System (Linux / Unix hosts only).
        ALSA,         //! Advanced Linux Sound Architecture (Linux hosts only).
        DirectSound,  //! DirectSound (Windows hosts only).
        CoreAudio,    //! CoreAudio (Mac hosts only).
        MMPM,         //! Reserved for historical reasons.
        Pulse,        //! PulseAudio (Linux hosts only).
        SolAudio      //! Solaris audio (Solaris hosts only, not supported at the moment).
    };

    enum class ProxyMode{
        System,     //! Use the system proxy settings as far as possible.
        NoProxy,    //! Direct connection to the Internet.
        Manual      //! Use the manual proxy from ISystemProperties::proxyURL.
    };

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

    enum class VFSType{
        File,
        Cloud,
        S3,
        WebDav
    };

    enum class ImportOptions{
        KeepAllMACs, //! Don’t generate new MAC addresses of the attached network adapters.
        KeepNATMACs, //! Don’t generate new MAC addresses of the attached network adapters when they are using NAT.
        ImportToVDI  //! Import all disks to VDI format
    };

    enum class ExportOptions{
        CreateManifest,     //! Write the optional manifest file (.mf) which is used for integrity checks prior import.
        ExportDVDImages,    //! Export DVD images. Default is not to export them as it is rarely needed for typical VMs.
        StripAllMACs,       //! Do not export any MAC address information. Default is to keep them to avoid losing information which can cause trouble after import, at the price of risking duplicate MAC addresses, if the import options are used to keep them.
        StripAllNonNATMACs  //! Do not export any MAC address information, except for adapters using NAT. Default is to keep them to avoid losing information which can cause trouble after import, at the price of risking duplicate MAC addresses, if the import options are used to keep them.
    };

    enum class RecordingAudioCodec{
        None,   //! No codec set.
        WavPCM, //! WAV format, linear PCM, uncompressed. Not implemented yet.
        Opus    //! Opus Audio.
    };

    enum class RecordingVideoCodec{
        None, //! No codec set.
        VP8,  //! VP8 codec.
        VP9,  //! VP9 codec. Not implemented yet.
        AV1   //! AV1 codec. Not implemented yet.
    };

    enum class RecordingVideoScalingMethod{
        None,            //! No scaling performed.
        NearestNeighbor, //! Performs scaling via nearest-neighbor interpolation. Not yet implemented.
        Bilinear,        //! Performs scaling via bilinear interpolation. Not yet implemented.
        Bicubic          //! Performs scaling via bicubic interpolation. Not yet implemented.
    };

    enum class RecordingVideoRateControlMode{
        CBR, //! Constant bit rate (CBR).
        VBR, //! Variable bit rate (VBR). Not yet implemented.
    };

    enum class GraphicsControllerType{
        Null,    //! Reserved value, invalid.
        VBoxVGA, //! VirtualBox VGA device.
        VMSVGA,  //! VMware SVGA II device.
        VBoxSVGA //! VirtualBox VGA device with VMware SVGA II extensions.
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

    enum class NetworkAttachmentType{
        Null,       //! Null value, also means “not attached”.
        NAT,
        Bridged,
        Internal,
        HostOnly,
        Generic,
        NATNetwork,
        Cloud
    };

    enum class NetworkAdapterType{
        Null,       //! Null value (never used by the API).
        Am79C970A,  //! AMD PCNet-PCI II network card (Am79C970A).
        Am79C973,   //! AMD PCNet-FAST III network card (Am79C973).
        I82540EM,   //! Intel PRO/1000 MT Desktop network card (82540EM).
        I82543GC,   //! Intel PRO/1000 T Server network card (82543GC).
        I82545EM,   //! Intel PRO/1000 MT Server network card (82545EM).
        Virtio,     //! Virtio network device.
        Am79C960,   //! AMD PCnet-ISA/NE2100 network card (Am79C960).
        Virtio_1_0 //! Virtio 1.0 network device.
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

    enum class AudioControllerType{
        AC97,
        SB16,
        HDA
    };

    enum class StorageControllerType{
        Null,        //! null value. Never used by the API.
        LsiLogic,    //! A SCSI controller of the LsiLogic variant.
        BusLogic,    //! A SCSI controller of the BusLogic variant.
        IntelAhci,   //! An Intel AHCI SATA controller; this is the only variant for SATA.
        PIIX3,       //! An IDE controller of the PIIX3 variant.
        PIIX4,       //! An IDE controller of the PIIX4 variant.
        ICH6,        //! An IDE controller of the ICH6 variant.
        I82078,      //! A floppy disk controller; this is the only variant for floppy drives.
        LsiLogicSas, //!A variant of the LsiLogic controller using SAS.
        USB,         //! Special USB based storage controller.
        NVMe,        //! An NVMe storage controller.
        VirtioSCSI   //! Virtio SCSI storage controller.
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

    enum class PortMode{
        Disconnected, //! Virtual device is not attached to any real host device.
        HostPipe,     //! Virtual device is attached to a host pipe.
        HostDevice,   //! Virtual device is attached to a host device.
        RawFile,      //! Virtual device is attached to a raw file.
        TCP           //! Virtual device is attached to a TCP socket.
    };

    enum class UartType{
        U16450,  //! The most basic emulated UART which doesn’t support FIFO operation.
        U16550A, //! The successor of the 16450 UART introducing a 16 byte FIFO to reduce operational overhead.
        U16750,  //! This UART developed by Texas Instruments introduced a 64 byte FIFO and hardware flow control.
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

    enum class BitmapFormat{
        Opaque,     //! Unknown buffer format (the user may not assume any particular format of the buffer).
        BGR,        //! Generic BGR format without alpha channel. Pixel layout depends on the number of bits per pixel: 32 - bits 31:24 undefined, bits 23:16 R, bits 15:8 G, bits 7:0 B; 16 - bits 15:11 R, bits 10:5 G, bits 4:0 B.
        BGR0,       //! 4 bytes per pixel: B, G, R, 0.
        BGRA,       //! 4 bytes per pixel: B, G, R, A.
        RGBA,       //! 4 bytes per pixel: R, G, B, A.
        PNG,        //! PNG image.
        JPEG        //! JPEG image.
    };

    enum class CleanupMode{
        UnregisterOnly,
        DetachAllReturnNone,
        DetachAllReturnHardDisksOnly,
        Full
    };
};


#endif