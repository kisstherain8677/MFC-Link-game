#pragma once

#include "global.h"
#include "CGraph.h"
class CGameControl
{
public:
	CGameControl();
	~CGameControl();
	virtual int GetGrade();
	virtual void SetGrade(int i);
	virtual void StartGame() = 0;
	int GetElement(int nRow, int nCol);//返回指定数组元素
	void SetFirstPoint(int nRow, int nCol);//设置第一个点行号列号
	void SetSecPoint(int nRow, int nCol);//设置第二个点的行列号
	bool Link(int avPath[MAX_VERTEX_NUM],int &nVertex);//判断是否可连通，如果能连通，通过参数返回连接路径和连接
	virtual int isWin(int time);//判断图中顶点是否为空，如果为空，清理图结构，返回true
	virtual bool Help(int avPath[MAX_VERTEX_NUM], int &nVexNum);
	virtual void ResetGraph();
	void SetFlag(Flag flag);
	Flag GetFlag();
	virtual bool PropLink();
protected:
	int m_nGrade;

	CGraph m_graph;//用一个图结构保存地图
	Vertex m_ptSelFirst;//第一次选中点
	Vertex m_ptSelSec;//第二次选中的点
	Flag m_flag;
};

