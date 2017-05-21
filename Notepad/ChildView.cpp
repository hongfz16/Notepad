
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
}

CChildView::~CChildView()
{
	delete m_text;
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
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

