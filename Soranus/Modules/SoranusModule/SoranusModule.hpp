#pragma once

#include <ThreadModule/ThreadModule.hpp>
#include <PluginModule/PluginModule.hpp>

// Combines modules needed by the Soranus app into a common store
// Each module can then be accessed statically
struct SoranusModule {
	ThreadModule threadModule;
	PluginModule pluginModule;

	// Show the cluster that this component is operating off of
	/*ThreadWrapper GetThreadCluster(const char* name) {
		return this->threadModule.Has(name) ?
			   this->threadModule.Get(name) :
			   this->threadModule.AddThread(name);
	}*/
};

namespace util {

} // namespace util