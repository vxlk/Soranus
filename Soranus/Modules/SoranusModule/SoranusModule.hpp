#pragma once

#include <ThreadModule/ThreadModule.hpp>

// Combines modules needed by the Soranus app into a common store
// Each module can then be accessed statically
struct SoranusModule {
	inline static ThreadModule threadModule;
};

// Show the cluster that this component is operating off of
ThreadWrapper RentsThread(const char* name) {
	return SoranusModule::threadModule.Has(name) ? 
		   SoranusModule::threadModule.Get(name) : 
		   SoranusModule::threadModule.AddThread(name);
}