// CGameDlg.cpp: 实现文件
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
	m_bPlaying = false;
	m_bPause = false;
	//初始化游戏更新区域
	

	m_ptGameTop.x = MAP_LEFT;
	m_ptGameTop.y = MAP_TOP;
	m_sizeElement.cx = PIC_WIDTH;
	m_sizeElement.cy = PIC_HEIGHT;
	m_bFirstPoint = true;

	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElement.cx * MAX_COL;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElement.cy * MAX_ROW;
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GAME_TIME, m_GameProgress);
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
ON_BN_CLICKED(IDC_BUTTON_HINT, &CGameDlg::OnClickedButtonHint)
ON_BN_CLICKED(IDC_BUTTON_RESET, &CGameDlg::OnClickedButtonReset)
ON_WM_TIMER()
ON_BN_CLICKED(IDC_BUTTON_PAUSE, &CGameDlg::OnClickedButtonPause)
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

void CGameDlg::DrawGameTime()
{

}

void CGameDlg::JudgeWin()
{
	int bGameStatus = m_gameControl.isWin(m_GameProgress.GetPos());

	if (bGameStatus == GAME_PLAY) {
		return;
	}
	else {
		m_bPlaying = false;
		KillTimer(PLAY_TIMER_ID);

		CString strTitle;
		this->GetWindowTextW(strTitle);
		if (bGameStatus == GAME_SUCCESS) {
			MessageBox(_T("WIN!!"));
		}
		else if (bGameStatus == GAME_LOSE) {
			MessageBox(_T("SORRY,YOU LOSE.."));
		}
		//还原开始游戏按钮
		this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	}
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

	//初始化地图
	m_gameControl.StartGame();

	m_bPlaying = true;
	//禁用开始游戏按键
	this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	
	//初始进度条
	m_GameProgress.SetRange(0, 300);//范围
	m_GameProgress.SetStep(-2);//步长
	m_GameProgress.SetPos(60 * 5);//初始值
	//启动定时器
	this->SetTimer(PLAY_TIMER_ID, 1000, NULL);//为NULL代表调用默认的回调函数OnTimer



	//更新界面
	UpdateMap();
	//更新窗口
	InvalidateRect(m_rtGameRect,FALSE);
}

void CGameDlg::UpdateMap() {
	int nX = MAP_LEFT;
	int nY = MAP_TOP;
	int nElemW = PIC_WIDTH;
	int nElemH = PIC_HEIGHT;
	
	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top,
		m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);

	
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			int elem = m_gameControl.GetElement(i, j);
			//去背景
			
			m_dcMem.BitBlt(nX + j * nElemW, nY + i * nElemH, nElemW, nElemH, &m_dcMask, 0,elem * nElemH, SRCPAINT);
			m_dcMem.BitBlt(nX + j * nElemW, nY + i * nElemH, nElemW, nElemH, &m_dcElement, 0, elem * nElemH, SRCAND);
			
			//不去背景
			//m_dcMem.BitBlt(nX + j * nElemW, nY + i * nElemH, nElemW, nElemH, &m_dcElement, 0, elem * nElemH, SRCCOPY);
				

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
	
	if (m_bPlaying == false) {
		return;
	}
	
	
	if (point.x < m_ptGameTop.x || point.y < m_ptGameTop.y) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}

	int nRow = (point.y - m_ptGameTop.y) / m_sizeElement.cy;
	int nCol = (point.x - m_ptGameTop.x) / m_sizeElement.cx;
	if (nRow > MAX_ROW-1 || nCol > MAX_COL-1) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}

	//如果是第一次选中，绘制矩形框
	if (m_bFirstPoint) {
		DrawTipFrame(nRow, nCol);
		m_gameControl.SetFirstPoint(nRow, nCol);
	}
	else {
		DrawTipFrame(nRow, nCol);
		m_gameControl.SetSecPoint(nRow, nCol);
		//消除
		//获得路径
		int avPath[MAX_VERTEX_NUM];
		int VertexNum;
		//连子判断
		if (m_gameControl.Link(avPath,VertexNum)) {
			//画线
			DrawTipLine(avPath,VertexNum);
			
			Sleep(200);
			//更新地图
			UpdateMap();
		}
		//判断是否是相同图片
		
		InvalidateRect(m_rtGameRect, FALSE);
		//判断是否胜利
		JudgeWin();
	}
	m_bFirstPoint = !m_bFirstPoint;
	
}



void CGameDlg::DrawTipLine(int asvPath[MAX_VERTEX_NUM],int nVexNum) {
	//获取DC
	CClientDC dc(this);
	//设置画笔
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));

	//将画笔送入DC
	CPen* pOldPen = dc.SelectObject(&penLine);
	
	//根据栈中元素绘制连接线
	for (int i = 0; i < nVexNum-1; i++) {
		dc.MoveTo(m_ptGameTop.x + asvPath[i]%MAX_COL*m_sizeElement.cx + m_sizeElement.cx / 2,
			m_ptGameTop.y + asvPath[i]/MAX_COL*m_sizeElement.cy + m_sizeElement.cy / 2);
		dc.LineTo(m_ptGameTop.x + asvPath[i+1]%MAX_COL*m_sizeElement.cx + m_sizeElement.cx / 2,
			m_ptGameTop.y + asvPath[i+1]/MAX_COL*m_sizeElement.cy + m_sizeElement.cy / 2);
	}

	dc.SelectObject(pOldPen);


}


void CGameDlg::OnClickedButtonHint()
{
	int avPath[MAX_VERTEX_NUM];
	int vertexNum;
	if (m_gameControl.Help(avPath, vertexNum)) {
		int row1 = avPath[0] / MAX_COL;
		int col1 = avPath[0] % MAX_COL;
		int row2 = avPath[vertexNum - 1] / MAX_COL;
		int col2 = avPath[vertexNum - 1] % MAX_COL;
		DrawTipFrame(row1, col1);
		DrawTipFrame(row2, col2);
		DrawTipLine(avPath, vertexNum);
		Sleep(1000);
		UpdateMap();
	}
}


void CGameDlg::OnClickedButtonReset()
{
	m_gameControl.ResetGraph();
	UpdateMap();
}


void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == PLAY_TIMER_ID&&m_bPause==false) {
		//游戏时间减一秒
		//StepIt根据增量重绘
		m_GameProgress.StepIt();
	}
	JudgeWin();
	CDialogEx::OnTimer(nIDEvent);
}


void CGameDlg::OnClickedButtonPause()
{
	if (!m_bPlaying) {
		return;
	}
	if (m_bPause == false) {
		this->GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowTextW(_T("继续"));
		m_bPause = true;
		return;
	}
	if (m_bPause == true) {
		this->GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowTextW(_T("暂停"));
		m_bPause = false;
		return;
	}
}
