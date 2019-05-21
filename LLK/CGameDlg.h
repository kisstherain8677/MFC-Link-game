#pragma once
#include"global.h"
#include"CGameControl.h"

// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	
	CGameDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	CDC m_dcMem;//内存DC
	CDC m_dcElement;//元素内存DC
	CDC m_dcMask;//掩码内存DC
	CDC m_dcBG;//背景DC
	CPoint m_ptGameTop;//元素初始位置
	CSize m_sizeElement;//元素大小
	bool m_bFirstPoint;//是否第一次选中
	
	CRect m_rtGameRect;//游戏区域大小
	CGameControl m_gameControl;
	bool m_bPlaying;//true表示游戏正在进行




	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void InitBackground();
	void InitElement();
	void UpdateMap();
	void DrawTipFrame(int nRow, int nCol);//根据行号列号绘制矩形提示框
	void DrawTipLine(int asvPath[16],int VexNum);//绘制连接线

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();

	
	afx_msg void OnClickedButtonStart();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClickedButtonHint();
};
