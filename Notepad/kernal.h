
#ifndef kernal_h
#define kernal_h

#include<vector>
#include<Windows.h>

using namespace std;

typedef wchar_t SICHAR_T;
typedef LOGFONT SIFONT;
typedef SIFONT* SIFONT_P;
typedef const SIFONT* SIFONT_PC;
typedef int COLORERF;
typedef int CHARSIZE;
typedef int CHARSPACE;
typedef int LINESPACE;

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
	SIFONT_PC fontpc;
	COLORERF color;
	CHARSIZE size;
	CHARSPACE cspace;
	LINESPACE lspace;
public:
	friend class SICHARNODE;
	SICHAR_INFO():fontpc(NULL)
	{
		//fontp = NULL;
		color = size = cspace = lspace = 0;
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
};

struct SIPOINT
{
	int x;
	int y;
	SIPOINT(int tx = 0, int ty = 0)
	{
		x = tx; y = ty;
	}
};

class SIDRAW_INFO
{
private:
	SIRECT S;		//small rectangle
	SIRECT L;		//large rectangle
	SIPOINT POS;	//coor. (left_top)
public:
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
	SICHAR_T ch;
	SICHAR_INFO_P char_infop;
	SIDRAW_INFO_P draw_infop;
	SICHARNODE *prevp;
	SICHARNODE *nextp;
public:
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
	inline void ins_forward(SICHARNODE* p);
	inline void ins_backward(SICHARNODE* p);
	inline void ins_forward(SICHARNODE* ps, SICHARNODE* pe);
	inline void ins_backward(SICHARNODE* ps, SICHARNODE* pe);
	inline void ins_forward(const SIRANGE& range);
	inline void ins_backward(const SIRANGE& range);
	friend void del(SICHARNODE* p);
	friend void del(SICHARNODE* ps, SICHARNODE* pe);
	friend void del(const SIRANGE& range);
///<interface>
	inline const SICHAR_INFO_P get_char_infop();
	inline const SIDRAW_INFO_P get_draw_infop();
	//change
	inline SICHARNODE* get_prevp();
	inline SICHARNODE* get_nextp();
	inline const SICHAR_T get_char();
	//change end
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
};
typedef SIRANGE SISELECT;
typedef SIRANGE SIPARAGRAPH;
typedef SIRANGE SILINE;

typedef int PAGEWIDTH;
typedef SICHARNODE_P SICURSORP;
typedef int SIDIRECT;
class SITEXT
{
public://used to be private
	SICHARNODE_P headp;
	SICHARNODE_P tailp;

	SICURSORP cursorp;
	SISELECT select;

	PAGEWIDTH pagewidth;

	SIFONT_PC curfontp;

	std::vector<SILINE> vlinep;
	std::vector<SIPARAGRAPH> vparap;

	//set true when text changed specifically when \
		effectable methods are called		\
	  set false when repaint() is called
	//bool text_changed_f;
	//set true when set_curfontp() is called \
	  set false when cursor moved
	bool set_curfontp_f;

private:
	inline void proc_line(SICHARNODE_P ps, SICHARNODE_P pe);
	inline void proc_text();
public:
	//change_begin
	bool text_changed_f;
	//change_end
	static const SIDIRECT LEFT;
	static const SIDIRECT RRIHT;
	static const SIDIRECT UP;
	static const SIDIRECT DOWN;
	//constructor
	SITEXT();
///<interface>
	//Operate method
	///inline void load();
	///inline void save();
	inline void _init();
	inline void ins_char(SICHAR_T);
	inline void del_char(bool backwards = false);
	inline void start_select();
	inline void end_select();
	inline void del_select();
	inline void replace_select();
	inline void clear_select();
	inline void mov_select(SICURSORP);
	inline void mov_cursorp(SICURSORP);
	inline void mov_cursorp(SIDIRECT);
	///several set_* method
	inline void set_select_font(SIFONT_PC tfontp);
	inline void set_select_font(const SIFONT& tfont);
	inline void set_curfont(SIFONT_PC tcurfontp);
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
///<\interface>
};

#endif