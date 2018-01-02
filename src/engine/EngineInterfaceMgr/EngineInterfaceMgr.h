#pragma once
#include <windows.h>

class IEngine;
class EngineInterfaceMgr
{
public:
	EngineInterfaceMgr();
	~EngineInterfaceMgr();

	IEngine* GetEngine();
	HRESULT CreateEngine();
	HRESULT ReleaseEngine();

private:
	HMODULE m_hModule;
	IEngine* m_pEngine;
};

