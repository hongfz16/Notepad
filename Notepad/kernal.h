
#ifndef kernal_h
#define kernal_h

#include "stdafx.h"
#include<vector>
//#include<Windows.h>

using namespace std;

//typedef wchar_t SICHAR_T;
typedef char SICHAR_T;
typedef LOGFONT SIFONT;
typedef SIFONT* SIFONT_P;
typedef const SIFONT* SIFONT_PC;
typedef int COLORERF;
typedef int CHARSIZE;
typedef int CHARSPACE;
typedef int LINESPACE;
typedef int SIALIGN;

class SICHAR_INFO;
class SIDRAW_INFO;
class SICHARNODE;
class SITEXT;
struct SIRECT;
struct SIPOINT;
struct SIRANGE;
//struct SITEXT;

class SICHAR_INFO
{
private:
	//const SIFONT_P fontp;

public:
	SIFONT_PC fontpc;
	COLORERF color;
	CHARSIZE size;
	CHARSPACE cspace;
	LINESPACE lspace;
	SIALIGN align;

	friend class SICHARNODE;
	SICHAR_INFO():fontpc(NULL)
	{
		//fontp = NULL;
		color = size = cspace = lspace = align = 0;
	}
	inline void set_fontpc(SIFONT_PC tfontpc);
	inline void set_fontpc(const SIFONT& tfont);
	inline void set_color(COLORERF tcolor);
	inline void set_size(CHARSIZE tsize);
	inline void set_cspace(CHARSPACE tcspace);
	inline void set_lspace(LINESPACE tlspace);
///<interface>
	inline SIFONT_PC get_fontpc();
	inline COLORERF get_color();
	inline CHARSIZE get_size();
///<interface>
	inline CHARSPACE get_cspace();
	inline LINESPACE get_lspace();
};
typedef SICHAR_INFO* SICHAR_INFO_P;

struct SIRECT
{
	int width;
	int height;
	SIRECT(int twidth = 0, int theight = 0)
	{
		width = twidth;
		height = theight;
	}
	void print()
	{
		printf("%d %d", width, height);
	}
};

struct SIPOINT
{
	int x;
	int y;
	SIPOINT(int tx = 0, int ty = 0)
	{
		x = tx; y = ty;
	}
	void print()
	{
		printf("%d %d", x, y);
	}
	friend SIPOINT operator + (const SIPOINT& A, const SIPOINT& B)
	{
		return SIPOINT(A.x + B.x, A.y + B.y);
	}
	friend SIPOINT operator - (const SIPOINT& A, const SIPOINT& B)
	{
		return SIPOINT(A.x - B.x, A.y - B.y);
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
	SIDRAW_INFO()
	{
		S = SIRECT(); L = SIRECT(); POS = SIPOINT();
	}
	SIDRAW_INFO(const SIRECT& TS, const SIRECT& TL,const SIPOINT& TPOS)
	{
		S = TS; L = TL; POS = TPOS;
	}
	inline void set_S(const SIRECT&);
	inline void set_L(const SIRECT&);
	inline void set_POS(const SIPOINT&);
///<interface>
	inline const SIRECT& get_S();
	inline const SIRECT& get_L();
	inline const SIPOINT& get_POS();
///<interface>
};
typedef SIDRAW_INFO* SIDRAW_INFO_P;

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

	~SICHARNODE()
	{
		if (char_infop != NULL) delete char_infop;
		if (draw_infop != NULL) delete draw_infop;
	}
	inline void set_fontpc(SIFONT_PC tfontpc);
	inline void set_fontpc(const SIFONT& tfont);
	inline void set_color(COLORERF tcolor);
	inline void set_size(CHARSIZE tsize);
	inline void set_char_infop(const SIFONT& tfont, COLORERF tcolor, CHARSIZE tsize);
	inline void set_char_infop(SIFONT_P tfontp, COLORERF tcolor, CHARSIZE tsize);
	inline void set_draw_infop_S(const SIRECT& TS);
	inline void set_draw_infop_L(const SIRECT& TL);
	inline void set_draw_infop_P(const SIPOINT& TP);
	inline void set_draw_infop_LP(const SIRECT& TL, const SIPOINT& TP);
	inline void set_draw_infop(const SIRECT& TS, const SIRECT& TL, const SIPOINT& TP);
	inline void ins_prev(SICHARNODE* p);
	inline void ins_next(SICHARNODE* p);
	inline void ins_prev(SICHARNODE* ps, SICHARNODE* pe);
	inline void ins_next(SICHARNODE* ps, SICHARNODE* pe);
	inline void ins_prev(const SIRANGE& range);
	inline void ins_next(const SIRANGE& range);
	friend void del(SICHARNODE* p);
	friend void del(SICHARNODE* ps, SICHARNODE* pe);
	friend void del(const SIRANGE& range);
///<interface>
	inline const SICHAR_INFO_P get_char_infop();
	inline const SIDRAW_INFO_P get_draw_infop();
///<\interface>
};
typedef SICHARNODE* SICHARNODE_P;

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
typedef SIRANGE SISELECT;
typedef SIRANGE SIPARAGRAPH;
typedef SIRANGE SILINE;

typedef int PAGEWIDTH;
typedef SICHARNODE_P SICURSORP;
typedef int SIDIRECT;
typedef int SIALIGN;
class SITEXT
{
private:
public:
	SICHARNODE_P headp;
	SICHARNODE_P tailp;

	SICURSORP cursorp;
	SISELECT select;

	PAGEWIDTH pagewidth;

	SIFONT_PC curfontpc;

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

	inline void draw_line_from_left(SICHARNODE_P ps, SICHARNODE_P pe, int sx, int y, int line_height, int deltax);
	inline void proc_line(SICHARNODE_P ps, SICHARNODE_P pe, int n, int y, int line_height, int tot_weight, int align);
	inline void proc_text();
public:
	
	static const PAGEWIDTH DEFAULT_PAGEWIDTH = 110;

	static const SIDIRECT DLEFT = 0;
	static const SIDIRECT DRIGHT = 1;
	static const SIDIRECT DUP = 2;
	static const SIDIRECT DDOWN = 3;

	static const SIALIGN ANORMAL = 0;
	static const SIALIGN ALEFT = 0;
	static const SIALIGN ARIGHT = 1;
	static const SIALIGN ACENTER = 2;
	static const SIALIGN ADISTRIBUTED = 3;
	//constructor
	SITEXT();
///<interface>
	//Operate method
	///inline void load();
	///inline void save();
	inline void _init();
	inline void ins_char(SICHAR_T);
	//debug mod?
	inline void ins_char(SICHAR_T, int, int);
	//------------
	inline void del_char(bool backwards);
	inline void start_select();
	inline void end_select();
	inline void del_select();
	inline void replace_select(const SIRANGE&);
	inline void replace_select(SICHARNODE_P ps, SICHARNODE_P pe);
	inline void cancel_select();
	inline void mov_select(SICURSORP);
	inline void mov_cursorp(SICURSORP);
	inline void mov_cursorp(SIDIRECT);
	inline void mov_cursorp(const SIPOINT&);
	///several set_* method
	inline void set_select_font(SIFONT_PC tfontpc);
	inline void set_select_font(const SIFONT& tfont);
	inline void set_curfont(SIFONT_PC tcurfontpc);
	inline void set_curfont(const SIFONT& tcurfont);
	inline void set_select_color(COLORERF tcolor);
	inline void set_select_lspace(LINESPACE tlspace);
	inline void set_select_cspace(CHARSPACE tcspace);
	inline void set_pagewidth(PAGEWIDTH tpagewidth);
	///several get_* method
	inline SICURSORP point_to_cursorp(const SIPOINT& P);
	//Draw method
		///cursor - coord transparent
		///divide line
		///line texing
	inline void repaint();
	void print_list();
///<\interface>
};

#endif