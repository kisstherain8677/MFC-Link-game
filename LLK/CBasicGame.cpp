#include "stdafx.h"
#include "CBasicGame.h"


CBasicGame::CBasicGame()
{
}


CBasicGame::~CBasicGame()
{
}

void CBasicGame::StartGame()
{
	CGameLogic gameLogic;
	gameLogic.InitMap(m_graph);
}
