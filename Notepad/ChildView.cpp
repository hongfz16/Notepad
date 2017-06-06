
// ChildView.cpp : CChildView 类的实现
//

#include "stdafx.h"
//#include"kernal.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//#define M_DEBUG
//#define ORI



// CChildView

CChildView::CChildView() {
  m_text = new SITEXT;
  LBuDown = false;
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
					m_text->repaint();

					if (m_text->text_changed_f) {
#ifdef M_DEBUG
						MessageBox(_T("after_repaint"));
#endif
						m_paintText(MemDC);
						m_paintCur(MemDC);
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
	
	//CDC* pDC = GetDC();
	//CMemDC mdc(*pDC,this);
	//CDC& dc = mdc.GetDC();
	/*
	CPaintDC dc(this);
	//CDC* dc = GetDC();
	CRect rct;
	GetClientRect(&rct);
	CMemDC memDC(dc, rct);
	CDC& pdc = memDC.GetDC();
	pdc.FillSolidRect(&rct, RGB(255,255,255));
	m_paintCur(pdc);
	m_paintText(pdc);
	//CDC *pDC = &memDC.GetDC();    
	//填充背景色  
	dc.BitBlt(0, 0, rct.right, rct.bottom, &pdc, 0, 0, SRCCOPY);
	*/
	//CDC* pDC = GetDC();
	/*
	CPaintDC pdc(this);
	CRect rct;
	GetClientRect(&rct);
	int nWidth = rct.right-rct.left;
	int nHeight = rct.bottom-rct.top;
	
	//nWidth = 1000;
	//nHeight = 1000;
	
	CDC MemDC; //首先定义一个显示设备对象  
	CBitmap MemBitmap;//定义一个位图对象  

					  //随后建立与屏幕显示兼容的内存显示设备  
	MemDC.CreateCompatibleDC(NULL);
	//这时还不能绘图，因为没有地方画 ^_^  
	//下面建立一个与屏幕显示兼容的位图，至于位图的大小嘛，可以用窗口的大小  
	MemBitmap.CreateCompatibleBitmap(pDC, nWidth, nHeight);

	//将位图选入到内存显示设备中  
	//只有选入了位图的内存显示设备才有地方绘图，画到指定的位图上  
	CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);

	//先用背景色将位图清除干净，这里我用的是白色作为背景  
	//你也可以用自己应该用的颜色  
	MemDC.FillSolidRect(0, 0, nWidth, nHeight, RGB(255, 255, 255));

	//绘图  
	m_paintCur(MemDC);
	m_paintText(MemDC);
	//将内存中的图拷贝到屏幕上进行显示  
	pDC->BitBlt(0, 0, nWidth, nHeight, &MemDC, 0, 0, SRCCOPY);

	//绘图完成后的清理  
	MemBitmap.DeleteObject();
	MemDC.DeleteDC();
	*/
#endif
	
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
  //MessageBox(_T("before_repaint"));
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
  else {//if (is_input(nChar)) {
	  if (m_text->select.sp != NULL)
		  m_text->del_select();
#ifdef M_DEBUG
	  MessageBox(_T("OnChar"));
#endif
	  m_text->ins_char(wchar);
  }
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
  if (m_text->select.ep == NULL && m_text->select.sp == NULL) {
    m_text->cursorp = m_text->point_to_cursorp(SIPOINT(point.x, point.y));
    m_text->mov_cursorp(m_text->cursorp);
    m_text->start_select();
  } else {
    // move?
    // need a move_flag for ONLButtonUp to decide whether to clear selection
  }
#ifdef M_DEBUG
  MessageBox(_T("LDown"));
#endif
  m_changed();
  CWnd::OnLButtonDown(nFlags, point);
}

void CChildView::OnLButtonUp(UINT nFlags, CPoint point) {
  // TODO: 在此添加消息处理程序代码和/或调用默认值
  LBuDown = false;
  if (m_text->select.ep == NULL && m_text->select.sp == NULL) {
    m_text->cursorp = m_text->point_to_cursorp(SIPOINT(point.x, point.y));
    m_text->mov_cursorp(m_text->cursorp);
    m_text->cancel_select();
  } else {
    m_text->cursorp = m_text->point_to_cursorp(SIPOINT(point.x, point.y));
    m_text->mov_cursorp(m_text->cursorp);
    m_text->end_select();
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
  if (nRepCnt > 1) {
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
  CWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
#ifndef ORI
	return true;
#else
	return CWnd::OnEraseBkgnd(pDC);
#endif
}

void CChildView::EraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	CRect rect;
	GetClientRect(&rect);
	CBrush brush;
	brush.CreateSolidBrush(RGB(0,0,0));
	pDC->FillRect(&rect, &brush);

}