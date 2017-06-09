#include "stdafx.h"
#include "lib.h"
#include "kernal.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
HDC globalhdc;

void SICHARNODE::calc_S_from_font()
{
	//problem
	int height = 1.5 * (-char_infop->fontpc->lfHeight * 72 / GetDeviceCaps(globalhdc, LOGPIXELSY));
	int width = 0.7 * height;
	draw_infop->set_S(width, height);
}

void SICHARNODE::set_fontpc(SIFONT& tfont)
{
	char_infop->set_fontpc(tfont);
	//char_infop->color=char_infop->fontpc->lf
	//int height = -char_infop->fontpc->lfHeight * 72 / GetDeviceCaps(globalhdc, LOGPIXELSY) + 10;
	//int width = height;
	//draw_infop->set_S(width, height);
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
	//default_fontp = new SIFONT;
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
SITEXT::~SITEXT()
{
	_destroy();
}

SITEXT::SITEXT()
{
/*
	headp = new SICHARNODE('\n');
	tailp = new SICHARNODE('\n');
	headp->nextp = tailp;
	tailp->prevp = headp;
	cursorp = tailp;
	//default_fontp = new SIFONT;
	curfontpc = NULL;
	pagewidth = DEFAULT_PAGEWIDTH;
	vlinep.clear();
	vparap.clear();

	text_changed_f = false;
	set_curfontp_f = false;
	inselect = false;
	fwdnum = 0;
	*/
	_init();
}



void SITEXT::print_list()
{
	for (SICHARNODE_P p = headp->nextp; p != tailp; p = p->nextp)
	{
		if (isenter(p->ch))
		{
			printf("-------------------------\n");
			continue;
		}
		printf("%c\n", p->ch);
		//		p->draw_infop->POS->print();
		p->draw_infop->POS.print();
		printf("\n");
		p->draw_infop->L.print();
		printf("\n\n");
	}
}



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
	/*<< tfont.lfItalic << " "
		<< tfont.lfUnderline << " " << tfont.lfStrikeOut << " "
		<< tfont.lfCharSet << " " << tfont.lfOutPrecision << " "
		<< tfont.lfClipPrecision << " " << tfont.lfQuality << " "
		<< tfont.lfPitchAndFamily << endl;
	//cout << tfont.lfFaceName << endl;
	*/
	printf("%u %u %u %u %u %u %u\n", tfont.lfItalic, tfont.lfUnderline,
		tfont.lfStrikeOut, tfont.lfCharSet, tfont.lfOrientation,
		tfont.lfClipPrecision, tfont.lfQuality, tfont.lfPitchAndFamily);
	printf("%ls\n", tfont.lfFaceName);
	//wprintf(L"%s\n", tfont.lfFaceName);
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
	/*>> tfont.lfItalic
		>> tfont.lfUnderline >> tfont.lfStrikeOut
		>> tfont.lfCharSet >> tfont.lfOutPrecision
		>> tfont.lfClipPrecision >> tfont.lfQuality
		>> tfont.lfPitchAndFamily;
	//std::cin >> tfont.lfFaceName;
	*/
	scanf("%u %u %u %u %u %u %u", &tfont.lfItalic, &tfont.lfUnderline,
		&tfont.lfStrikeOut, &tfont.lfCharSet, &tfont.lfOrientation,
		&tfont.lfClipPrecision, &tfont.lfQuality, &tfont.lfPitchAndFamily);
	
	//scanf("%ls", tfont.lfFaceName);
	//gets(tfont.lfFaceName);
	//std::wcin >> tfont.lfFaceName;
	//wscanf(L"%[^\n]", tfont.lfFaceName);
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