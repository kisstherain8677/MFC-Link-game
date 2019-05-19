#include "stdafx.h"
#include "CGameLogic.h"


CGameLogic::CGameLogic()
{
	m_nVexNum = 0;
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
	//将第一个选中的点入栈
	PushVertex(v1);
	//X直连方式
	if (v1.row == v2.row) {
		if (LinkInRow(anMap, v1, v2)) {
			PushVertex(v2);
			return true;
		}
			
	}

	//Y直连方式
	else if (v1.col == v2.col) {
		if (LinkInCol(anMap, v1, v2)) {
			PushVertex(v2);
			return true;
		}
	}

	//两条直线连通
	if (OneCornorLink(anMap, v1, v2)) {
		PushVertex(v2);
		return true;
	}

	//三条直线连通
	if (TwoCornorLink(anMap, v1, v2)) {
		PushVertex(v2);
		return true;
	}
	//不能消子，pop出第一个元素
	PopVertex();
	return false;
}

int CGameLogic::GetVexPath(Vertex avPath[4])
{
	for (int i = 0; i < m_nVexNum; i++) {
		avPath[i] = m_avPath[i];
	}
	return m_nVexNum;
}

void CGameLogic::Clear(int anMap[][4], Vertex v1, Vertex v2)
{
	anMap[v1.row][v1.col] = BLANK;
	anMap[v2.row][v2.col] = BLANK;
}

void CGameLogic::PushVertex(Vertex v)
{
	m_avPath[m_nVexNum] = v;
	m_nVexNum++;
}

void CGameLogic::PopVertex()
{
	m_nVexNum--;
}

bool CGameLogic::LinkInRow(int anMap[][4], Vertex v1, Vertex v2)
{
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	int nRow = v1.row;
	//保证nCol1<nCol2
	if (nCol1 > nCol2) {
		int temp = nCol1;
		nCol1 = nCol2;
		nCol2 = temp;
	}

	for (int i = nCol1 + 1; i <= nCol2; i++) {
		if (i == nCol2) return true;
		if (anMap[nRow][i] != BLANK) break;
	}
	return false;
}

bool CGameLogic::LinkInCol(int anMap[][4], Vertex v1, Vertex v2)
{
	int nRow1 = v1.row;
	int nRow2 = v2.row;
	int nCol = v1.col;

	//保证nCol1<nCol2
	if (nRow1 > nRow2) {
		int temp = nRow1;
		nRow1 = nRow2;
		nRow2 = temp;
	}

	for (int i = nRow1 + 1; i <= nRow2; i++) {
		if (i == nRow2) return true;
		if (anMap[i][nCol] != BLANK) break;
	}
	return false;
}




bool CGameLogic::OneCornorLink(int anMap[][4], Vertex v1, Vertex v2)
{
	int nRow1 = v1.row;
	int nRow2 = v2.row;
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	Vertex coVertex;//拐点
	//确保1<2
	if (nRow1 > nRow2) {
		int temp = nRow1;
		nRow1 = nRow2;
		nRow2 = temp;

		int temp2 = nCol1;
		nCol1 = nCol2;
		nCol2 = temp2;
	}
	if (nCol2 < nCol1) {
		if (LineX(anMap, nRow1, nCol2, nCol1 - 1) && LineY(anMap, nCol2, nRow1, nRow2 - 1))
		{
			
			coVertex.col = nCol2;
			coVertex.row = nRow1;
			//拐点入栈
			PushVertex(coVertex);
			return true;
		}
		if (LineY(anMap, nCol1, nRow1+1, nRow2) && LineX(anMap, nRow2, nCol2+1, nCol1))
		{

			coVertex.col = nCol1;
			coVertex.row = nRow2;
			//拐点入栈
			PushVertex(coVertex);
			return true;
		}
	}
	else {
		if (LineX(anMap, nRow1, nCol1 + 1, nCol2) && LineY(anMap, nCol2, nRow1, nRow2 - 1))
		{

			coVertex.col = nCol2;
			coVertex.row = nRow1;
			//拐点入栈
			PushVertex(coVertex);
			return true;
		}
		if (LineY(anMap, nCol1, nRow1 + 1, nRow2) && LineX(anMap, nRow2, nCol1, nCol2 - 1))
		{

			coVertex.col = nCol1;
			coVertex.row = nRow2;
			//拐点入栈
			PushVertex(coVertex);
			return true;
		}
	}

	return false;
}

bool CGameLogic::TwoCornorLink(int anMap[][4], Vertex v1, Vertex v2)
{
	int nRow1 = v1.row;
	int nRow2 = v2.row;
	int nCol1 = v1.col;
	int nCol2 = v2.col;
    //拐点
	Vertex cov1;
	Vertex cov2;

	//确保1<2
	if (nRow1 > nRow2) {
		int temp = nRow1;
		nRow1 = nRow2;
		nRow2 = temp;

		int temp2 = nCol1;
		nCol1 = nCol2;
		nCol2 = temp2;
	}

	if (nCol2 < nCol1) {
		for (int rx = nRow1 + 1; rx <= nRow2 - 1; rx++) {
			if (LineY(anMap, nCol1, nRow1 + 1, rx) && LineX(anMap, rx, nCol2, nCol1) && LineY(anMap, nCol2, rx, nRow2 - 1))
			{
				cov1.row = rx;
				cov1.col = nCol1;

				cov2.row = rx;
				cov2.col = nCol2;
				//两个拐点入栈
				PushVertex(cov1);
				PushVertex(cov2);
				return true;
			}
		}

		for (int cx = nCol2 + 1; cx <= nCol1 - 1; cx++) {
			if (LineX(anMap, nRow2, nCol2 + 1, cx) && LineY(anMap, cx, nRow1, nRow2) && LineX(anMap, nRow1, cx, nCol1 - 1)) 
			{
				cov1.row = nRow1;
				cov1.col = cx;

				cov2.row = nRow2;
				cov2.col = cx;
				//两个拐点入栈
				PushVertex(cov1);
				PushVertex(cov2);
				return true;
			}
			
		}

	}
	else {
		for (int rx = nRow1 + 1; rx <= nRow2 - 1; rx++) {
			if (LineY(anMap, nCol1, nRow1 + 1, rx) && LineX(anMap, rx, nCol1, nCol2) && LineY(anMap, nCol2, rx, nRow2 - 1))
			{
				cov1.row = rx;
				cov1.col = nCol1;

				cov2.row = rx;
				cov2.col = nCol2;
				//两个拐点入栈
				PushVertex(cov1);
				PushVertex(cov2);
				return true;
			}
		}
		for (int cx = nCol1 + 1; cx <= nCol2 - 1; cx++) {
			if (LineX(anMap, nRow1, nCol1 + 1, cx) && LineY(anMap, cx, nRow1, nRow2) && LineX(anMap, nRow2, cx, nCol2 - 1))
			{
				cov1.row = nRow1;
				cov1.col = cx;

				cov2.row = nRow2;
				cov2.col = cx;
				//两个拐点入栈
				PushVertex(cov1);
				PushVertex(cov2);
				return true;
			}
		}

	}

	//row和col有一个相同的情况，即C形
	//r1==r2
	if (nRow1 == nRow2) {
		for (int rx = 0; rx <= 3; rx++) {
			if (rx == nRow1)
				continue;
			else {
				if (rx < nRow1) {//rx在两点下面
					if (LineY(anMap, nCol1, nRow1 + 1, rx) && LineX(anMap, rx, nCol1, nCol2) && LineY(anMap, nCol2, nRow1 + 1, rx))
					{
						cov1.row = rx;
						cov1.col = nCol1;

						cov2.row = rx;
						cov2.col = nCol2;
						//两个拐点入栈
						PushVertex(cov1);
						PushVertex(cov2);
						return true;
					}
				}
				else {//rx在两点上面
					if (LineY(anMap, nCol1, rx, nRow1 - 1) && LineX(anMap, rx, nCol1, nCol2) && LineY(anMap, nCol2, rx, nRow1 - 1))
					{
						cov1.row = rx;
						cov1.col = nCol1;

						cov2.row = rx;
						cov2.col = nCol2;
						//两个拐点入栈
						PushVertex(cov1);
						PushVertex(cov2);
						return true;
					}
				}
			}
		}
	}

	if (nCol1 == nCol2) {
		for (int cx = 0; cx <= 3; cx++) {
			if (cx == nCol1)
				continue;
			else {
				if (cx < nCol1) {//cx在两点左边
					if (LineX(anMap, nRow1, cx, nCol1 - 1) && LineY(anMap, cx, nRow1, nRow2) && LineX(anMap, nRow2, cx, nCol2 - 1))
					{
						cov1.row = nRow1;
						cov1.col = cx;

						cov2.row = nRow2;
						cov2.col = cx;
						//两个拐点入栈
						PushVertex(cov1);
						PushVertex(cov2);
						return true;
					}
				}
				else {//cx在两点右边
					if (LineX(anMap, nRow1, nCol1 + 1, cx) && LineY(anMap, cx, nRow1, nRow2) && LineX(anMap, nRow2, nCol2 + 1, cx))
					{
						cov1.row = nRow1;
						cov1.col = cx;

						cov2.row = nRow2;
						cov2.col = cx;
						//两个拐点入栈
						PushVertex(cov1);
						PushVertex(cov2);
						return true;
					}
				}
			}
		}
	}
	


	return false;
}

bool CGameLogic::LineX(int anMap[][4], int nRow, int nCol1, int nCol2)
{
	for (int nCol = nCol1; nCol <= nCol2; nCol++) {
		if (anMap[nRow][nCol] != BLANK)
			return false;
	}
	return true;
}

bool CGameLogic::LineY(int anMap[][4], int nCol, int nRow1, int nRow2) {
	for (int nRow = nRow1; nRow <= nRow2; nRow++) {
		if (anMap[nRow][nCol] != BLANK)
			return false;
	}
	return true;
}
