#pragma once
#include "CGameControl.h"
#include "CGameLogic.h"

class CBasicGame :
	public CGameControl
{
public:
	CBasicGame();
	~CBasicGame();

	virtual void StartGame();
};

