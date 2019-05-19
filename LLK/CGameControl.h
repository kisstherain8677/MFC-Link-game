#pragma once

#include "global.h"
class CGameControl
{
public:
	CGameControl();
	~CGameControl();

	void StartGame();
	int GetElement(int nRow, int nCol);//返回指定数组元素
	void SetFirstPoint(int nRow, int nCol);//设置第一个点行号列号
	void SetSecPoint(int nRow, int nCol);//设置第二个点的行列号
	bool Link(Vertex avPath[2]);

private:
	int m_anMap[4][4];//四行四列地图
	Vertex m_ptSelFirst;//第一次选中点
	Vertex m_ptSelSec;//第二次选中的点
};

