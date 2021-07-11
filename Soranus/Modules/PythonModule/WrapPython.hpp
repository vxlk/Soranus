#pragma once
//https://github.com/pybind/pybind11/issues/1295
#ifdef _DEBUG
# ifndef BOOST_DEBUG_PYTHON
#  undef _DEBUG // Don't let Python force the debug library just because we're debugging.
#  define DEBUG_UNDEFINED_FROM_WRAP_PYTHON_H
# endif
#endif