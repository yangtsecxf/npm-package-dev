#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

extern "C" ENGINE_API HRESULT CreateIEngineInterface(void*& pInterface);
extern "C" ENGINE_API HRESULT ReleaseIEngineInterface(void*& pInterface);

class IEngine
{
public:
	virtual int random(int m, int n) = 0;
};

