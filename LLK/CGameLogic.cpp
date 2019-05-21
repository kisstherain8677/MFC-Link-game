#include "stdafx.h"
#include "CGameLogic.h"


CGameLogic::CGameLogic()
{
	m_nVexNum = 0;
	m_nCorner = 0;
}


CGameLogic::~CGameLogic()
{
}

//初始化游戏地图的二维数组
void CGameLogic::InitMap(CGraph &graph)
{


	//随机生成地图
	int anTemp[MAX_VERTEX_NUM];
	//多少花色
	for (int i = 0; i < MAX_PIC_NUM; i++) {
		//重复数
		for (int j = 0; j < REPEAT_NUM; j++) {
			anTemp[i*REPEAT_NUM + j] = i;
		}
	}
	//设置种子
	srand((int)time(NULL));

	//随机任意交换两个数
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		//随机得到两个坐标
		int nIndex1 = rand() % MAX_VERTEX_NUM;
		int nIndex2 = rand() % MAX_VERTEX_NUM;
		//交换两个数值
		int temp = anTemp[nIndex1];
		anTemp[nIndex1] = anTemp[nIndex2];
		anTemp[nIndex2] = temp;
	}

	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		
			graph.AddVertex(anTemp[i]);
		
	}
	//更新图信息
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			UpdateArc(graph, i, j);
		}
	}

}

//判断两个图是否可以消除
bool CGameLogic::IsLink(CGraph &g, Vertex v1, Vertex v2)
{
	//获取顶点索引号
	int nV1Index = v1.row * MAX_COL + v1.col;
	int nV2Index = v2.row * MAX_COL + v2.col;
	//压入第一个点
	PushVertex(nV1Index);
	//判断两顶点是否相邻连通
	if (g.GetArc(nV1Index, nV2Index)) {
		PushVertex(nV2Index);
		return true;
	}
	if (SearchPathDFS(g, nV1Index, nV2Index)) {
		return true;
	}
	//PopVertex();
	return false;
}

int CGameLogic::GetVexPath(int avPath[])
{
	for (int i = 0; i < m_nVexNum; i++) {
		avPath[i] = m_anPath[i];
	}
	return m_nVexNum;
}

void CGameLogic::Clear(CGraph &g, Vertex v1, Vertex v2)
{
	//获取顶点索引
	int index1 = v1.row * MAX_COL + v1.col;
	int index2 = v2.row * MAX_COL + v2.col;
	//更新顶点
	g.UpdateVertex(index1, BLANK);
	g.UpdateVertex(index2, BLANK);
	//更新边数组
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			UpdateArc(g, i, j);
		}
	}
	
}

bool CGameLogic::isBlank(CGraph & g)
{
	int vn = g.GetVexNum();
	for (int i = 0; i < vn; i++) {
		if (g.GetVertex(i) != BLANK)
			return false;
	}
	return true;
}

bool CGameLogic::SearchValidPath(CGraph & g)
{
	//找到第一个不为空的点V1
	int index1;
	int index2;
	for (int i = 0; i < g.GetVexNum(); i++) {
		if (g.GetVertex(i) != BLANK) {
			index1 = i;
			for (int j = 0; j < g.GetVexNum(); j++) {
				if (i != j) {
					if (g.GetVertex(index1) == g.GetVertex(j)) {
						PushVertex(index1);
						if (SearchPathDFS(g, index1, j)) {
							return true;
						}
						PopVertex();
					}

				}
			}
		}
		
	}

	return false;
}

int CGameLogic::GetPathNum()
{
	return m_nVexNum;
}

int CGameLogic::GetPathIn(int index)
{
	if (index < m_nVexNum) {
		return m_anPath[index];
	}
	return -1;
}

void CGameLogic::ResetGraph(CGraph & g)
{
	for (int i = 0; i < 100; i++) {
		int index1 = rand() % MAX_VERTEX_NUM;
		int index2 = rand() % MAX_VERTEX_NUM;
		int temp = g.GetVertex(index1);
		g.SetVertex(index1, g.GetVertex(index2));
		g.SetVertex(index2, temp);
	}
	//更新图信息（边的关系）
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			UpdateArc(g, i, j);
		}
	}
}

void CGameLogic::UpdateArc(CGraph & g, int nRow, int nCol)
{
	int nV1Index = nRow * MAX_COL + nCol;
	if (nCol > 0) {
		int nV2Index = nV1Index - 1;
		if (g.GetVertex(nV2Index) == g.GetVertex(nV1Index)||g.GetVertex(nV1Index)==BLANK||g.GetVertex(nV2Index)==BLANK) {
			g.AddArc(nV1Index, nV2Index);
		}
	}
	if (nCol < MAX_COL-1) {
		int nV2Index = nV1Index + 1;
		if (g.GetVertex(nV2Index) == g.GetVertex(nV1Index) || g.GetVertex(nV1Index) == BLANK || g.GetVertex(nV2Index) == BLANK) {
			g.AddArc(nV1Index, nV2Index);
		}
	}
	if (nRow > 0) {
		int nV2Index = nV1Index - MAX_COL;
		if (g.GetVertex(nV2Index) == g.GetVertex(nV1Index) || g.GetVertex(nV1Index) == BLANK || g.GetVertex(nV2Index) == BLANK) {
			g.AddArc(nV1Index, nV2Index);
		}
	}
	if (nRow < MAX_ROW-1) {
		int nV2Index = nV1Index + MAX_COL;
		if (g.GetVertex(nV2Index) == g.GetVertex(nV1Index) || g.GetVertex(nV1Index) == BLANK || g.GetVertex(nV2Index) == BLANK) {
			g.AddArc(nV1Index, nV2Index);
		}
	}
}

bool CGameLogic::SearchPathDFS(CGraph & g, int v0, int v1)
{
	//得到顶点数
	int nVexnum = g.GetVexNum();
	//遍历图中nV0行，从0到nVexnum列值为true的点
	for (int vi = 0; vi < nVexnum; vi++) {
		if (g.GetArc(v0, vi) && !isExsit(vi)) {
			PushVertex(vi);
			if (m_nCorner > 2) {
				PopVertex();
				continue;
			}

			//当中间顶点不是v1时，继续搜索下一个相邻且连通的点
			if (vi != v1) {
				//当中间顶点不为空时，表示路径不连通
				if (g.GetVertex(vi) != BLANK) {
					PopVertex();
					continue;
				}
				//如果vi是一个已消除的点，判断(vi v1)
				if (SearchPathDFS(g, vi, v1)) {
					return true;
					//表示已经找到了一条连通路径，返回true
				}
			}
			else {//如果vi=v1表示已经找到了一条连通路径，返回true
				return true;
			}
			PopVertex();
		}
	}
	return false;
}

bool CGameLogic::isExsit(int nVi)
{
	for (int i = 0; i < m_nVexNum; i++) {
		if (m_anPath[i] == nVi) {
			return true;
		}
	}
	return false;
}

bool CGameLogic::IsCorner()
{
	if (m_nVexNum >= 3) {
		if ((m_anPath[m_nVexNum - 1] + m_anPath[m_nVexNum - 3]) / 2 != m_anPath[m_nVexNum - 2]) {
			
			return true;
		}
	}
	return false;
}

void CGameLogic::PushVertex(int nV )
{
	m_anPath[m_nVexNum++] = nV;
	if (IsCorner()) {
		m_nCorner++;
	}
}

void CGameLogic::PopVertex()
{
	if (IsCorner()) {
		m_nCorner--;
	}
	m_nVexNum--;
}

