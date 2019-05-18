﻿// CGameDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "LLK.h"
#include "CGameDlg.h"
#include "afxdialogex.h"


// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	//初始化游戏更新区域
	

	m_ptGameTop.x = 50;
	m_ptGameTop.y = 50;
	m_sizeElement.cx = 40;
	m_sizeElement.cy = 40;
	m_bFirstPoint = true;

	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElement.cx * 4;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElement.cy * 4;
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CGameDlg::InitBackground()
{

	//获取当前对话框的视频内存
	CClientDC dc(this);
    
	//加载bmp图片资源
	HANDLE bmp = ::LoadImage(NULL, _T("theme\\picture\\basic_bg.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);;
	//创建与视频内存兼容的内存DC
	m_dcBG.CreateCompatibleDC(&dc);
	//将位图资源选入DC
	m_dcBG.SelectObject(bmp);

	//初始化内存DC
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	m_dcMem.SelectObject(&bmpMem);
	//绘制背景到内存DC。
	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_START, &CGameDlg::OnClickedButtonStart)
//	ON_WM_LBUTTONUP()
ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CGameDlg 消息处理程序


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//载入背景到内存
	InitBackground();
	//载入元素图片到内存
	InitElement();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);

}

//将元素图片载入内存
void CGameDlg::InitElement() {
	CClientDC dc(this);
	
	HANDLE bmp = ::LoadImage(NULL, _T("theme\\picture\\all_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);;
	
	m_dcElement.CreateCompatibleDC(&dc);
	m_dcElement.SelectObject(bmp);

	HANDLE bmpMask = ::LoadImage(NULL, _T("theme\\picture\\all_element_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);;

	m_dcMask.CreateCompatibleDC(&dc);
	m_dcMask.SelectObject(bmpMask);
}



void CGameDlg::OnClickedButtonStart()
{
	int anMap[4][4] = { 0,1,2,1,0,2,1,1,2,3,2,0,3,1,2,0 };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m_anMap[i][j] = anMap[i][j];
		}
	}

	UpdateMap();
	Invalidate(FALSE);
}

void CGameDlg::UpdateMap() {
	int nX = 50;
	int nY = 50;
	int nElemW = 40;
	int nElemH = 40;
	
	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top,
		m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);

	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			
				m_dcMem.BitBlt(nX + j * nElemW, nY + i * nElemH, nElemW, nElemH, &m_dcMask, 0, m_anMap[i][j] * nElemH, SRCPAINT);
				m_dcMem.BitBlt(nX + j * nElemW, nY + i * nElemH, nElemW, nElemH, &m_dcElement, 0, m_anMap[i][j] * nElemH, SRCAND);

		}
	}
	CClientDC dc(this);
	dc.BitBlt(m_rtGameRect.left, m_rtGameRect.top,m_rtGameRect.Width(),m_rtGameRect.Height(),
		&m_dcMem, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
}




void CGameDlg::DrawTipFrame(int nRow,int nCol) {
	CClientDC dc(this);
	CBrush brush(RGB(233, 43, 43));
	CRect rtTipFrame;
	rtTipFrame.left = m_ptGameTop.x + nCol * m_sizeElement.cx;
	rtTipFrame.top = m_ptGameTop.y + nRow * m_sizeElement.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElement.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElement.cy;
	dc.FrameRect(rtTipFrame, &brush);
}



void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (point.x < m_ptGameTop.x || point.y < m_ptGameTop.y) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}

	int nRow = (point.y - m_ptGameTop.y) / m_sizeElement.cy;
	int nCol = (point.x - m_ptGameTop.x) / m_sizeElement.cx;
	if (nRow > 3 || nCol > 3) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}

	//如果是第一次选中，绘制矩形框
	if (m_bFirstPoint) {
		DrawTipFrame(nRow, nCol);
		m_ptSelFirst.x = nCol;
		m_ptSelFirst.y = nRow;
	}
	else {
		DrawTipFrame(nRow, nCol);
		m_ptSelSec.x = nCol;
		m_ptSelSec.y = nRow;
		//判断是否是相同图片
		if (IsLink()) {
			DrawTipLine();//绘制连线
			//消除
			m_anMap[m_ptSelFirst.y][m_ptSelFirst.x] = -1;
			m_anMap[m_ptSelSec.y][m_ptSelSec.x] = -1;
			Sleep(200);
			UpdateMap();
		}
		
		InvalidateRect(m_rtGameRect, FALSE);
	}
	m_bFirstPoint = !m_bFirstPoint;
	
}

bool CGameDlg::IsLink() {
	if (m_anMap[m_ptSelFirst.y][m_ptSelFirst.x]==m_anMap[m_ptSelSec.y][m_ptSelSec.x]) {//此处注意x y
		return true;
	}
		return false;
}

void CGameDlg::DrawTipLine() {
	//获取DC
	CClientDC dc(this);
	//设置画笔
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));

	//将画笔送入DC
	CPen* pOldPen = dc.SelectObject(&penLine);
	//绘制连接线
	dc.MoveTo(m_ptGameTop.x + m_ptSelFirst.x*m_sizeElement.cx + m_sizeElement.cx / 2,
		m_ptGameTop.y + m_ptSelFirst.y*m_sizeElement.cy + m_sizeElement.cy / 2);
	dc.LineTo(m_ptGameTop.x + m_ptSelSec.x*m_sizeElement.cx + m_sizeElement.cx / 2,
		m_ptGameTop.y + m_ptSelSec.y*m_sizeElement.cy + m_sizeElement.cy / 2);
	
	dc.SelectObject(pOldPen);


}