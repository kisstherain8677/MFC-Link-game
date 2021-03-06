﻿#pragma once
#include"global.h"
#include"CGameControl.h"
#include "CBasicGame.h"
#include "CEasyGame.h"

//音乐相关文件
#include <mmsystem.h>
#pragma comment(lib,"Winmm.lib")
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
	CDC m_dcPause;//暂停图片
	CDC m_dcCache;//保存缓冲
	CPoint m_ptGameTop;//元素初始位置
	CSize m_sizeElement;//元素大小
	bool m_bFirstPoint;//是否第一次选中
	
	CRect m_rtGameRect;//游戏区域大小
	
	CGameControl* m_pGameControl;//设置为指针绕开抽象类不能初始化的问题,可以更好复用代码这里是实现多态的关键

	bool m_bPlaying;//true表示游戏正在进行
	bool m_bPause;
	Flag m_flag;
	bool m_bProp;//表示是否用道具消除
	int m_nProp;//表示道具数量

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void InitBackgroundBasic();
	void InitBackgroundEasy();
	void InitElement();
	void UpdateMap();
	void DrawTipFrame(int nRow, int nCol);//根据行号列号绘制矩形提示框
	void DrawTipLine(int asvPath[MAX_VERTEX_NUM],int VexNum);//绘制连接线
	void DrawGrade();
	void DrawTool();
	//绘制分数
	void CaculateGrade();//计算分数,根据当前分数，决定是否让按键可用
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnClickedButtonStart();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClickedButtonHint();
	afx_msg void OnClickedButtonReset();
	CProgressCtrl m_GameProgress;
	afx_msg void OnTimer(UINT_PTR nIDEvent);


	void DrawGameTime();
	void JudgeWin();
	CGameControl* GetGameControl() {
		return m_pGameControl;
	}
	void SetGameModel(CGameControl* pGameC) {
		m_pGameControl = pGameC;
	}
	
	afx_msg void OnClickedButtonPause();
	afx_msg void OnBnClickedButtonHelp();

	Flag GetFlag();
	void SetFlag(Flag flag);
	afx_msg void OnBnClickedButtonTool();
};
