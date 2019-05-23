#pragma once


// CHelpDialog 对话框

class CHelpDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CHelpDialog)

public:
	CHelpDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CHelpDialog();

	virtual BOOL OnInitDialog();//将帮助图片加载到内存DC
	afx_msg void OnPaint();
	HBRUSH OnCtlColor(CDC *pDC, CWnd * pWnd, UINT nCtlColor);//WM_CTLCOLOR响应函数


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD__DIALOG_HELP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	HICON m_hIcon;//系统图片
	CDC m_dcMem;//内存DC
	CDC m_dcHelp;//帮助图片DC
	CRect m_rtHelp;//帮助图片显示区域

	int nMinPos = 0;
	int nMaxPos = 1000;
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnStnClickedStaticHelp();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void UpdateHelp(int nPos);
};


