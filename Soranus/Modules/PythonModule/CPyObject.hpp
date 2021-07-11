// Soranus.h : Include file for standard system include files,
// or project specific include files.

#pragma once

//#include "WrapPython.hpp"

#include <Python.h>

#include <vector>
#include <map>
#include <iostream>

namespace python {

class CPyInstance {
public:
	CPyInstance() {
		Py_Initialize();
	}

	virtual ~CPyInstance() {
		Py_Finalize();
	}
};

// A common base class for non-owning as well as owning cpy objects
struct ICPyObject {
	virtual ~ICPyObject() = default;

	virtual PyObject* AsPyObject() const = 0;
	virtual PyObject*& AsPyObject() = 0;
};

// Non-owning wrapper around python object
class CPyReference : public ICPyObject {
	PyObject* p = nullptr;
public:
	CPyReference(PyObject* _p) : p(_p)
	{}
	~CPyReference() = default;

	PyObject* AsPyObject() const override {
		return p;
	}

	PyObject*& AsPyObject() override {
		return p;
	}

	PyObject* operator ->()
	{
		return p;
	}

	bool is()
	{
		return p ? true : false;
	}

	operator PyObject* ()
	{
		return p;
	}

	PyObject* operator = (PyObject* pp)
	{
		p = pp;
		return p;
	}

	operator bool()
	{
		return p ? true : false;
	}
};

// Owning wrapper around a python object
class CPyObject : public ICPyObject
{
	PyObject* p = nullptr;
public:
	CPyObject() : p(nullptr)
	{}

	CPyObject(PyObject* _p) : p(_p)
	{}


	~CPyObject() {
		Release();
	}

	PyObject* AsPyObject() const override {
		return p;
	}

	PyObject*& AsPyObject() override {
		return p;
	}

	// return a reference wrapper around this object
	CPyReference Ref() const { return CPyReference(p); }

	PyObject* AddRef() {
		if (p)
		{
			Py_INCREF(p);
		}
		return p;
	}

	void Release() {
		if (p)
		{
			try {
				Py_DECREF(p);
			}
			catch (...) {
				// will leave this non-exceptional for now
				std::cout << "Could not free python memory, you do not own this object!";
			}
		}

		p = NULL;
	}

	PyObject* operator ->() {
		return p;
	}

	bool is() {
		return p ? true : false;
	}

	operator PyObject* () {
		return p;
	}

	PyObject* operator = (PyObject* pp) {
		p = pp;
		return p;
	}

	operator bool() {
		return p ? true : false;
	}
};

// todo: use these methods for python apis to reduce code bloat
// and improve organization

struct PythonMethod {
	const char* methodName;
	std::vector<PyObject*> arguments;
	bool Call() {

	}
};

struct PythonModule {
	const char* moduleName;
	const char* modulePath;
	bool isLoaded = false;
	std::map<const char*, PythonMethod> methods;
};

} //namespace python