#pragma once
#include "global.h"
class CGraph
{
public:
	CGraph();
	~CGraph();

	int AddVertex(int info);//增加一个顶点
	void AddArc(int nV1Index, int nV2Index);//增加一条边
	int GetVertex(int nIndex);//获取数组索引为nIndex的元素
	int GetVexNum();//获取顶点数组中的顶点数
	int GetArcNum();//获取边数
	void UpdateVertex(int nIndex, int info);//将图中索引号为nIndex的元素更新为info
	bool GetArc(int v1, int v2);//根据索引返回边
	void ClearGraph();//将图中顶点和边还原为初始状态
	void SetVertex(int index, int val);
protected:

typedef int Vertices[MAX_VERTEX_NUM];
typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

Vertices m_Vertices;//顶点数组
AdjMatrix m_AdjMatrix;//邻接矩阵
int m_VexNum;//顶点数
int m_nArcNum;//边数


void InitGraph();


};

