#include "stdafx.h"
#include "CGraph.h"


CGraph::CGraph()
{
	InitGraph();
}


CGraph::~CGraph()
{
}

int CGraph::AddVertex(int info)
{
	if (m_VexNum >= MAX_VERTEX_NUM) {
		return MAX_VERTEX_NUM;
	}
	m_Vertices[m_VexNum++] = info;
	return m_VexNum;//返回当前顶点个数
}

void CGraph::AddArc(int nV1Index, int nV2Index)
{
	m_AdjMatrix[nV1Index][nV2Index] = true;
	m_AdjMatrix[nV2Index][nV1Index] = true;
}

int CGraph::GetVertex(int nIndex)
{
	return m_Vertices[nIndex];
}

int CGraph::GetVexNum()
{
	return m_VexNum;
}

int CGraph::GetArcNum()
{
	return m_nArcNum;
}

void CGraph::UpdateVertex(int nIndex, int info)
{
	m_Vertices[nIndex] = info;
}

bool CGraph::GetArc(int v1, int v2)
{
	return m_AdjMatrix[v1][v2];
}

void CGraph::ClearGraph()
{
	InitGraph();
}

void CGraph::SetVertex(int index, int val)
{
	m_Vertices[index] = val;
}

void CGraph::InitGraph()
{
	m_VexNum = 0;
	m_nArcNum = 0;
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		//初始化顶点
		m_Vertices[i] = -1;
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			//初始化边
			m_AdjMatrix[i][j] = false;
		}
	}
}
