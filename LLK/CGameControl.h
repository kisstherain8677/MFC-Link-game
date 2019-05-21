#pragma once

#include "global.h"
#include "CGraph.h"
class CGameControl
{
public:
	CGameControl();
	~CGameControl();

	void StartGame();
	int GetElement(int nRow, int nCol);//返回指定数组元素
	void SetFirstPoint(int nRow, int nCol);//设置第一个点行号列号
	void SetSecPoint(int nRow, int nCol);//设置第二个点的行列号
	bool Link(int avPath[MAX_VERTEX_NUM],int &nVertex);//判断是否可连通，如果能连通，通过参数返回连接路径和连接
	bool isWin();//判断图中顶点是否为空，如果为空，清理图结构，返回true
	bool Help(int avPath[MAX_VERTEX_NUM], int &nVexNum);
	void ResetGraph();
protected:
	CGraph m_graph;//用一个图结构保存地图
	Vertex m_ptSelFirst;//第一次选中点
	Vertex m_ptSelSec;//第二次选中的点
};

