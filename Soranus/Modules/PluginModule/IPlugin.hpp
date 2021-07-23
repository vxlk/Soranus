#pragma once

#include <vector>

// Interface to a generic plugin
struct IPlugin {

    // The name of the plugin
    virtual const char* Name() const = 0;

    // Register a plugin
    // Register is called before load
    // todo: what do you want to do here?
    virtual void Register() = 0;

    // Load a plugin
    // Load is called after Register
    // todo: what do you want to do here?
    virtual void Load() = 0;

    // What plugins are required to be loaded before this one?
    // A Load dependency is a dependency in which this plugin will interact
    // with that other plugin directly.
    virtual std::vector<const char*> RequiredLoadedPlugins() { return {}; }

    // What plugins are required to be registered before this one?
    // A Registration dependency is a dependency in which this plugin will require
    // interfaces or actions that are provided by another plugin.  It should *not* interact
    // with that plugin directly.  That would be a load dependency.
    virtual std::vector<const char*> RequiredRegisteredPlugins() { return {}; }
};