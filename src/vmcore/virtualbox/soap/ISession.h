#ifndef ISESSION_H
#define ISESSION_H

#include "VBox.h"
#include "IObject.h"
//#include "IMachine.h"
#include "IConsole.h"
#include <memory>

class IMachine;

class ISession : public IObject{
public:
    ISession(std::string sessKey) : IObject(sessKey) {}

    void unlockMachine();

    VBox::SessionState state();
    VBox::SessionState state()const;
    VBox::SessionType type();
    VBox::SessionType type()const;
    const std::string& name(std::string str); // Set
    const std::string& name();
    const std::string& name()const;
    std::shared_ptr<IMachine> machine();
    std::shared_ptr<IConsole> console();

private:
    VBox::SessionState stateProp;
    VBox::SessionType typeProp;
    std::string nameProp;
    std::shared_ptr<IMachine> machineProp;
    std::shared_ptr<IConsole> consoleProp;
};

#endif