#include "stdafx.h"
#include "CEasyGame.h"


void CEasyGame::StartGame()
{
	CGameLogic gameLogic;
	gameLogic.InitMap(m_graph);
}

bool CEasyGame::PropLink()//用道具 直接消除
{
	//判断是否为同一位置
	if (m_ptSelFirst.col == m_ptSelSec.col&&m_ptSelFirst.row == m_ptSelSec.row) {
		return false;
	}
	
	
	CGameLogic gameLogic;

	gameLogic.Clear(m_graph, m_ptSelFirst, m_ptSelSec);
	//获取路径，以及路径中顶点的个数
	return true;
}

CEasyGame::CEasyGame()
{
}


CEasyGame::~CEasyGame()
{
}


