#include "stdafx.h"
#include "EngineImp.h"
#include <stdlib.h>
#include <time.h>

EngineImp::EngineImp()
{
}


EngineImp::~EngineImp()
{
}

int EngineImp::random(int m, int n)
{
	srand((unsigned)time(NULL));
	int pos, dis;
	if (m == n)
	{
		return m;
	}
	else if (m > n)
	{
		pos = n;
		dis = m - n + 1;
		return rand() % dis + pos;
	}
	else
	{
		pos = m;
		dis = n - m + 1;
		return rand() % dis + pos;
	}
}
