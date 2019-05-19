#include "stdafx.h"
#include "CGameLogic.h"


CGameLogic::CGameLogic()
{

}


CGameLogic::~CGameLogic()
{
}

//初始化游戏地图的二维数组
void CGameLogic::InitMap(int anMap[][4])
{
	int anTemp[4][4] = { 0,1,2,1,0,2,1,1,2,3,2,0,3,1,2,0 };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			anMap[i][j] = anTemp[i][j];
		}
	}
}

//判断两个图是否可以消除
bool CGameLogic::IsLink(int anMap[][4], Vertex v1, Vertex v2)
{
	if (anMap[v1.row][v1.col] == anMap[v2.row][v2.col]) {
		return true;
	}
	return false;
}

void CGameLogic::Clear(int anMap[][4], Vertex v1, Vertex v2)
{
	anMap[v1.row][v1.col] = -1;
	anMap[v2.row][v2.col] = -1;
}


