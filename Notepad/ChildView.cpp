
// ChildView.cpp : CChildView 类的实现
//

#include "stdafx.h"
#include "Notepad.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_text = new SITEXT;
	LBuDown = false;
}

CChildView::~CChildView()
{
	delete m_text;
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
END_MESSAGE_MAP()



// CChildView 消息处理程序

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	// TODO: 在此处添加消息处理程序代码
	/*
	CRect draw;
	this->GetClientRect(&draw);
	LOGFONT lf;
	CFontDialog dlg;
	//if(dlg.DoModal() == IDOK)
	//dlg.GetCurrentFont(&lf);
	CFont font;
	//font.CreateFontIndirectW(&lf);
	font.CreatePointFont(100, L"ËÎÌå");
	dc.SelectObject(&font);
	//	LPRECT client;
	//	GetClientRect(client);
	//	CString str;
	//	int temp = client->left;
	//	str.Format(_T("%ld"), client->left);
	CRect draw_ins;
	draw_ins.left = draw.left;
	draw_ins.right = draw.right;
	draw_ins.top = 0;
	draw_ins.bottom = 5000;
	dc.DrawTextW(_T("SDI"), &draw_ins, DT_SINGLELINE | DT_CENTER | DT_BOTTOM);
	dc.Draw3dRect(&draw_ins, (0, 0, 0), (0, 0, 0));
	*/
	// 不要为绘制消息而调用 CWnd::OnPaint()
	m_text->repaint();
	if (m_text->text_changed_f) 
	{
		m_paintText(dc);
		m_paintCur(dc);
	}
	m_text->text_changed_f = false;
}

void CChildView::m_paintText(CPaintDC& dc)
{
	SICHARNODE_P curr = m_text->headp;
	while (curr->get_nextp() != NULL)
	{
		CFont font;
		font.CreateFontIndirectW(&(*(curr->get_char_infop()->get_fontpc())));
		dc.SelectObject(&font);
		dc.SetTextColor(curr->get_char_infop()->get_color());
		int posx = curr->get_draw_infop()->get_POS().x;
		int posy = curr->get_draw_infop()->get_POS().y;
		int width = curr->get_draw_infop()->get_L().width;
		int height = curr->get_draw_infop()->get_L().height;
		CRect outrect(CPoint(posx, posy), CPoint(posx + width, posy + height));
		CString str(curr->get_char());
		dc.DrawTextW(str, &outrect, DT_SINGLELINE | DT_CENTER | DT_BOTTOM);
		curr = curr->get_nextp();
	}
}

void CChildView::m_paintCur(CPaintDC& dc)
{
	SICURSORP curr = m_text->cursorp;
	int posx= curr->get_draw_infop()->get_POS().x;
	int posy = curr->get_draw_infop()->get_POS().y;
	int width = curr->get_draw_infop()->get_L().width;
	int height = curr->get_draw_infop()->get_L().height;
	dc.MoveTo(posx + width, posy);
	dc.LineTo(posx + width, posy + height);
}



void CChildView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	wchar_t wchar = nChar;
	if (nChar == VK_BACK)
	{
		if (m_text->select.sp == NULL && m_text->select.ep == NULL)
		{
			m_text->del_char(SIBACKSPACE);
		}
		else
		{
			m_text->del_select();
		}
	}
	else if (nChar == VK_DELETE)
	{
		if (m_text->select.sp == NULL && m_text->select.ep == NULL)
		{
			m_text->del_char(SIDELETE);
		}
		else
		{
			m_text->del_select();
		}
	}
	else if(is_input(nChar))
	{
		m_text->del_select();
		m_text->ins_char(wchar);
	}
	m_changed();
	CWnd::OnChar(nChar, nRepCnt, nFlags);
}

inline bool CChildView::is_input(UINT nChar)
{
	/*
	if((nChar>=0x30 && nChar<=0x39)
		||(nChar>=0x41 && nChar<=0x5A)
		||())
		*/
	if (nChar != VK_BACK && nChar != VK_DELETE)
	{
		return true;
	}
}

inline void CChildView::m_changed()
{
	m_text->text_changed_f = true;
	Invalidate(true);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	LBuDown = true;
	if (m_text->select.ep == NULL && m_text->select.sp == NULL)
	{
		m_text->cursorp = m_text->point_to_cursorp(SIPOINT(point.x, point.y));
		m_text->mov_cursorp(m_text->cursorp);
		m_text->start_select();
	}
	else
	{
		//move?
		//need a move_flag for ONLButtonUp to decide whether to clear selection 
	}
	m_changed();
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	LBuDown = false;
	if (m_text->select.ep == NULL && m_text->select.sp == NULL)
	{
		m_text->cursorp = m_text->point_to_cursorp(SIPOINT(point.x, point.y));
		m_text->mov_cursorp(m_text->cursorp);
		m_text->end_select();
	}
	else
	{
		m_text->cursorp = m_text->point_to_cursorp(SIPOINT(point.x, point.y));
		m_text->mov_cursorp(m_text->cursorp);
		m_text->clear_select();
	}
	m_changed();
	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (LBuDown == true)
	{
		m_text->cursorp = m_text->point_to_cursorp(SIPOINT(point.x, point.y));
		m_text->mov_cursorp(m_text->cursorp);
	}
	m_changed();
	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nRepCnt > 1) 
	{
		switch (nChar)
		{
		case VK_UP:
			m_text->mov_cursorp(m_text->UP);
			break;
		case VK_DOWN:
			m_text->mov_cursorp(m_text->DOWN);
			break;
		case VK_LEFT:
			m_text->mov_cursorp(m_text->LEFT);
			break;
		case VK_RIGHT:
			m_text->mov_cursorp(m_text->RIGHT);
			break;
		}
	}
	m_changed();
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CChildView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nChar)
	{
	case VK_UP:
		m_text->mov_cursorp(m_text->UP);
		break;
	case VK_DOWN:
		m_text->mov_cursorp(m_text->DOWN);
		break;
	case VK_LEFT:
		m_text->mov_cursorp(m_text->LEFT);
		break;
	case VK_RIGHT:
		m_text->mov_cursorp(m_text->RIGHT);
		break;
	}
	m_changed();
	CWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}
