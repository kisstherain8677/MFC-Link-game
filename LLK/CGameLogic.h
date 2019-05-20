#pragma once

#include "global.h"
#include "CGraph.h"

class CGameLogic
{
public:
	CGameLogic();
	~CGameLogic();

	void InitMap(CGraph &graph);
	bool IsLink(CGraph &graph, Vertex v1, Vertex v2);//判断v1v2是否连通

	int GetVexPath(int avPath[]);//得到路径axPath，并通过参数返回给调用函数，返回值为顶点数
	void Clear(CGraph &g, Vertex v1, Vertex v2);
	
	

protected:

	//保存连通路径的顶点索引
	int m_anPath[16];
	//连通路径顶点个数
	int m_nVexNum;
	//连通路径数组m_anPath中的拐点数
	int m_nCorner;

	//深度优先搜索，判断顶点V0，V1在图中是否连通
	bool SearchPathDFS(CGraph &g, int v0,int v1);
	//判断索引为nVi的顶点是否保存到连通数组m_anPath中 
	bool isExsit(int nVi);
	//判断连接路径数组m_anPath中，连续三个顶点是否构成一个拐点
	bool IsCorner();


	void PushVertex(int nV);//添加一个路径顶点到m_anPath，并判断压入后，是否形成一个拐点，如果是拐点，则拐点数量加一

	void PopVertex();//pop出一个顶点
	//判断nRow行，nCol列的顶点与它上下左右的顶点是否有边，如果有边，更新图结构
	void UpdateArc(CGraph &g, int nRow, int nCol);

	

	//IsLink的辅助函数
	bool LinkInRow(int anMap[][4], Vertex v1, Vertex v2);//横向连通判断
	bool LinkInCol(int anMap[][4], Vertex v1, Vertex v2);//纵向连通判断
	bool OneCornorLink(int anMap[][4], Vertex v1, Vertex v2);//一个拐点连通判断
	bool TwoCornorLink(int anMap[][4], Vertex v1, Vertex v2);//两个拐点连通判断
	bool LineY(int anMap[][4], int nRow1, int nRow2, int nCol);//直线连通Y轴
	bool LineX(int anMap[][4], int nRow, int nCol1, int nCol2);//直线连通X轴

};

