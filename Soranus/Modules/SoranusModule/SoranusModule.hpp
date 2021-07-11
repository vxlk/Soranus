#pragma once

#include <ThreadModule/ThreadModule.hpp>

// Combines modules needed by the Soranus app into a common store
// Each module can then be accessed statically
struct SoranusModule {
	inline static ThreadModule threadModule;
};