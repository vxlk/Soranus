// Soranus.cpp : Defines the entry point for the application.
//

#include "Soranus.hpp"
#include "Exchange/crypto/ftx/FTXExchange.hpp"

#pragma warning( push )
#pragma warning( disable : 4101 ) // warning C4101: 'appReturnCode': unreferenced local variable
								  // Dunno why it thinks this is a problem, so we are disabling it

Message::ReturnCode Soranus::Run() {
	auto& pool = this->Thread();
	auto& genThread = this->moduleCollection.threadModule.Get("General Thread");
	auto& mainThread = this->moduleCollection.threadModule.Get("Main Thread");

	this->LoadStartupPlugins();

	auto runFuture = this->Thread().enqueue([this]() { 
		auto result = this->PrivateRun(); 
		return result;
	});
	// while (true) {}
	runFuture.wait();
	//return Message::ReturnCode::Okay;
	return runFuture.get();
}

Message::ReturnCode Soranus::PrivateRun() {
	// do stuff
	FTXExchange ftxExchange;
	auto solPrice = ftxExchange.TickerPrice("SOL/USD");
	return Message::ReturnCode::Okay;
}

void Soranus::LoadStartupPlugins() {
	this->ProcessFeature(this->StartupPlugins());
}

bool Soranus::ProcessFeature(Feature feature) {
	return this->moduleCollection.pluginModule.featureConfiguration.Process(
		std::move(feature), 
		std::move(this->moduleCollection.pluginModule.pluginCollection));
}
const Feature& Soranus::FeatureConfiguration() const {
	return this->moduleCollection.pluginModule.featureConfiguration.Configuration();
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

#pragma warning( pop )
