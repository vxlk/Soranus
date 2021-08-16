#pragma once

#include "PluginCollection.hpp"

#include <vector>

struct Feature {
	std::vector<const char*> requestedRegisters;
	std::vector<const char*> requestedLoads;
};

// A feature configuration is an interface for turning plugins on/off in groups 
// or "features" requested by either the app or other plugins.
//
// A "feature" is just a list of plugin names.
class FeatureConfigurationProcessor {
	Feature m_currentConfiguration;
public:
	bool Process(Feature feature, PluginCollection collection);
	const Feature& Configuration() const { return m_currentConfiguration; }
};