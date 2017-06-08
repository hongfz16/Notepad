
// ChildView.cpp : CChildView 类的实现
//


#include "stdafx.h"
//#include"kernal.h"
#include "ChildView.h"
#include"MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//#define M_DEBUG
//#define ORI



// CChildView

CChildView::CChildView(){//:re_m_client_cy(temp) ,re_scrollpix(temp)  {
  m_text = new SITEXT;
  LBuDown = false;
  need_recompute = true;
  /*
  for (int i = 0; i < 10000; ++i)
  {
//	  for (int j = 0; j < 20; ++j)
	  {
		  m_text->ins_char('A');
	  }
	//  m_text->ins_char('\n');
  }
  */
}

CChildView::~CChildView() { delete m_text; }

BEGIN_MESSAGE_MAP(CChildView, CWnd)
ON_WM_PAINT()
ON_WM_CHAR()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
ON_WM_KEYDOWN()
ON_WM_KEYUP()
ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CChildView 消息处理程序

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) {
  if (!CWnd::PreCreateWindow(cs)) return FALSE;

  cs.dwExStyle |= WS_EX_CLIENTEDGE;
  cs.style &= ~WS_BORDER;
  cs.lpszClass = AfxRegisterWndClass(
      CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS, ::LoadCursor(NULL, IDC_ARROW),
      reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), NULL);

  return TRUE;
}

void CChildView::OnPaint() {

#ifndef ORI
	
	CRect PaintRect;
	CPaintDC dc(this);
	CDC MemDC;
	CBitmap MemBitmap;
	// 双缓冲绘图  
	GetClientRect(PaintRect);
	if (MemDC.CreateCompatibleDC(&dc))
	{
		if (MemBitmap.CreateCompatibleBitmap(&dc, PaintRect.Width(), PaintRect.Height()))
		{
			if (HGDIOBJ OldObject = MemDC.SelectObject(MemBitmap))
			{
				// 拷贝背景图, 以处理透明色  
				if (MemDC.BitBlt(0, 0, PaintRect.Width(), PaintRect.Height(), &dc, 0, 0, SRCCOPY))
				{
					Gdiplus::Graphics g(MemDC);
					MemDC.FillSolidRect(&PaintRect,RGB(255, 255, 255));
					// Paint here ...  

					if (m_text->text_changed_f) {
#ifdef M_DEBUG
						MessageBox(_T("after_repaint"));
#endif
						if (need_recompute)
						{
							//MessageBox(_T("recompute"));
							m_text->repaint();
						}
							m_paintText(MemDC);
							m_paintCur(MemDC);
						
						int temp = mainframep->m_client_cy;
						MemDC.MoveTo(0, temp);
						MemDC.LineTo(1000, temp);
#ifdef M_DEBUG
						MessageBox(_T("End OnPaint"));
#endif
					}

					dc.BitBlt(0, 0, PaintRect.Width(), PaintRect.Height(), &MemDC, 0, 0, SRCCOPY);
				}
				MemDC.SelectObject(OldObject);
			}
			MemBitmap.DeleteObject();
		}
		MemDC.DeleteDC();
	}
#endif
#ifdef ORI
  CPaintDC dc(this);  // 用于绘制的设备上下文
  //CDC* dc = this->GetDC();
  m_text->repaint();
  
  if (m_text->text_changed_f) {
#ifdef M_DEBUG
	  MessageBox(_T("after_repaint"));
#endif
	  m_paintText(dc);
	  m_paintCur(dc);
#ifdef M_DEBUG
	  MessageBox(_T("End OnPaint"));
#endif
  }
#endif
  m_text->text_changed_f = false;
  need_recompute = false;
  CString strtemp;
  strtemp.Format(_T("%d %d"), mainframep->maincy,mainframep->m_client_cy);
  //MessageBox(_T("OnPaint"));
}

void CChildView::m_paintText(CDC& dc)
{
	SICHARNODE_P curr = m_text->headp->nextp;
	while (curr->nextp != NULL)
	{
		if (isenter(curr->ch))
		{
			curr = curr->nextp;
			continue;
		}
#ifdef M_DEBUG
		MessageBox(_T("Not empty"));
#endif
		CFont font;
		font.CreateFontIndirectW(&(*(curr->get_char_infop()->get_fontpc())));
		dc.SelectObject(&font);
		dc.SetTextColor(curr->get_char_infop()->get_color());
#ifdef M_DEBUG
		dc.SetTextColor(RGB(255, 0, 0));
#endif
		int posx = curr->draw_infop->POS.x;//curr->get_draw_infop()->get_POS().x;
		int posy = curr->draw_infop->POS.y;//curr->get_draw_infop()->get_POS().y;
		int width = curr->draw_infop->L.width;//get_draw_infop()->get_L().width;
		int height = curr->draw_infop->L.height;//get_draw_infop()->get_L().height;
		CRect outrect(CPoint(posx, posy), CPoint(posx + width, posy + height));
		CString str(curr->ch);
#ifdef M_DEBUG
		CRect outrect(CPoint(0, 0), CPoint(100, 100));
		MessageBox(str);
#endif
		dc.FillSolidRect(&outrect,curr->char_infop->bgcolor);
		dc.DrawTextW(str, &outrect, DT_SINGLELINE | DT_CENTER | DT_BOTTOM);
		curr = curr->nextp;
	}
}

void CChildView::m_paintText(CPaintDC& dc)
{
	SICHARNODE_P curr = m_text->headp->nextp;
	while (curr->nextp != NULL)
	{
		if (isenter(curr->ch))
		{
			curr = curr->nextp;
			continue;
		}
#ifdef M_DEBUG
		MessageBox(_T("Not empty"));
#endif
		CFont font;
		font.CreateFontIndirectW(&(*(curr->get_char_infop()->get_fontpc())));
		dc.SelectObject(&font);
		dc.SetTextColor(curr->get_char_infop()->get_color());
#ifdef M_DEBUG
		dc.SetTextColor(RGB(255, 0, 0));
#endif
		int posx = curr->draw_infop->POS.x;//curr->get_draw_infop()->get_POS().x;
		int posy = curr->draw_infop->POS.y;//curr->get_draw_infop()->get_POS().y;
		int width = curr->draw_infop->L.width;//get_draw_infop()->get_L().width;
		int height = curr->draw_infop->L.height;//get_draw_infop()->get_L().height;
		CRect outrect(CPoint(posx, posy), CPoint(posx + width, posy + height));
		CString str(curr->ch);
#ifdef M_DEBUG
		CRect outrect(CPoint(0, 0), CPoint(100, 100));
		MessageBox(str);
#endif
		dc.FillSolidRect(&outrect, curr->char_infop->bgcolor);
		dc.DrawTextW(str, &outrect, DT_SINGLELINE | DT_CENTER | DT_BOTTOM);
		curr = curr->nextp;
	}
}

void CChildView::m_paintCur(CDC& dc) {
  SICURSORP curr = m_text->cursorp;
  int posx = curr->get_draw_infop()->get_POS().x;
  int posy = curr->get_draw_infop()->get_POS().y;
  int width = curr->get_draw_infop()->get_L().width;
  int height = curr->get_draw_infop()->get_L().height;

  dc.MoveTo(posx, posy);
  dc.LineTo(posx, posy + height);
}

void CChildView::m_paintCur(CPaintDC& dc) {
	SICURSORP curr = m_text->cursorp;
	int posx = curr->get_draw_infop()->get_POS().x;
	int posy = curr->get_draw_infop()->get_POS().y;
	int width = curr->get_draw_infop()->get_L().width;
	int height = curr->get_draw_infop()->get_L().height;

	dc.MoveTo(posx, posy);
	dc.LineTo(posx, posy + height);
}


void CChildView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
  // TODO: 在此添加消息处理程序代码和/或调用默认值
  SICHAR_T wchar = nChar;
  if (nChar == VK_BACK) {
    if (m_text->select.sp == NULL && m_text->select.ep == NULL) {
      m_text->del_char(SIBACKSPACE);
    } else {
      m_text->del_select();
    }
  } else if (nChar == VK_DELETE) {
    if (m_text->select.sp == NULL && m_text->select.ep == NULL) {
      m_text->del_char(SIDELETE);
    } else {
      m_text->del_select();
    }
  }
  
  else if (nChar == VK_TAB)
  {
	  for (int i = 0; i < 4; ++i)
		  m_text->ins_char(' ');
  }
  
  else {//if (is_input(nChar)) {
	  if (m_text->select.ep != m_text->select.sp && m_text->select.ep != NULL)
		  m_text->del_select();
#ifdef M_DEBUG
	  MessageBox(_T("OnChar"));
#endif
	  m_text->ins_char(wchar);
  }
  ///<adjust the m_client_cy>
  if (m_text->tailp->get_draw_infop()->get_POS().y + m_text->tailp->get_draw_infop()->get_L().height < mainframep->maincy)
	  mainframep->m_client_cy = mainframep->maincy;
  else if (m_text->tailp->get_draw_infop()->get_POS().y + m_text->tailp->get_draw_infop()->get_L().height > mainframep->m_client_cy)
	  mainframep->m_client_cy = m_text->tailp->get_draw_infop()->get_POS().y + 10 + m_text->tailp->get_draw_infop()->get_L().height;
  ///</end>

  ///<adjust the screen pos according to the cursor pos>
  if (m_text->cursorp->get_draw_infop()->get_POS().y - mainframep->scrolledpix + m_text->cursorp->get_draw_infop()->get_L().height > mainframep->maincy)
	  mainframep->scrolledpix = m_text->cursorp->get_draw_infop()->get_POS().y - mainframep->maincy + m_text->cursorp->get_draw_infop()->get_L().height;
  if (m_text->cursorp->get_draw_infop()->get_POS().y - mainframep->scrolledpix -10 < 0 && mainframep->scrolledpix!=0)
	  mainframep->scrolledpix = m_text->cursorp->get_draw_infop()->get_POS().y - m_text->cursorp->get_draw_infop()->get_L().height;
  ///</end>
  mainframep->UpdateClientRect();
  mainframep->UpdateScrollBarPos();
  
  /*
  
  */
  //mainframep->UpdateScrollBarPos();
  need_recompute = true;
  m_changed();
  CWnd::OnChar(nChar, nRepCnt, nFlags);
}

inline bool CChildView::is_input(UINT nChar) {
  /*
  if((nChar>=0x30 && nChar<=0x39)
          ||(nChar>=0x41 && nChar<=0x5A)
          ||())
          */
  if (nChar != VK_BACK && nChar != VK_DELETE) {
    return true;
  }
  else return false;
}

inline void CChildView::m_changed() {
  m_text->text_changed_f = true;
  Invalidate(true);
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point) {
  // TODO: 在此添加消息处理程序代码和/或调用默认值
  LBuDown = true;
  //if (m_text->select.ep == NULL && m_text->select.sp == NULL) {
	m_text->cancel_select();
    m_text->cursorp = m_text->point_to_cursorp(SIPOINT(point.x, point.y));
    m_text->mov_cursorp(m_text->cursorp);
    m_text->start_select();
  //} else {
    // move?
    // need a move_flag for ONLButtonUp to decide whether to clear selection
  //}
#ifdef M_DEBUG
  MessageBox(_T("LDown"));
#endif
  m_changed();
  CWnd::OnLButtonDown(nFlags, point);
}

void CChildView::OnLButtonUp(UINT nFlags, CPoint point) {
  // TODO: 在此添加消息处理程序代码和/或调用默认值
  LBuDown = false;
  if (m_text->select.ep == NULL) {
    m_text->cursorp = m_text->point_to_cursorp(SIPOINT(point.x, point.y));
    m_text->mov_cursorp(m_text->cursorp);
    m_text->end_select();
  } else {
    m_text->cursorp = m_text->point_to_cursorp(SIPOINT(point.x, point.y));
    m_text->mov_cursorp(m_text->cursorp);
    m_text->cancel_select();
  }
  m_changed();
  CWnd::OnLButtonUp(nFlags, point);
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point) {
  // TODO: 在此添加消息处理程序代码和/或调用默认值
  if (LBuDown == true) {
    m_text->cursorp = m_text->point_to_cursorp(SIPOINT(point.x, point.y));
    m_text->mov_cursorp(m_text->cursorp);
	m_changed();
  }
  
  CWnd::OnMouseMove(nFlags, point);
}

void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
  // TODO: 在此添加消息处理程序代码和/或调用默认值
  if (nRepCnt >= 1) {
	  for (int i = nRepCnt; i != 0; --i) {
		  switch (nChar) {
		  case VK_UP:
			  m_text->mov_cursorp(m_text->DUP);
			  break;
		  case VK_DOWN:
			  m_text->mov_cursorp(m_text->DDOWN);
			  break;
		  case VK_LEFT:
			  m_text->mov_cursorp(m_text->DLEFT);
			  break;
		  case VK_RIGHT:
			  m_text->mov_cursorp(m_text->DRIGHT);
			  break;
		  }
	  }
	m_changed();
  }
  CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CChildView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) {
  // TODO: 在此添加消息处理程序代码和/或调用默认值
	/*
  switch (nChar) {
    case VK_UP:
      m_text->mov_cursorp(m_text->DUP);
      break;
    case VK_DOWN:
      m_text->mov_cursorp(m_text->DDOWN);
      break;
    case VK_LEFT:
      m_text->mov_cursorp(m_text->DLEFT);
      break;
    case VK_RIGHT:
      m_text->mov_cursorp(m_text->DRIGHT);
      break;
  }
  m_changed();
  */
  CWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
#ifndef ORI
	return false;
#else
	return CWnd::OnEraseBkgnd(pDC);
#endif
}
