//
// Created by anderson on 28/12/2020.
//

#ifndef VM_FRAMEWORK_IMACHINETEST_H
#define VM_FRAMEWORK_IMACHINETEST_H

#include "IWebSessionManager.h"
#include "IVirtualBox.h"
#include "IMachine.h"
#include <vector>
#include <memory>

class IMachineTest : public ::testing::Test{
protected:
    void SetUp() override {
        vbox = mn.logon("","");
        machines = vbox->machines();
        machine = machines[0];
    }

    void TearDown() override{
        mn.logoff();
    }

    IWebSessionManager mn;
    std::shared_ptr<IVirtualBox> vbox;
    std::vector<std::shared_ptr<IMachine>> machines;
    std::shared_ptr<IMachine> machine;
};

TEST_F(IMachineTest, machineProperties){
    EXPECT_TRUE(!machine->name().empty());
}

#endif //VM_FRAMEWORK_IMACHINETEST_H
