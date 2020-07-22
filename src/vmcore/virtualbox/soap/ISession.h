#ifndef ISESSION_H
#define ISESSION_H

#include "VBox.h"
#include "IConsole.h"
#include <memory>

namespace VBox{
    class ISession : public IObject{
    public:
        ISession(std::string sessKey) : IObject(sessKey) {}

        void unlockMachine();

        VBox::SessionState state();
        VBox::SessionType type();
        std::string name(std::string str);
        std::string name();
        std::shared_ptr<VBox::IMachine> machine();
        std::shared_ptr<VBox::IConsole> console();

    private:
        //std::shared_ptr<VBox::IMachine> machine;
        //std::shared_ptr<VBox::IConsole> console;
    };
};

#endif