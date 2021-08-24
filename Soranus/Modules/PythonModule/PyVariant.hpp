#pragma once

#include "CPyObject.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <string>
#include <vector>

// todo: make an actual pyvariant class

namespace python {
namespace pyvariant {
static double Double(const CPyObject& obj) {
	return 0.0;
}

static std::vector<CPyReference> List(const CPyReference& listObj) {
	std::vector<CPyReference> toBeReturned;
	for (auto&& obj : pybind11::cast<pybind11::list>(listObj.AsPyObject()))
		toBeReturned.push_back(obj.ptr());
	return toBeReturned;
}

static std::string String(const CPyReference& stringObj) {
	return pybind11::str(stringObj.AsPyObject());
}

static std::vector<std::string> StringList(const CPyReference& listObj) {
	std::vector<std::string> toBeReturned;
	for (auto&& obj : List(listObj))
		toBeReturned.push_back(String(obj));
	return toBeReturned;
}

static CPyObject StringToPyObj(const char* string) {
	return PyUnicode_FromString(string);
}
} // namespace pyvariant
} // namespace python