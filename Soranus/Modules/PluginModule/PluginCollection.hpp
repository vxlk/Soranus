#pragma once

#include "IPlugin.hpp"

#include <memory>
#include <mutex>

// A container of plugins!
class PluginCollection {
public:
	using plugin_list_t = std::vector<std::unique_ptr<IPlugin>>;
	using iterator = plugin_list_t::iterator;
	using const_iterator = plugin_list_t::const_iterator;
	
	iterator begin() { return this->m_loadedPlugins.begin(); }
	iterator end() { return this->m_loadedPlugins.end(); }

	PluginCollection() noexcept = default;
	~PluginCollection() noexcept = default;

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
	std::vector<std::string> m_filePathsToSearch; //todo: not using!
	std::mutex m_pluginListMutex;
};