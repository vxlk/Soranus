#pragma once

#include "IPlugin.hpp"

#include <memory>

// A container of plugins!
class PluginCollection {
public:
	using iterator = std::vector<std::unique_ptr<IPlugin>>::iterator;
	using const_iterator = std::vector<std::unique_ptr<IPlugin>>::const_iterator;
	iterator begin() { return this->m_loadedPlugins.begin(); }
	iterator end() { return this->m_loadedPlugins.end(); }

	template <class T>
	T* FindPluginT(T pluginType) {
		for (auto&& plugin : m_plugins)
			if (auto p = std::dynamic_pointer_cast<T>(plugin))
				return p;
		return nullptr;
	}
	
	IPlugin* FindPlugin(const char* name) {
		for (auto&& plugin : m_loadedPlugins)
			if (name == plugin->Name())
				return plugin.get();
		return nullptr;
	}

	template <class T>
	void RegisterPlugin(T pluginType) {}
	template <class T>
	void LoadPlugin(T pluginType) {}

private:
	std::vector<std::unique_ptr<IPlugin>> m_loadedPlugins;
	std::vector<std::unique_ptr<IPlugin>> m_registeredPlugins;
};