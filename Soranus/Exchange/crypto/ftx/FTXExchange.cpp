#include "FTXExchange.hpp"

#include <string>

FTXExchange::FTXExchange(void) {
	// todo: abstract out to json
	this->AddModulePath("C:\\Users\\small\\Desktop\\Soranus\\Soranus\\Exchange\\crypto\\ftx");

	// hardcoded
	char fileName[] = "C:\\Users\\small\\Desktop\\Soranus\\Soranus\\Exchange\\crypto\\ftx\\ftx_api_test.py";
	auto fp = _Py_fopen(fileName, "r");
	PyRun_SimpleFileEx(fp, fileName, 0);
	
	// PyRun_SimpleFile(fp, fileName);

	m_pModule = PyImport_Import(m_pModuleName);
	
	if (m_pModule)
	{
		python::CPyObject pFunc = PyObject_GetAttrString(m_pModule, "ws_start_all");
		if (pFunc && PyCallable_Check(pFunc))
		{
			python::CPyObject pValue = PyObject_CallObject(pFunc, nullptr);
		}
		else
		{
			throw std::exception("Could not start FTX Web socket service");
		}

	}
	else
	{
		throw std::exception("FTX MODULE COULD NOT BE LOADED");;
	}
}

const double FTXExchange::TickerPrice(const char* ticker) {
	auto pFunc = PyObject_GetAttrString(m_pModule, "ws_ticker_price");
	if (pFunc && PyCallable_Check(pFunc))
	{
		python::CPyObject pValue = PyObject_CallFunction(pFunc, "s", ticker);
		return PyFloat_AsDouble(pValue);
	}
	else {
		throw std::exception(std::string(std::string("Could not get FTX Ticker price: ") + std::string(ticker)).c_str());
		return -1;
	}
}