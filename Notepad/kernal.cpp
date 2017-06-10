#include "stdafx.h"
#include "lib.h"
#include "kernal.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
HDC globalhdc;


void del(SICHARNODE* p)
{
	p->prevp->nextp = p->nextp;
	p->nextp->prevp = p->prevp;
	delete p;
}
void del(SICHARNODE* ps, SICHARNODE* pe)
{
	if (ps == pe) return;
	if (ps->nextp == pe)
	{
		del(ps);
		return;
	}
	SICHARNODE_P p;
	ps->prevp->nextp = pe;
	pe->prevp = ps->prevp;
	for (p = ps->nextp; p->nextp != pe; p = p->nextp) delete p->prevp;
	delete p->prevp;
	delete p;
}
void del(const SIRANGE& range)
{
	del(range.sp, range.ep);
}

void print_font(const SIFONT& tfont)
{
	cout << tfont.lfHeight << " " << tfont.lfWidth << " "
		<< tfont.lfEscapement << " " << tfont.lfOrientation << " "
		<< tfont.lfWeight << endl;
	printf("%u %u %u %u %u %u %u\n", tfont.lfItalic, tfont.lfUnderline,
		tfont.lfStrikeOut, tfont.lfCharSet, tfont.lfOrientation,
		tfont.lfClipPrecision, tfont.lfQuality, tfont.lfPitchAndFamily);
	wprintf(L"%s\n", tfont.lfFaceName);

}

inline void si_getline(wchar_t* S)
{
	wchar_t t = getwchar();
	while (t == L' ' || t == L'\n' || t == L'\r') t = getwchar();
	int N = 0;
	while (t != L'\n'&&t != L'\r')
	{
		S[N++] = t;
		t = getwchar();
	}
	S[N++] = L'\0';
}
void read_font(SIFONT& tfont)
{
	std::cin >> tfont.lfHeight >> tfont.lfWidth
		>> tfont.lfEscapement >> tfont.lfOrientation
		>> tfont.lfWeight;
	scanf("%u %u %u %u %u %u %u", &tfont.lfItalic, &tfont.lfUnderline,
		&tfont.lfStrikeOut, &tfont.lfCharSet, &tfont.lfOrientation,
		&tfont.lfClipPrecision, &tfont.lfQuality, &tfont.lfPitchAndFamily);
	si_getline(tfont.lfFaceName);
}
void print_ch(const SICHAR_T& tch)
{
	printf("%d\n", tch);
}
void read_ch(SICHAR_T& tch)
{
	int d;
	scanf("%d", &d);
	tch = d;
}


void SICHARNODE::ins_prev(SICHARNODE* p)
{
	p->prevp = this->prevp;
	p->nextp = this;
	this->prevp->nextp = p;
	this->prevp = p;
	*(prevp->char_infop) = *(prevp->prevp->char_infop);
	prevp->calc_S_from_font();
}
void SICHARNODE::ins_next(SICHARNODE* p)
{
	p->prevp = this;
	p->nextp = this->nextp;
	this->nextp->prevp = p;
	this->nextp = p;

	(*nextp->char_infop) = *(char_infop);
	nextp->calc_S_from_font();
}
void SICHARNODE::ins_prev(SICHARNODE* ps, SICHARNODE* pe)
{
	ps->prevp = this->prevp;
	pe->nextp = this;
	this->prevp->nextp = ps;
	this->prevp = pe;
}
void SICHARNODE::ins_next(SICHARNODE* ps, SICHARNODE* pe)
{
	ps->prevp = this;
	pe->nextp = this->nextp;
	this->nextp->prevp = pe;
	this->nextp = ps;
}

void SICHARNODE::calc_S_from_font()
{
	int height = 1.5 * (-char_infop->fontpc->lfHeight * 72 / GetDeviceCaps(globalhdc, LOGPIXELSY));
	int width = 0.7 * height;
	draw_infop->set_S(width, height);
}

void SICHARNODE::set_fontpc(SIFONT& tfont)
{
	char_infop->set_fontpc(tfont);
	calc_S_from_font();
}
void SITEXT::_init()
{
	headp = new SICHARNODE('\n');
	tailp = new SICHARNODE('\n');
	*(tailp->char_infop) = *(headp->char_infop);
	headp->nextp = tailp;
	tailp->prevp = headp;
	cursorp = tailp;
	curfontpc = NULL;
	pagewidth = DEFAULT_PAGEWIDTH;
	vlinep.clear();
	vparap.clear();
	select._clear();
	save_path = "$";
	open_path = "$";
	text_changed_f = false;
	set_curfontp_f = false;
	inselect = false;
	fwdnum = 0;
}
void SITEXT::_destroy()
{
	save_path.clear();
	open_path.clear();
	vlinep.clear();
	vparap.clear();
	select._clear();
	delete curfontpc;
	for (SICHARNODE_P p = headp->nextp; p != tailp; p = p->nextp)
		delete p->prevp;
	delete tailp;
}


SICHAR_INFO& SICHAR_INFO::operator =(const SICHAR_INFO& tinfo)
{
	if (&tinfo == this) return *this;
	*fontpc = *(tinfo.fontpc);
	color = tinfo.color;
	bgcolor = tinfo.bgcolor;
	cspace = tinfo.cspace;
	lspace = tinfo.lspace;
	align = tinfo.align;
	return *this;
}
void SICHAR_INFO::print_info()
{
	print_font(*fontpc);
	printf("%d %d %d %d %d %d\n", color, bgcolor, size, cspace, lspace, align);
}
void SICHAR_INFO::read_info()
{
	read_font(*fontpc);
	std::cin >> color >> bgcolor >> size >> cspace >> lspace >> align;
}

void SIRECT::print_info()
{
	printf("%d %d\n", width, height);
}
void SIRECT::read_info()
{
	std::cin >> width >> height;
}
void SIPOINT::print_info()
{
	printf("%d %d\n", x, y);
}
void SIPOINT::read_info()
{
	std::cin >> x >> y;
}

void SIDRAW_INFO::print_info()
{
	S.print_info();
	L.print_info();
	POS.print_info();
}
void SIDRAW_INFO::read_info()
{
	S.read_info();
	L.read_info();
	POS.read_info();
}

void SICHARNODE::print_info()
{
	print_ch(ch);
	char_infop->print_info();
	draw_infop->print_info();
	printf("\n\n");
}
void SICHARNODE::read_info()
{
	read_ch(ch);
	char_infop->read_info();
	draw_infop->read_info();
}


void SITEXT::print_info()
{
	int N = 1;
	std::cout << save_path << std::endl;
	std::cout << open_path << std::endl << pagewidth << std::endl;
	print_font(default_font);
	for (SICHARNODE_P p = headp; p != tailp; p = p->nextp) ++N;
	printf("%d\n", N);
	headp->print_info();
	tailp->print_info();
	for (SICHARNODE_P p = headp->nextp; p != tailp; p = p->nextp)
		p->print_info();
}

void SITEXT::read_info()
{
	_destroy();
	_init();
	int N;
	std::cin >> save_path >> open_path >> pagewidth;
	read_font(default_font);
	std::cin >> N;
	for (int i = 3; i <= N; ++i) ins_char(' ');
	headp->read_info();
	tailp->read_info();
	for (SICHARNODE_P p = headp->nextp; p != tailp; p = p->nextp)
		p->read_info();

}

void SITEXT::draw_line_from_left(SICHARNODE_P ps, SICHARNODE_P pe, int sx, int y, int line_height, int deltax)
{
	int x;
	SICHARNODE_P p;
	SIDRAW_INFO_P pd;

	for (x = sx, p = ps; p != pe; p = p->nextp)
	{
		pd = p->draw_infop;
		pd->L.height = line_height;
		pd->L.width = pd->S.width + p->char_infop->cspace + deltax;
		pd->POS = SIPOINT(x, y);
		if (pd->S.width == 0) pd->L.width = 0;
		x += pd->L.width;
	}

}


void SITEXT::proc_line(SICHARNODE_P ps, SICHARNODE_P pe,
	int n, int y, int line_height, int tot_width, SIALIGN align)
{
	//if (n == 0) return;
	int sx = 0, deltax = 0;

	if (align == ANORMAL || align == ALEFT)
	{
		//draw_line_from_left(ps, pe, 0, y, line_height, 0);
		sx = 0;
		deltax = 0;
	}
	if (align == ARIGHT)
	{
		//draw_line_from_left(ps, pe, pagewidth - tot_width, y, line_height, 0);
		sx = pagewidth - tot_width;
		deltax = 0;
	}
	if (align == ACENTER)
	{
		//draw_line_from_left(ps, pe, (pagewidth - tot_width) >> 1, y, line_height, 0);
		sx = (pagewidth - tot_width) >> 1;
		deltax = 0;
	}
	if (align == ADISTRIBUTED)
	{
		//draw_line_from_left(ps, pe, 0, y, line_height, (pagewidth - tot_width) / n);
		sx = 0;
		if (n > 0) deltax = (pagewidth - tot_width) / n;
	}

	draw_line_from_left(ps, pe, sx, y, line_height, deltax);
	return;
}
void SITEXT::pre_proc()
{
	SICHARNODE_P p;
	for (p = headp->nextp; p != tailp; p = p->nextp)
	{
		if (isenter(p->ch) && isenter(p->nextp->ch))
		{
			p->ins_next(new SICHARNODE(' ', 0, p->draw_infop->S.height));
			p->nextp->set_size(-1);
		}
		if (p->char_infop->size == -1)
		{
			p->draw_infop->S.width = 0;
			p->char_infop->cspace = 0;
		}
	}
}
void SITEXT::proc_text()
{
	SICHARNODE_P ps, pe, pps;
	SIDRAW_INFO_P pd;
	SICHAR_INFO_P pc;
	int tot_width;
	int n;
	int line_height;
	int y;
	int align;

	vlinep.clear();
	vparap.clear();

	for (y = 0, ps = headp->nextp, pps = headp; ps != tailp; ps = pe)
	{
		tot_width = 0;
		line_height = 0;
		n = 0;
		for (pe = ps; tot_width <= pagewidth && (!isenter(pe->ch)); pe = pe->nextp)
		{
			++n;
			pd = pe->draw_infop;
			pc = pe->char_infop;
			tot_width += (pd->S.width + pc->cspace);
			line_height = Max(line_height, pd->S.height + pc->lspace);
			if (tot_width > pagewidth)
			{
				tot_width -= (pd->S.width + pc->cspace);
				--n;
				break;
			}
		}
		//if(tot_width>)--n;
		//if (ps->draw_infop->S.width == 0) --n;
		if (isenter(pe->ch) && pe != tailp)
		{
			vparap.push_back(SIPARAGRAPH(pps->nextp, pe));
			pps = pe;
			pe = pe->nextp;
		}
		if (ps->draw_infop->S.width == 0) --n;
		vlinep.push_back(SILINE(ps, pe));
		align = get_range_align(ps, pe);
		proc_line(ps, pe, n, y, line_height, tot_width, align);
		y += line_height;
		if (pe == tailp)
		{
			tailp->draw_infop->POS = tailp->prevp->draw_infop->POS
				+ SIPOINT(tailp->prevp->draw_infop->L.width, 0);
			break;
		}
	}
	tailp->draw_infop->L.height = tailp->prevp->draw_infop->L.height;
	if (tailp->prevp == headp) tailp->draw_infop->POS.x = 0;
}
SICURSORP SITEXT::point_to_cursorp(const SIPOINT& P)
{
	SICURSORP p;
	std::vector<SILINE>::iterator it;
	for (it = vlinep.begin(); it != vlinep.end(); ++it)
		if (point_on_line(*it, P)) break;
	if (it == vlinep.end()) return tailp;
	p = it->sp;
	if (p->draw_infop->POS.y <= P.y&&P.y < p->draw_infop->POS.y + p->draw_infop->L.height
		&& P.x < p->draw_infop->POS.x)
	{
		if (p->draw_infop->L.width == 0) p = p->nextp;
		return p;
	}
	for (p = it->sp; p != it->ep; p = p->nextp)
		if (point_on_char_col(p, P)) break;
	if (p == it->ep)
		if (p != tailp)
			p = p->prevp;
	if (p->nextp != NULL && (p->nextp != it->ep || p->nextp == tailp) && (P.x > p->draw_infop->POS.x + (double)(p->draw_infop->L.width) / 2.0))
		return p->nextp;
	else
		return p;
}
void SITEXT::del_char(bool backwards = true)
{
	SICHARNODE_P prevp, pprevp, curp, nextp;
	prevp = cursorp->prevp;
	curp = cursorp;
	nextp = curp->nextp;
	if (backwards&&prevp != headp)
	{
		pprevp = prevp->prevp;
		if (prevp->draw_infop->S.width == 0 && pprevp != headp&&isenter(pprevp->ch))
			del(pprevp);
		del(prevp);
	}
	if ((!backwards) && nextp != NULL)
	{
		if (isenter(curp->ch) && nextp->draw_infop->S.width == 0)
			del(nextp);
		cursorp = cursorp->nextp;
		del(cursorp->prevp);
	}
}

void SITEXT::end_select()
{
	if (select.sp == NULL) return;
	select.ep = cursorp;
	if (select.sp->draw_infop->POS > select.ep->draw_infop->POS)
		exchange<SICHARNODE_P>(select.sp, select.ep);
	if (select.sp == select.ep) select._clear();
	anticolor(select.sp, select.ep);
	//if (fwdnum < 0) exchange<SICHARNODE_P>(select.sp, select.ep);
	//if (fwdnum == 0) select._clear();
	//inselect = false;
	//fwdnum = 0;
}
void SITEXT::del_select()
{
	if (select.ep == NULL) return;
	cursorp = select.ep;
	anticolor(select.sp, select.ep);
	del(select.sp, select.ep);
	select._clear();
}

void SITEXT::mov_cursorp(SIDIRECT tdir)
{
	switch (tdir)
	{
	case DLEFT:
		if (cursorp->prevp != headp)
		{
			cursorp = cursorp->prevp;
			if (cursorp->draw_infop->S.width == 0 && cursorp->prevp != headp && isenter(cursorp->prevp->ch))
				cursorp = cursorp->prevp;
		}
		break;
	case DRIGHT:
		if (cursorp->nextp != NULL)
		{
			cursorp = cursorp->nextp;
			if (cursorp->draw_infop->S.width == 0 && cursorp->nextp != NULL&&isenter(cursorp->prevp->ch))
				cursorp = cursorp->nextp;
		}
		break;
	case DUP:
		if (cursorp->draw_infop->POS.y != 0)
			cursorp = point_to_cursorp(cursorp->draw_infop->POS - SIPOINT(0, 1));
		break;
	case DDOWN:
		//if(cursorp->draw_infop->POS.y!=MAX_POSY)
		cursorp = point_to_cursorp(cursorp->draw_infop->POS + SIPOINT(0, cursorp->draw_infop->L.height + 2));
		break;
	}
}
void SITEXT::set_select_align(SIALIGN align)
{
	std::vector<SILINE>::iterator sl, el;
	sl = point_to_line(select.sp->draw_infop->POS);
	el = point_to_line(select.ep->prevp->draw_infop->POS);
	for (std::vector<SILINE>::iterator it = sl; it != el; ++it)
		set_line_align(*it, align);
	set_line_align(*el, align);
	return;
}

SIALIGN SITEXT::get_range_align(SICHARNODE_P ps, SICHARNODE_P pe)
{
	for (SICHARNODE_P p = ps; p != pe; p = p->nextp)
	{
		if (p->char_infop->align != ANORMAL)
			return p->char_infop->align;
	}
	return ANORMAL;
}