#ifndef kernal_h
#define kernal_h

#include "stdafx.h"
#include<string>
#include<vector>

using namespace std;

class SICHAR_INFO;
class SIDRAW_INFO;
class SICHARNODE;
class SITEXT;
struct SIRECT;
struct SIPOINT;
struct SIRANGE;



typedef char SICHAR_T;
typedef LOGFONT SIFONT;
typedef SIFONT* SIFONT_P;
typedef int COLORERF;
typedef int CHARSIZE;
typedef int CHARSPACE;
typedef int LINESPACE;
typedef int SIALIGN;
typedef SICHAR_INFO* SICHAR_INFO_P;
typedef SIDRAW_INFO* SIDRAW_INFO_P;
typedef SICHARNODE* SICHARNODE_P;
typedef SIRANGE SISELECT;
typedef SIRANGE SIPARAGRAPH;
typedef SIRANGE SILINE;
typedef int PAGEWIDTH;
typedef SICHARNODE_P SICURSORP;
typedef int SIDIRECT;
typedef int SIALIGN;

template<class T>
void exchange(T& a, T& b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

inline bool isenter(SICHAR_T ch)
{
	return ch == '\n' || ch == '\r';
}

inline int Max(int a, int b)
{
	return a > b ? a : b;
}
inline COLORERF anticolor_ext(COLORERF c)
{
	return (~c)&((1 << 24) - 1);
}
inline int ABS(int a)
{
	return a < 0 ? (-a) : a;
}


class SICHAR_INFO
{
public:
	SIFONT_P fontpc;
	COLORERF color;
	COLORERF bgcolor;
	CHARSIZE size;
	CHARSPACE cspace;
	LINESPACE lspace;
	SIALIGN align;

	friend class SICHARNODE;
	SICHAR_INFO() :fontpc(NULL)
	{
		//fontp = NULL;
		color = 0x000000;
		bgcolor = 0xffffff;
		size = cspace = lspace = 0;
		align = 0;
		fontpc = new SIFONT;
	};
	SICHAR_INFO(const SICHAR_INFO& tinfo)
	{

		*fontpc = *(tinfo.fontpc);
		color = tinfo.color;
		bgcolor = tinfo.bgcolor;
		cspace = tinfo.cspace;
		lspace = tinfo.lspace;
		align = tinfo.align;
	}
	~SICHAR_INFO()
	{
		delete fontpc;
	}
	void set_fontpc(SIFONT_P tfontpc);
	void set_fontpc(SIFONT& tfont);
	void set_color(COLORERF tcolor);
	void set_size(CHARSIZE tsize);
	void set_cspace(CHARSPACE tcspace);
	void set_lspace(LINESPACE tlspace);
	///<interface>
	SIFONT_P get_fontpc();
	COLORERF get_color();
	CHARSIZE get_size();
	///<interface>
	CHARSPACE get_cspace();
	LINESPACE get_lspace();
	void print_info();
	void read_info();
	SICHAR_INFO& operator = (const SICHAR_INFO& tinfo);
};

struct SIRECT
{
	int width;
	int height;

	SIRECT(int twidth = 20, int theight = 20)
	{
		width = twidth;
		height = theight;
	}

	SIRECT(const SIRECT& trect)
	{
		width = trect.width;
		height = trect.height;
	}
	void print_info();
	void read_info();
};

struct SIPOINT
{
	int x;
	int y;
	SIPOINT(int tx = 0, int ty = 0)
	{
		x = tx; y = ty;
	}
	void print_info();
	void read_info();
	friend SIPOINT operator + (const SIPOINT& A, const SIPOINT& B)
	{
		return SIPOINT(A.x + B.x, A.y + B.y);
	}
	friend SIPOINT operator - (const SIPOINT& A, const SIPOINT& B)
	{
		return SIPOINT(A.x - B.x, A.y - B.y);
	}
	friend bool operator < (const SIPOINT& A, const SIPOINT& B)
	{
		return	A.y < B.y ||
			A.y == B.y && (A.x < B.x);
	}
	friend bool operator > (const SIPOINT& A, const SIPOINT& B)
	{
		return B < A;
	}
};

class SIDRAW_INFO
{
private:

public:
	SIRECT S;		//small rectangle
	SIRECT L;		//large rectangle
	SIPOINT POS;	//coor. (left_top)

	friend class SICHARNODE;
	SIDRAW_INFO();
	SIDRAW_INFO(const SIRECT& TS, const SIRECT& TL, const SIPOINT& TPOS);
	void set_S(const SIRECT&);
	void set_S(int, int);
	void set_L(const SIRECT&);
	void set_POS(const SIPOINT&);
	///<interface>
	const SIRECT& get_S();
	SIRECT& get_L();
	SIPOINT& get_POS();
	///<interface>
	void print_info();
	void read_info();

};

class SICHARNODE
{
private:

public:
	SICHAR_T ch;
	SICHAR_INFO_P char_infop;
	SIDRAW_INFO_P draw_infop;
	SICHARNODE *prevp;
	SICHARNODE *nextp;

	friend class SITEXT;
	SICHARNODE(SICHAR_T tch, SICHARNODE* tprevp = NULL, SICHARNODE* tnextp = NULL
		, SICHAR_INFO_P tchar_infop = NULL, SIDRAW_INFO_P tdraw_infop = NULL)
	{
		ch = tch;
		char_infop = new SICHAR_INFO;
		draw_infop = new SIDRAW_INFO;
		if (tchar_infop != NULL) *char_infop = *tchar_infop;
		if (tdraw_infop != NULL) *draw_infop = *tdraw_infop;
		prevp = tprevp;
		nextp = tnextp;
	}

	SICHARNODE(SICHAR_T tch, int tswidth, int tsheight)
	{
		ch = tch;
		char_infop = new SICHAR_INFO;
		draw_infop = new SIDRAW_INFO;
		draw_infop->S.width = tswidth;
		draw_infop->S.height = tsheight;
	}

	~SICHARNODE()
	{
		if (char_infop != NULL) delete char_infop;
		if (draw_infop != NULL) delete draw_infop;
	}

	void calc_S_from_font();
	void set_fontpc(SIFONT_P tfontpc);
	void set_fontpc(SIFONT& tfont);
	void set_color(COLORERF tcolor);
	void set_size(CHARSIZE tsize);
	void set_draw_infop_S(const SIRECT& TS);
	void set_draw_infop_L(const SIRECT& TL);
	void set_draw_infop_P(const SIPOINT& TP);
	void set_align(SIALIGN align);
	void ins_prev(SICHARNODE* p);
	void ins_next(SICHARNODE* p);
	void ins_prev(SICHARNODE* ps, SICHARNODE* pe);
	void ins_next(SICHARNODE* ps, SICHARNODE* pe);
	void ins_prev(const SIRANGE& range);
	void ins_next(const SIRANGE& range);
	friend void del(SICHARNODE* p);
	friend void del(SICHARNODE* ps, SICHARNODE* pe);
	friend void del(const SIRANGE& range);
	///<interface>
	const SICHAR_INFO_P get_char_infop();
	const SIDRAW_INFO_P get_draw_infop();
	///<\interface>
	void print_info();
	void read_info();

};

struct SIRANGE
{
	SICHARNODE_P sp;
	SICHARNODE_P ep;
	SIRANGE(SICHARNODE_P tsp = NULL, SICHARNODE_P tep = NULL)
	{
		sp = tsp;
		ep = tep;
	}
	void _clear()
	{
		sp = ep = NULL;
	}
};
class SITEXT
{
public:

	string save_path;
	string open_path;

	SICHARNODE_P headp;
	SICHARNODE_P tailp;

	SICURSORP cursorp;
	SISELECT select;

	PAGEWIDTH pagewidth;

	SIFONT_P curfontpc;
	SIFONT default_font;

	bool inselect;
	int fwdnum;
	std::vector<SILINE> vlinep;
	std::vector<SIPARAGRAPH> vparap;

	//set true when text changed specifically when \
				effectable methods are called		\
	  set false when repaint() is called
	bool text_changed_f;
	//set true when set_curfontp() is called \
			  set false when cursor moved
	bool set_curfontp_f;

private:

	void draw_line_from_left(SICHARNODE_P ps, SICHARNODE_P pe, int sx, int y, int line_height, int deltax);
	void proc_line(SICHARNODE_P ps, SICHARNODE_P pe, int n, int y, int line_height, int tot_weight, SIALIGN align);
	void proc_text();
	void pre_proc();
	inline std::vector<SILINE>::iterator point_to_line(const SIPOINT& P);
	inline void set_line_align(const SILINE& line, SIALIGN align);

public:

	static const PAGEWIDTH DEFAULT_PAGEWIDTH = 110;

	static const SIDIRECT DLEFT = 0;
	static const SIDIRECT DRIGHT = 1;
	static const SIDIRECT DUP = 2;
	static const SIDIRECT DDOWN = 3;

	static const SIALIGN ANORMAL = 0;
	static const SIALIGN ALEFT = 1;
	static const SIALIGN ARIGHT = 2;
	static const SIALIGN ACENTER = 3;
	static const SIALIGN ADISTRIBUTED = 4;
	//constructor
	SITEXT()
	{
		_init();
	}
	~SITEXT()
	{
		_destroy();
	}
	
	void save();
	void open();
	void ins_char(SICHAR_T);
	void ins_char(SICHAR_T, int, int);
	void del_char(bool backwards);
	void start_select();
	void end_select();
	void del_select();
	void replace_select(const SIRANGE&);
	void replace_select(SICHARNODE_P ps, SICHARNODE_P pe);
	void cancel_select();
	void mov_select(SICURSORP);
	void mov_cursorp(SICURSORP);
	void mov_cursorp(SIDIRECT);
	void mov_cursorp(const SIPOINT&);
	
	void set_default_font(SIFONT& tfont);
	void set_default_font(SIFONT_P tfontp);
	void set_select_font(SIFONT_P tfontpc);
	void set_select_font(SIFONT& tfont);
	void set_curfont(SIFONT_P tcurfontpc);
	void set_curfont(SIFONT& tcurfont);
	void set_select_color(COLORERF tcolor);
	void set_select_lspace(LINESPACE tlspace);
	void set_select_cspace(CHARSPACE tcspace);
	void set_pagewidth(PAGEWIDTH tpagewidth);
	void set_select_align(SIALIGN align);
	void set_cursorp_align(SIALIGN align);
	SIALIGN get_range_align(SICHARNODE_P ps,SICHARNODE_P pe);
	SIALIGN get_range_align(const SIRANGE& range);

	void set_save_path(string tsave_path);
	void set_open_path(string topen_path);
	SICURSORP point_to_cursorp(const SIPOINT& P);
	void repaint();
	void print_info();
	void read_info();
	void _init();
	void _destroy();
	void anticolor(SICHARNODE_P ps, SICHARNODE_P pe);
};


inline void SICHAR_INFO::set_fontpc(SIFONT_P tfontp)
{
	if (fontpc == NULL) fontpc = new SIFONT;
	*fontpc = *tfontp;
}
inline void SICHAR_INFO::set_fontpc(SIFONT& tfont)
{
	if (fontpc == NULL) fontpc = new SIFONT;
	*fontpc = tfont;
}
inline void SICHAR_INFO::set_color(COLORERF tcolor)
{
	color = tcolor;
}
inline void SICHAR_INFO::set_size(CHARSIZE tsize)
{
	size = tsize;
}
inline void SICHAR_INFO::set_cspace(CHARSPACE tcspace)
{
	cspace = tcspace;
}
inline void SICHAR_INFO::set_lspace(LINESPACE tlspace)
{
	lspace = tlspace;
}
inline SIFONT_P SICHAR_INFO::get_fontpc()
{
	return fontpc;
}
inline COLORERF SICHAR_INFO::get_color()
{
	return color;
}
inline CHARSIZE SICHAR_INFO::get_size()
{
	return size;
}
inline CHARSPACE SICHAR_INFO::get_cspace()
{
	return cspace;
}
inline LINESPACE SICHAR_INFO::get_lspace()
{
	return lspace;
}


inline void SIDRAW_INFO::set_S(const SIRECT& TS)
{
	S = TS;
}
inline void SIDRAW_INFO::set_S(int twidth, int theight)
{
	S.width = twidth;
	S.height = theight;
}
inline void SIDRAW_INFO::set_L(const SIRECT& TL)
{
	S = TL;
}
inline void SIDRAW_INFO::set_POS(const SIPOINT& TPOS)
{
	POS = TPOS;
}
inline const SIRECT& SIDRAW_INFO::get_S()
{
	return S;
}
inline SIRECT& SIDRAW_INFO::get_L()
{
	return L;
}
inline SIPOINT& SIDRAW_INFO::get_POS()
{
	return POS;
}
//SICHARNODE


inline void SICHARNODE::set_fontpc(SIFONT_P tfontp)
{
	char_infop->set_fontpc(tfontp);
//	int wd = ABS();
//	int ht = ;
	draw_infop->set_S(char_infop->fontpc->lfWidth, char_infop->fontpc->lfHeight);
}

inline void SICHARNODE::set_color(COLORERF tcolor)
{
	char_infop->set_color(tcolor);
}
inline void SICHARNODE::set_size(CHARSIZE tsize)
{
	char_infop->set_size(tsize);
}

inline void SICHARNODE::set_draw_infop_S(const SIRECT& TS)
{
	draw_infop->set_S(TS);
}
inline void SICHARNODE::set_draw_infop_L(const SIRECT& TL)
{
	draw_infop->set_L(TL);
}
inline void SICHARNODE::set_draw_infop_P(const SIPOINT& TP)
{
	draw_infop->set_POS(TP);
}
inline void SICHARNODE::set_align(SIALIGN align)
{
	char_infop->align = align;
}

inline void SICHARNODE::ins_prev(const SIRANGE& range)
{
	ins_prev(range.sp, range.ep);
}
inline void SICHARNODE::ins_next(const SIRANGE& range)
{
	ins_next(range.sp, range.ep);
}

inline const SICHAR_INFO_P SICHARNODE::get_char_infop()
{
	return char_infop;
}
inline const SIDRAW_INFO_P SICHARNODE::get_draw_infop()
{
	return draw_infop;
}



///<\private>
//constructor

/*
///<interface>
//Operate method
///inline void load();
///inline void save();
inline void SITEXT::_init();
*/


inline void SITEXT::set_save_path(string tsave_path)
{
	save_path = tsave_path;
}
inline void SITEXT::set_open_path(string topen_path)
{
	open_path = topen_path;
}
inline void SITEXT::ins_char(SICHAR_T tchar)
{
	cursorp->ins_prev(new SICHARNODE(tchar));
}

inline void SITEXT::ins_char(SICHAR_T ch, int twidth, int theight)
{
	ins_char(ch);
	cursorp->prevp->draw_infop->S.width = twidth;
	cursorp->prevp->draw_infop->S.height = theight;
}



inline void SITEXT::start_select()
{
	select.sp = cursorp;
	inselect = true;
	fwdnum = 0;
}

inline void SITEXT::cancel_select()
{
	anticolor(select.sp, select.ep);
	select._clear();
}


inline void SITEXT::replace_select(SICHARNODE_P ps, SICHARNODE_P pe)
{
	SICHARNODE_P p = select.ep->nextp;
	del(select);
	p->ins_prev(ps, pe);
}

inline void SITEXT::replace_select(const SIRANGE& range)
{
	replace_select(range.sp, range.ep);
}

/*
inline void SITEXT::replace_select()
*/

inline void SITEXT::mov_select(SICURSORP tcursorp)
{
	select.sp->prevp->nextp = select.ep->nextp;
	select.ep->nextp->prevp = select.sp->prevp;
	tcursorp->ins_prev(select.sp, select.ep);
}


inline void SITEXT::mov_cursorp(SICURSORP tcursorp)
{
	cursorp = tcursorp;
}
inline void SITEXT::mov_cursorp(const SIPOINT& P)
{
	cursorp = point_to_cursorp(P);
}

///several set_* method
inline void SITEXT::set_default_font(SIFONT& tfont)
{
	default_font = tfont;
	headp->set_fontpc(tfont);
	tailp->set_fontpc(tfont);
}
inline void SITEXT::set_default_font(SIFONT_P tfontp)
{
	headp->set_fontpc(tfontp);
	tailp->set_fontpc(tfontp);
}
inline void SITEXT::set_select_font(SIFONT_P tfontpc)
{
	if (select.ep == NULL) return;
	for (SICHARNODE_P p = select.sp; p != select.ep; p = p->nextp)
		p->set_fontpc(tfontpc);
}
inline void SITEXT::set_select_font(SIFONT& tfont)
{
	if (select.ep == NULL) return;
	for (SICHARNODE_P p = select.sp; p != select.ep; p = p->nextp)
		p->set_fontpc(tfont);
}
inline void SITEXT::set_curfont(SIFONT_P tcurfontpc)
{
	curfontpc = tcurfontpc;
}
inline void SITEXT::set_curfont(SIFONT& tcurfont)
{
	curfontpc = &tcurfont;
}
inline void SITEXT::set_select_color(COLORERF tcolor)
{
	if (select.ep == NULL) return;
	for (SICHARNODE_P p = select.sp; p != select.ep; p = p->nextp)
		p->set_color(anticolor_ext(tcolor));
}
inline void SITEXT::set_select_lspace(LINESPACE tlspace)
{
	for (SICHARNODE_P p = select.sp; p != select.ep; p = p->nextp)
		p->char_infop->lspace = tlspace;
}
inline void SITEXT::set_select_cspace(CHARSPACE tcspace)
{
	for (SICHARNODE_P p = select.sp; p != select.ep; p = p->nextp)
		p->char_infop->cspace = tcspace;
}
inline void SITEXT::set_pagewidth(PAGEWIDTH tpagewidth)
{
	pagewidth = tpagewidth;
}

inline void SITEXT::set_line_align(const SILINE& line, SIALIGN align)
{
	for (SICHARNODE_P p = line.sp; p != line.ep; p = p->nextp)
		p->set_align(align);
}


inline void SITEXT::set_cursorp_align(SIALIGN align)
{
	std::vector<SILINE>::iterator it = point_to_line(cursorp->draw_infop->POS);
	set_line_align(*it, align);
	return;
}



inline SIALIGN SITEXT::get_range_align(const SIRANGE& range)
{
	return get_range_align(range.sp, range.ep);
}
///several get_* method
inline bool point_on_line(SILINE L, const SIPOINT& P)
{
	return L.sp->draw_infop->POS.y <= P.y &&
		P.y < L.sp->draw_infop->POS.y + L.sp->draw_infop->L.height;
}
inline bool point_on_char_col(SICHARNODE_P np, const SIPOINT& P)
{
	return np->draw_infop->POS.x <= P.x&&
		P.x < np->draw_infop->POS.x + np->draw_infop->L.width;
}


inline std::vector<SILINE>::iterator SITEXT::point_to_line(const SIPOINT& P)
{
	std::vector<SILINE>::iterator it;
	for (it = vlinep.begin(); it != vlinep.end(); ++it)
		if (point_on_line(*it, P)) break;
	return it;

}

inline void SITEXT::repaint()
{
	pre_proc();
	proc_text();
}

inline void SITEXT::anticolor(SICHARNODE_P ps, SICHARNODE_P pe)
{
	if (ps == NULL || pe == NULL) return;
	for (SICHARNODE_P p = ps; p != pe; p = p->nextp)
	{
		p->char_infop->bgcolor = anticolor_ext(p->char_infop->bgcolor);//(~(p->char_infop->bgcolor))&((1 << 24) - 1);
		p->char_infop->color = anticolor_ext(p->char_infop->color);//(~(p->char_infop->color))&((1 << 24) - 1);
	}
}
inline void SITEXT::save()
{
	freopen(save_path.c_str(), "w", stdout);
	print_info();
	fclose(stdout);
}

inline void SITEXT::open()
{
	freopen(open_path.c_str(), "r", stdin);
	read_info();
	fclose(stdin);
}
#endif