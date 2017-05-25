
// ChildView.h : CChildView 类的接口
//


#pragma once

#include "kernal.h"
#include "M_PARA_DIA.h"
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

//keyboard message map
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	inline bool is_input(UINT nChar);


//changed so need repaint
public:
	inline void m_changed();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

//flags
private:
	bool LBuDown;

//other key messages
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};

