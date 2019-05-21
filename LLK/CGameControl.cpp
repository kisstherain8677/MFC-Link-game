#include "stdafx.h"
#include "CGameLogic.h"
#include "CGameControl.h"


CGameControl::CGameControl()
{
}


CGameControl::~CGameControl()
{
}

void CGameControl::StartGame()
{
	CGameLogic gameLogic;
	gameLogic.InitMap(m_graph);
}

int CGameControl::GetElement(int nRow, int nCol)
{
	return m_graph.GetVertex(nRow*MAX_COL+nCol);
}

void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_ptSelFirst.row = nRow;
	m_ptSelFirst.col = nCol;
}

void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_ptSelSec.col = nCol;
	m_ptSelSec.row = nRow;
}

bool CGameControl::Link(int avPath[MAX_VERTEX_NUM], int &nVertex)
{   //判断是否为同一位置
	if (m_ptSelFirst.col == m_ptSelSec.col&&m_ptSelFirst.row == m_ptSelSec.row) {
		return false;
	}
	//判断图片是否相同
	int index1 = MAX_COL * m_ptSelFirst.row + m_ptSelFirst.col;
	int index2 = MAX_COL * m_ptSelSec.row + m_ptSelSec.col;
	if (m_graph.GetVertex(index1) != m_graph.GetVertex(index2)) {
		return false;
	}
	CGameLogic gameLogic;
	
	if (!gameLogic.IsLink(m_graph, m_ptSelFirst, m_ptSelSec)){
		return false;
	}
	gameLogic.Clear(m_graph, m_ptSelFirst, m_ptSelSec);
	//获取路径，以及路径中顶点的个数
	nVertex = gameLogic.GetVexPath(avPath);
	return true;
}

bool CGameControl::isWin()
{
	CGameLogic gameLogic;
	if (gameLogic.isBlank(m_graph)) {
		m_graph.ClearGraph();
		return true;
	}
	return false;
}

bool CGameControl::Help(int avPath[MAX_VERTEX_NUM], int & nVexNum)
{
	CGameLogic logic;
	if (logic.isBlank(m_graph)) {
		return false;
	}
	if (logic.SearchValidPath(m_graph)) {
		for (int i = 0; i < logic.GetPathNum(); i++) {
			avPath[i] = logic.GetPathIn(i);
		}
		nVexNum = logic.GetPathNum();
		return true;
	}
	return false;
}

void CGameControl::ResetGraph()
{
	CGameLogic logic;
	logic.ResetGraph(m_graph);
}


