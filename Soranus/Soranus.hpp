#pragma once

// Stoinks.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include "Message.hpp"
#include "Modules/SoranusModule/SoranusModule.hpp"
// The app entry point.  This is responsible for providing an entry function, as well
// as static references to file paths and other app data.
class Soranus {
public:
	Soranus() {
		moduleCollection.threadModule.AddThread("Main Thread");
	}

	// Runs the Soranus application and 
	// @Returns	A message associated with the return result	
	Message::ReturnCode Run();

	ThreadPool& Thread() { return moduleCollection.threadModule.Get("Main Thread"); }

	// A collection of modules associated with a Soranus Application
	SoranusModule moduleCollection;

	bool ProcessFeature(Feature);
	const Feature& FeatureConfiguration() const;

private:
	Feature StartupPlugins() {
		return {
			{},
			{}
		};
	}
	void LoadStartupPlugins();
	Message::ReturnCode PrivateRun();

	const char* m_appName = "Soranus Console Application";
};