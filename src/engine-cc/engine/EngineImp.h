#pragma once
#include "IEngine.h"

class EngineImp : public IEngine
{
public:
	EngineImp();
	~EngineImp();

	virtual int random(int m, int n);
};

