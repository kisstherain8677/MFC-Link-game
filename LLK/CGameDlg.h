#pragma once


// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CDC m_dcMem;
	CGameDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void InitBackground();

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButton4();
};
