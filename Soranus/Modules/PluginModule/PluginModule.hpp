#include "PluginCollection.hpp"
#include "FeatureConfiguration.hpp"

// Export the sub-modules required to use plugins in your application
struct PluginModule {
	PluginCollection pluginCollection;
	FeatureConfigurationProcessor featureConfiguration;

	// Add your high level plugin interactions here!
};