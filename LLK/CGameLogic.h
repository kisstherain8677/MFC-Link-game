#pragma once

#include "global.h"

class CGameLogic
{
public:
	CGameLogic();
	~CGameLogic();

	void InitMap(int anMap[][4]);
	bool IsLink(int anMap[][4], Vertex v1, Vertex v2);//判断v1v2是否连通

	int GetVexPath(Vertex avPath[4]);//得到路径axPath，并通过参数返回给调用函数，返回值为顶点数
	void Clear(int anMap[][4], Vertex v1, Vertex v2);

	

protected:
	Vertex m_avPath[4];//保存在进行连接时所经过的点
	int m_nVexNum;//存放在m_avPath中的顶点数

	void PushVertex(Vertex v);//添加一个路径顶点
	void PopVertex();//pop出一个顶点

	//IsLink的辅助函数
	bool LinkInRow(int anMap[][4], Vertex v1, Vertex v2);//横向连通判断
	bool LinkInCol(int anMap[][4], Vertex v1, Vertex v2);//纵向连通判断
	bool OneCornorLink(int anMap[][4], Vertex v1, Vertex v2);//一个拐点连通判断
	bool TwoCornorLink(int anMap[][4], Vertex v1, Vertex v2);//两个拐点连通判断
	bool LineY(int anMap[][4], int nRow1, int nRow2, int nCol);//直线连通Y轴
	bool LineX(int anMap[][4], int nRow, int nCol1, int nCol2);//直线连通X轴

};

