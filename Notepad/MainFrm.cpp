
// MainFrm.cpp : CMainFrame 类的实现
//
//#include"kernal.h"

#include "stdafx.h"
#include "Notepad.h"

#include "MainFrm.h"

#include "M_PARA_DIA.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
	m_client_cy = 2500;
	scrolledpix = 0;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 创建一个视图以占用框架的工作区
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("未能创建视图窗口\n");
		return -1;
	}
	m_wndView.mainframep = this;
	//m_wndView.re_m_client_cy = m_client_cy;
	//m_wndView.re_scrollpix = scrolledpix;
	//create the scroll bar
	m_scrollBar.Create(
		SB_VERT | SBS_RIGHTALIGN | WS_CHILD | WS_VISIBLE, CRect(0, 0, 100, 100), this, 10);
	m_scrollBar.ShowScrollBar();
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// 将焦点前移到视图窗口
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// 让视图第一次尝试该命令
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// 否则，执行默认处理
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}



void CMainFrame::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect temp1;
	m_scrollBar.GetClientRect(&temp1);
	int nMin, nMax, nCurpos;
	pScrollBar = &m_scrollBar;
	pScrollBar->SetScrollRange(0, m_client_cy);
	pScrollBar->GetScrollRange(&nMin, &nMax);  
	nCurpos = pScrollBar->GetScrollPos();
	double prop = double(m_client_cy) / double(maincy);// double(m_client_cy-(temp1.bottom-temp1.top)) / double(nMax - nMin);
	switch (nSBCode)
	{
	case SB_LINEUP:
		nCurpos--;
		break;
	case SB_LINEDOWN:
		nCurpos++;
		break;   
	case SB_THUMBTRACK: 
		nCurpos = nPos;
		break;
	}
	if (nCurpos < nMin)
	{
		nCurpos = nMin;
	}
	if (nCurpos > nMax)
	{
		nCurpos = nMax;
	}
	pScrollBar->SetScrollPos(nCurpos);  
	CRect temp = &m_client_rect;
	temp.top = -nCurpos*prop;
	temp.bottom = m_client_cy - nCurpos*prop;
	scrolledpix = nCurpos*prop;
	m_wndView.MoveWindow(temp);
	m_wndView.m_changed();
	CFrameWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CMainFrame::UpdateScrollBarPos()
{
	CRect temp;
	m_scrollBar.GetClientRect(&temp);
	int n_min, n_max;

	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL;
	si.nMin = 0;
	si.nMax = m_client_cy;//你滑动画面的高度
	si.nPage = temp.Height();  //这个是你显示画面的高度
	si.nPos = double(scrolledpix) * (maincy) / m_client_cy ;//这个是滑块的位置  初始化的时候是0 以后会根据你的操作变动
	m_scrollBar.SetScrollInfo(&si);

	
	//m_scrollBar.SetScrollRange(0, temp.bottom);
	//m_scrollBar.GetScrollRange(&n_min, &n_max);
	//int new_pos = scrolledpix*(n_max - n_min) /(m_client_cy-temp.Height());
	//m_scrollBar.SetScrollPos(new_pos);
	
}


void CMainFrame::UpdateClientRect()
{
	CRect viewrect;
	m_wndView.GetClientRect(&viewrect);
	viewrect.right =maincx- 20;
	viewrect.left = 0;
	viewrect.top = -scrolledpix;
	viewrect.bottom = viewrect.top + m_client_cy;
	m_client_rect = viewrect;
	m_wndView.MoveWindow(&viewrect);
}

void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);
	maincx = cx;
	maincy = cy;

	//adjust the scroll bar
	CRect rect;
	m_scrollBar.GetClientRect(&rect);
	rect.right = cx;
	rect.left = cx - 20;
	rect.bottom = cy;
	m_scrollBar.MoveWindow(&rect);
	//adjust the client
	UpdateClientRect();
	//adjust the scroll bar pos
	UpdateScrollBarPos();
	//repaint
	m_wndView.m_text->set_pagewidth(cx);
	m_wndView.m_text->text_changed_f = true;
	m_wndView.m_changed();
	//Invalidate(true);
	//Unsure if it is needed
	// TODO: 在此处添加消息处理程序代码
}
