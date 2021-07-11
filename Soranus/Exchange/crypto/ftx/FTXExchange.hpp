// Soranus.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <IPythonApp.hpp>
#include <IExchange.hpp>

#include <exception>

class FTXExchange : public python::PythonApp, public IExchange {
public:
	explicit FTXExchange(void);
	virtual ~FTXExchange() = default;

	// IExchange

	// Return the name of the exchange
	virtual const char* Name() const override { return "FTX Exchange"; }
	// Return the amount of funds (USD) available for purchase
	virtual double AvailableFunds() { throw std::exception("Not implemented"); return false; }
	// Return the amount of funds (USD) invested through this exchange
	// (can be in multiple assets)
	virtual double InvestedFunds() { throw std::exception("Not implemented"); return false; }
	// Buy an amount of a certain ticker in (USD)
	virtual bool Buy(const double amount, const char* ticker) { throw std::exception("Not implemented"); return false; }
	// Sell an amount of a certain ticker in (USD)
	virtual bool Sell(const double amount, const char* ticker) { throw std::exception("Not implemented"); return false; }

	virtual const double TickerPrice(const char* ticker) override;
private:
	python::CPyObject m_pModuleName = python::pyvariant::StringToPyObj("ftx_api");
	python::CPyObject m_pModule = nullptr;
};