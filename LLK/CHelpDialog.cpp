// CHelpDialog.cpp: 实现文件
//

#include "stdafx.h"
#include "LLK.h"
#include "CHelpDialog.h"
#include "afxdialogex.h"


// CHelpDialog 对话框

IMPLEMENT_DYNAMIC(CHelpDialog, CDialogEx)

CHelpDialog::CHelpDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD__DIALOG_HELP, pParent)
{

}

CHelpDialog::~CHelpDialog()
{
}

BOOL CHelpDialog::OnInitDialog()
{
	
	CDialogEx::OnInitDialog();

	

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	CClientDC dc(this);
	//加载bmp图片资源
	HANDLE hBmpHelp = ::LoadImage(NULL, _T("theme\\picture\\helpText.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcHelp.CreateCompatibleDC(&dc);
	//将位图资源选入DC
	m_dcHelp.SelectObject(hBmpHelp);

	//创建内存大小
	CRect rtClient;
	this->GetWindowRect(&rtClient);
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, rtClient.Width(), rtClient.Height());
	m_dcMem.SelectObject(&bmpMem);
	//绘制白色背景
	m_dcMem.BitBlt(0, 0, rtClient.Width(), rtClient.Height(), NULL, 0, 0, WHITENESS);
	//设置显示区域
	m_rtHelp.top = 0;
	m_rtHelp.left = 0;
	m_rtHelp.right = 800;
	m_rtHelp.bottom = 600;

	//绘制帮助信息
	UpdateHelp(0);
	


	//设置滚动条范围
	CBitmap bmapHelp;
	bmapHelp.Attach(hBmpHelp);
	BITMAP bmpinfo;
	bmapHelp.GetBitmap(&bmpinfo);
	((CScrollBar*)this->GetDlgItem(IDC_SCROLLBAR_HELP))->SetScrollRange(0, bmpinfo.bmHeight, FALSE);
	return TRUE;

}

void CHelpDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHelpDialog, CDialogEx)
	ON_WM_PAINT()
	ON_WM_VSCROLL()
END_MESSAGE_MAP()



void CHelpDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);

}

void CHelpDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int pos = nPos;
	switch (nSBCode)
	{
	case SB_LINEUP:
		pos -= 1;
		break;
	case SB_LINEDOWN:
		pos += 1;
		break;
	case SB_PAGEUP:
		pos -= 10;
		break;
	case SB_PAGEDOWN:
		pos += 10;
		break;
	case SB_TOP:
		pos = nMinPos;
		break;
	case SB_BOTTOM:
		pos = nMaxPos;
		break;
	case SB_THUMBPOSITION:
		pos = nPos;
		break;
	default:
		break;
	}

	//设置滚动条当前的值
	pScrollBar->SetScrollPos(pos, TRUE);
	//更新帮助信息
	UpdateHelp(pos);

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CHelpDialog::UpdateHelp(int nPos)
{
	//将重绘区绘制成白色
	m_dcMem.BitBlt(m_rtHelp.left, m_rtHelp.top, m_rtHelp.Width(), m_rtHelp.Height(), NULL, 0, 0, BLACKNESS);
	//绘制当前帮助信息
	m_dcMem.BitBlt(m_rtHelp.left, m_rtHelp.top, m_rtHelp.Width(), m_rtHelp.Height(), &m_dcHelp, 0, nPos, SRCCOPY);
	InvalidateRect(m_rtHelp, FALSE);
}

