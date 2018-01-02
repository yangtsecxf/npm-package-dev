#include "EngineInterfaceMgr.h"
#include "../../include/IEngine.h"
#include <string>
using namespace std;

#ifndef DEBUG
const string kEngineDllName = "engine.dll";
#else
const string kEngineDllName = "engine.dll";
#endif

EngineInterfaceMgr::EngineInterfaceMgr()
	: m_hModule(nullptr)
	, m_pEngine(nullptr)
{
}


EngineInterfaceMgr::~EngineInterfaceMgr()
{
	ReleaseEngine();
}

IEngine* EngineInterfaceMgr::GetEngine()
{
	if (nullptr == m_pEngine)
	{
		if (S_OK != CreateEngine())
		{
			return nullptr;
		}
	}

	return m_pEngine;
}

HRESULT EngineInterfaceMgr::CreateEngine()
{
	// load dll
	if (nullptr == m_hModule)
	{
		m_hModule = LoadLibraryA(kEngineDllName.c_str());
		if (nullptr == m_hModule)
		{
			return S_FALSE;
		}
	}

	// check
	if (nullptr != m_pEngine)
	{
		ReleaseEngine();
	}

	// create engine interface
	typedef HRESULT(*P_CREATE_INTERFACE_FUNC)(void*&);
	P_CREATE_INTERFACE_FUNC pCreateInterfaceFunc = nullptr;
	pCreateInterfaceFunc = (P_CREATE_INTERFACE_FUNC)(GetProcAddress(m_hModule, "CreateIEngineInterface"));
	if (nullptr == pCreateInterfaceFunc) // get create func failed
	{
		return S_FALSE;
	}

	pCreateInterfaceFunc((void*&)m_pEngine);
	if (nullptr == m_pEngine) // create interface failed
	{
		return S_FALSE;
	}

	return S_OK;
}

HRESULT EngineInterfaceMgr::ReleaseEngine()
{
	// release engine interface
	typedef HRESULT(*P_FUNC_RELEASE_INTERFACE)(void*&);
	P_FUNC_RELEASE_INTERFACE pFuncReleaseInterface = nullptr;
	pFuncReleaseInterface = (P_FUNC_RELEASE_INTERFACE)(GetProcAddress(m_hModule, "ReleaseIEngineInterface"));
	if (nullptr == pFuncReleaseInterface) // get create func failed
	{
		return S_FALSE;
	}

	HRESULT rt = pFuncReleaseInterface((void*&)m_pEngine);
	if (rt == S_OK)
	{
		m_hModule = nullptr;
		m_pEngine = nullptr;
	}

	return rt;
}
