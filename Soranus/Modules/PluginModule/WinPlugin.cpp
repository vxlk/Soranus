#include "WinPlugin.hpp"

#include <windows.h> 
#include <stdio.h> 

#include <string>

struct WinLibData {
    HINSTANCE hinstLib;
    FARPROC ProcAdd;
    BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;
};

WinPlugin::WinPlugin(const char* dllName, const char* aliasName = "") : m_dllName(dllName) {
    if (aliasName == "")
        m_aliasName = dllName;
    else
        m_aliasName = aliasName;
}

WinPlugin::~WinPlugin() {
    if (m_data != nullptr)
        delete m_data;
    auto fFreeResult = FreeLibrary(m_data->hinstLib);
}

// Load a windows dll
void WinPlugin::Load() {
    // todo: handle dll directory!!!
    m_data = new WinLibData();
    m_data->hinstLib = LoadLibrary(TEXT(this->addExtensionIfNeeded(m_dllName)));

    // If the handle is valid, try to get the function address.

    if (m_data->hinstLib != nullptr)
    {
        m_data->ProcAdd = (FARPROC)GetProcAddress(m_data->hinstLib, this->addExtensionIfNeeded(m_dllName));

        // If the function address is valid, call the function.

        if (NULL != m_data->ProcAdd)
        {
            m_data->fRunTimeLinkSuccess = TRUE;
        }
    }
}

const char* WinPlugin::addExtensionIfNeeded(const char* incomingName) {
    std::string nameWrapper = incomingName;
    if (std::find(nameWrapper.begin(), nameWrapper.end(), ".dll") != nameWrapper.end())
        return incomingName;
    else return std::string(nameWrapper + ".dll").c_str();
}