#ifndef IVIRTUAL_BOX_H
#define IVIRTUAL_BOX_H

#include "VBox.h"
#include <iostream>
#include <string>
#include <vector>


class IVirtualBox{
public:
    IVirtualBox();



private:
    std::wstring version;
    std::wstring versionNormalized;
    std::wstring revision;
    std::wstring packageType;
    std::wstring APIVersion;
    std::wstring APIRersion;
    std::wstring homeFolder;
    std::wstring settingsFilePath;
    VBox::IHost host;
    VBox::ISystemProperties systemProperties;
    std::vector<VBox::IMachine*> machines;
    std::vector<std::wstring> machineGroups;
    std::vector<VBox::IMedium> hardDisks;
    std::vector<VBox::IMedium> DVDImages;
    std::vector<VBox::IMedium> floppyImages;
};

#endif