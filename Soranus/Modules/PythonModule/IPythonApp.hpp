// Soranus.h : Include file for standard system include files,
// or project specific include files.

#pragma once

//#include "WrapPython.hpp"
#include "CPyObject.hpp"
#include "PyVariant.hpp"

namespace python {

class IPythonApp : public CPyInstance {
public:
	IPythonApp() : CPyInstance() {}
	virtual ~IPythonApp() = default;
};

class PythonApp : public IPythonApp {
public:
	PythonApp()
		: IPythonApp()
	{
		// Get system path
		m_sysPath = PySys_GetObject("path");
	}

	virtual ~PythonApp() = default;

	// Add a module to the list of system paths to be searched when loading
	void AddModulePath(const char* newPath) {
		CPyObject dir = PyUnicode_FromString(newPath);
		PyList_Append(m_sysPath, dir);
	}

protected:
	CPyReference m_sysPath = nullptr;
	std::vector<PythonModule> m_modules; // todo: use this
};

} //namespace python