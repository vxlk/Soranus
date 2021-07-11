#pragma once

// Stoinks.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include "Message.hpp"

// The app entry point.  This is responsible for providing an entry function, as well
// as static references to file paths and other app data.
class Soranus {
public:
	Message::ReturnCode Run();
};