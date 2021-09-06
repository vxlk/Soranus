#pragma once

#include <IPlugin.hpp>

struct WinLibData;

class WinPlugin : public IPlugin {
public:
	WinPlugin(const char* dllName, const char* aliasName = "");
	virtual ~WinPlugin();

	virtual const char* Name() const override { return m_aliasName; }
	virtual void Load();
	virtual void Register() = 0;
private:
	const char* addExtensionIfNeeded(const char*);
	const char* m_dllName;
	const char* m_aliasName;
	WinLibData* m_data = nullptr;
};
