#pragma once

#include "PluginCollection.hpp"

#include <vector>

// Will be important in the future, but for now we will take a load if available approach

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
	bool Process(const Feature& feature, const PluginCollection& collection);
	const Feature& Configuration() const { return m_currentConfiguration; }
};