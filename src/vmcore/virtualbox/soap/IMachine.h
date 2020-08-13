#ifndef IMACHINE_H
#define IMACHINE_H

#include "IObject.h"
#include "IVirtualBox.h"

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
    IMachine(std::string key) : IObject(key) {}
private:
    //! Associated parent object.
    IVirtualBox parent;

    //! Overridden VM Icon details.
    std::vector<long> icon;

    //! Whether this virtual machine is currently accessible or not.
    bool accessible;
};

#endif