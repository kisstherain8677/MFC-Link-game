#pragma once
#include "CGameControl.h"
#include "CGameLogic.h"
class CEasyGame :
	public CGameControl
{
public:
	virtual void StartGame();
	//virtual int isWin(int time);//判断图中顶点是否为空，如果为空，清理图结构，返回true
	//virtual bool Help(int avPath[MAX_VERTEX_NUM], int &nVexNum);
	//virtual void ResetGraph();
	virtual bool PropLink();
	CEasyGame();
	~CEasyGame();

	
};

