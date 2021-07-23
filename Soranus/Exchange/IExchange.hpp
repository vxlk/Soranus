// The interface to an exchange - either crypto or traditional
class IExchange {
public:
	virtual ~IExchange() = default;
	// Return the name of the exchange
	virtual const char* Name() const = 0;

	// can these be const if they call python?

	// Return the amount of funds (USD) available for purchase
	virtual double AvailableFunds() = 0;
	// Return the amount of funds (USD) invested through this exchange
	// (can be in multiple assets)
	virtual double InvestedFunds() = 0;
	// Buy an amount of a certain ticker in (USD)
	virtual bool Buy(const double amount, const char* ticker) = 0;
	// Sell an amount of a certain ticker in (USD)
	virtual bool Sell(const double amount, const char* ticker) = 0;

	virtual const double TickerPrice(const char* ticker) = 0;
};