
// ChildView.h : CChildView 类的接口
//


#pragma once

#include "kernal.h"
// CChildView 窗口

class CChildView : public CWnd
{
// 构造
public:
	CChildView();

// 特性
public:

// 操作
public:

// 重写
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CChildView();

	// 生成的消息映射函数
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

//Text class
public:
	SITEXT* m_text;
public:
	void m_paintText(CPaintDC& dc);
	void m_paintCur(CPaintDC& dc);
};

