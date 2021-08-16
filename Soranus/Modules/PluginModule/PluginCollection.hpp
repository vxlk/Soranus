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
	void RegisterPlugin() {
		T pluginType;
		m_registeredPlugins.push_back(std::move(pluginType));
	}
	template <class T>
	void LoadPlugin() {
		T pluginType;
		if (auto p = this->FindRegisteredPluginT<T>(pluginType) == nullptr)
			this->RegisterPlugin(p);
		m_loadedPlugins.push_back(std::move(pluginType));
	}

private:
	template <typename T>
	IPlugin* FindLoadedPluginT(T t) {
		for (auto&& plugin : m_loadedPlugins)
			if (auto p = std::dynamic_pointer_cast<T>(plugin))
				return p;
		return nullptr;
	}
	template <typename T>
	IPlugin* FindRegisteredPluginT(T t) {
		for (auto&& plugin : m_registeredPlugins)
			if (auto p = std::dynamic_pointer_cast<T>(plugin))
				return p;
		return nullptr;
	}
	std::vector<std::unique_ptr<IPlugin>> m_loadedPlugins;
	std::vector<std::unique_ptr<IPlugin>> m_registeredPlugins;
};