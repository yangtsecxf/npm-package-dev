// engine.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "EngineImp.h"

extern "C" ENGINE_API HRESULT CreateIEngineInterface(void*& pInterface)
{
	if (nullptr != pInterface)
	{
		ReleaseIEngineInterface(pInterface);
	}

	pInterface = new EngineImp();

	return S_OK;
}

extern "C" ENGINE_API HRESULT ReleaseIEngineInterface(void*& pInterface)
{
	EngineImp* pIF = (EngineImp*)(pInterface);
	if (nullptr == pIF)
	{
		return S_FALSE;
	}
	else
	{
		delete pIF;
		pIF = nullptr;
		return S_OK;
	}
}

