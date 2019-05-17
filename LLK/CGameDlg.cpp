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
	HANDLE bmp = ::LoadImage(NULL, _T("theme\\picture\\basic_bg.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);;
	CClientDC dc(this);
	m_dcMem.CreateCompatibleDC(&dc);
	m_dcMem.SelectObject(bmp);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_BASIC, &CGameDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CGameDlg 消息处理程序


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitBackground();


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


void CGameDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
}
