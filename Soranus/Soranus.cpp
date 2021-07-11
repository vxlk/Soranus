// Soranus.cpp : Defines the entry point for the application.
//

#include "Soranus.hpp"
#include "Exchange/crypto/ftx/FTXExchange.hpp"

// Stoinks.cpp : Defines the entry point for the application.
//

Message::ReturnCode Soranus::Run() {
	// do stuff
	FTXExchange ftxExchange;
	auto solPrice = ftxExchange.TickerPrice("SOL/USD");
	return Message::ReturnCode::Okay;
}

int main(void)
{
	Soranus appImpl;
	// start with a generic exception ... then if we never get a return 
	// we can throw a generic exception
	Message::ReturnCode appReturnCode = Message::ReturnCode::ExceptionError;
	try {
		appReturnCode = appImpl.Run();
	}
	catch (...) {
		Message::ReturnCodeException(appReturnCode);
	}
	return static_cast<int>(appReturnCode);
}
