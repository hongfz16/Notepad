
// Notepad.h : Notepad 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include "kernal.h"

// CNotepadApp:
// 有关此类的实现，请参阅 Notepad.cpp
//

class CNotepadApp : public CWinApp
{
public:
	CNotepadApp();
	CMainFrame* mainp;

// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

//font dialoge
public:
	afx_msg void OnFont();
//para dialoge
public:
	afx_msg void OnPara();

//cut/copy/paste
public:
	afx_msg void OnCut();
	afx_msg void OnCopy();
	afx_msg void OnPaste();
	afx_msg void OnBackColor();
	SIRANGE m_cutBoard;

// 实现

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CNotepadApp theApp;
