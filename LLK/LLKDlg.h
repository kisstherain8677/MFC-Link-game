﻿
// LLKDlg.h: 头文件
//

#pragma once
//音乐相关文件
#include <Mmsystem.h>
#include<conio.h>
#pragma comment(lib,"Winmm.lib")

// CLLKDlg 对话框
class CLLKDlg : public CDialogEx
{
// 构造
public:
	CLLKDlg(CWnd* pParent = nullptr);	// 标准构造函数
	
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LLK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:

	//声明播放音乐函数
	//BOOL PlaySound(LPCSTR pszSound, HMODULE hmod, DWORD fdwSound);

	CDC m_dcMem;//位图内存
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	//初始化背景DC
	void InitBackground();
public:
	afx_msg void OnClickedButtonBasic();
	afx_msg void OnBnClickedButtonHelp();
	afx_msg void OnBnClickedButtonRelax();
};
