#ifndef kernal_h
#define kernal_h

/**
@brief 记事本的内核\n
@file kernal.h
@author 李仁杰
@email ShadowIterator@hotmail.com
@version 1.0
@date 2015.5.28
*/

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


typedef int SIDIRECT;
typedef int SIALIGN;
typedef int PAGEWIDTH;
typedef int COLORERF;
typedef int CHARSIZE;
typedef int CHARSPACE;
typedef int LINESPACE;
typedef int SIALIGN;
typedef char SICHAR_T;
typedef LOGFONT SIFONT;
typedef SIFONT* SIFONT_P;
typedef SIPOINT SIVECTOR;
typedef SICHAR_INFO* SICHAR_INFO_P;
typedef SIDRAW_INFO* SIDRAW_INFO_P;
typedef SICHARNODE* SICHARNODE_P;
typedef SIRANGE SISELECT;
typedef SIRANGE SIPARAGRAPH;
typedef SIRANGE SILINE;
typedef SICHARNODE_P SICURSORP;


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

/**
@brief 反色函数\n
@param[in] c 当前颜色
@retval 反色后的颜色
*/
inline COLORERF anticolor_ext(COLORERF c)
{
	return (~c)&((1 << 24) - 1);
}

inline int ABS(int a)
{
	return a < 0 ? (-a) : a;
}
/**
@brief 矩形结构体\n
用于表示一个字符占据的屏幕空间大小
*/
struct SIRECT
{
	int width;	///<宽度(px)
	int height;	///<高度(px)

	SIRECT(int twidth = 20, int theight = 20) ///<构造函数1(默认)
	{
		width = twidth;
		height = theight;
	}

	SIRECT(const SIRECT& trect)	///<构造函数2
	{
		width = trect.width;
		height = trect.height;
	}
	void print_info();	///<输出信息
	void read_info();	///<读入信息
};
/**
@brief 点/向量结构体\n
用于表示一个字符(的左上角)在屏幕上的位置
*/
struct SIPOINT
{
	int x;	///<x坐标(px)
	int y;	///<y坐标(px)
	SIPOINT(int tx = 0, int ty = 0)	///<构造函数
	{
		x = tx; y = ty;
	}
	friend SIPOINT operator + (const SIPOINT& A, const SIPOINT& B)	///<向量加法
	{
		return SIPOINT(A.x + B.x, A.y + B.y);
	}
	friend SIPOINT operator - (const SIPOINT& A, const SIPOINT& B)	///<向量减法
	{
		return SIPOINT(A.x - B.x, A.y - B.y);
	}
	/**
	@brief 定义两个点的小于关系
	@param[in] A 左操作数
	@param[in] B 右操作数
	@retval true A的x坐标更小 或 AB的x坐标相等且A的y坐标更小
	@retval false B的x坐标更小 或 AB的x坐标相等且B的y坐标更小
	*/
	friend bool operator < (const SIPOINT& A, const SIPOINT& B)
	{
		return	A.y < B.y ||
			A.y == B.y && (A.x < B.x);
	}
	friend bool operator > (const SIPOINT& A, const SIPOINT& B)	///<定义两个点的大于关系，与小于关系相反 @see operator <
	{
		return B < A;
	}
	void print_info();	///<输出信息
	void read_info();	///<读入信息
};

/**
@brief 表示文本链表中的一段节点
*/
struct SIRANGE
{
	SICHARNODE_P sp;	///<指向这段节点的头指针 @see SICHARNODE_P
	SICHARNODE_P ep;	///<指向这段节点的尾指针 @see SICHARNODE_P
	SIRANGE(SICHARNODE_P tsp = NULL, SICHARNODE_P tep = NULL)	///<构造函数(默认)
	{
		sp = tsp;
		ep = tep;
	}
	/**
	@brief 清空函数\n
	@note 这个函数只是把sp和ep的值赋为NULL，并不会清空链表中的节点
	*/
	void _clear()
	{
		sp = ep = NULL;
	}
};

/**
@brief 表示一个字符的与绘制相关的信息\n
把每个字符抽象成一个屏幕上的矩形，每两个矩形之间没有缝隙
*/
class SIDRAW_INFO
{
public:
	/**
	@brief 一个字符初始矩形的形状\n
	影响它的属性是\n
		-字体
		-字号
	@see struct SIRECT
	*/
	SIRECT S;		//small rectangle	
	/**
	@brief 一个字符画在屏幕上的形状\n
	影响它的属性是\n
		-字体
		-字号
		-字间距
		-行间距
		-该字符当前所在行高度最高的字符的高度
	@see struct SIRECT
	*/
	SIRECT L;		//large rectangle	
	SIPOINT POS;	//coor. (left_top)	///<表示一个字符的左上角在屏幕上的位置 @see struct SIPOINT

	friend class SICHARNODE;
	SIDRAW_INFO()	///<构造函数1(默认)
	{
		S = SIRECT(); L = SIRECT(); POS = SIPOINT();
	}
	SIDRAW_INFO::SIDRAW_INFO(const SIRECT& TS, const SIRECT& TL, const SIPOINT& TPOS)	///<构造函数2
	{
		S = TS; L = TL; POS = TPOS;
	}	
	void set_S(const SIRECT&);	///<设置S的值(重载:1)
	void set_S(int, int);	///<设置S的值(重载:2)
	void set_L(const SIRECT&);	///<设置L的值
	void set_POS(const SIPOINT&);	///<设置POS的值
	const SIRECT& get_S();	///<获得S的值
	SIRECT& get_L();	///<获得L的值
	SIPOINT& get_POS();	///<获得POS的值
	///<interface>
	void print_info();	///<输出信息
	void read_info();	///<读入信息

};

/**
@brief 表示一个字符的可以"设置"的信息
*/
class SICHAR_INFO
{
public:
	SIFONT_P fontpc;	///<字体信息,详见MSDN @see SIFONT_P
	COLORERF color;	///<颜色信息 @COLORERF
	COLORERF bgcolor;	///<背景颜色信息 @COLORERF
	CHARSIZE size;	///<字体大小，这里用作标识符 @CHARSIZE
	CHARSPACE cspace;	///<字间距 @CHARSPACE
	LINESPACE lspace;	///<行间距 @LINESPACE
	SIALIGN align;	///<对齐方式 @SIALIGN

	friend class SICHARNODE;
	SICHAR_INFO() :fontpc(NULL)	///<构造函数1(默认)
	{
		//fontp = NULL;
		color = 0x000000;
		bgcolor = 0xffffff;
		size = cspace = lspace = 0;
		align = 0;
		fontpc = new SIFONT;
	};
	SICHAR_INFO(const SICHAR_INFO& tinfo)	///<构造函数2
	{

		*fontpc = *(tinfo.fontpc);
		color = tinfo.color;
		bgcolor = tinfo.bgcolor;
		cspace = tinfo.cspace;
		lspace = tinfo.lspace;
		align = tinfo.align;
	}
	~SICHAR_INFO()	///<析构函数
	{
		delete fontpc;
	}
	void set_fontpc(SIFONT_P tfontpc);	///<设置fontpc成员(重载:1) @see fontpc
	void set_fontpc(SIFONT& tfont);	///<设置fontpc成员(重载:2) @see fontpc
	void set_color(COLORERF tcolor);	///<设置color成员 @see color
	void set_size(CHARSIZE tsize);	///<设置size成员 @see size
	void set_cspace(CHARSPACE tcspace);	///<设置cspace成员 @see cspace
	void set_lspace(LINESPACE tlspace);	///<设置lspace成员 @see lspace
	///<interface>
	/**
	@brief 得到字体信息\n
	@retval 一个指向SIFONT的指针，表示字体信息
	*/
	SIFONT_P get_fontpc();	
	/**
	@brief 得到颜色信息\n
	@retval 一个COLORREF类型的变量，表示颜色
	*/
	COLORERF get_color();	
	/**
	@brief 得到字体大小\n
	@retval 一个CHARSIZE类型的变量，表示字体大小
	*/
	CHARSIZE get_size();
	///<interface>
	/**
	@brief 得到字间距\n
	@retval 一个CHARSPACE类型的变量，表示字间距
	*/
	CHARSPACE get_cspace();
	/**
	@brief 得到行间距\n
	@retval 一个LINESPACE类型的变量，表示行间距
	*/
	LINESPACE get_lspace();
	void print_info();	///<输出信息
	void read_info();	///<读入信息
	/**
	@brief 重载赋值函数\n
	@note 这个函数中，fontpc是复制指针指向的内容而不是指针本身
	@param[in] *this 左操作数
	@param[in] tinfo 右操作数
	@retval *this 
	*/
	SICHAR_INFO& operator = (const SICHAR_INFO& tinfo);	
};


/**
@brief 表示文本链表的一个节点\n
*/
class SICHARNODE
{
public:
	SICHAR_T ch;	///<字符 @see SICHAR_T
	/**
	@brief 字体信息\n
	一个指向SICHAR_INFO类型的指针，储存该字符的字体信息 
	@see class SICHAR_INFO
	*/
	SICHAR_INFO_P char_infop; 
	/**
	@brief 绘制信息\n
	一个指向SIDRAW_INFO类型的指针，储存该字符的绘制信息
	@see class SIDRAW_INFO
	*/
	SIDRAW_INFO_P draw_infop;
	SICHARNODE *prevp;	///<指向链表前一个节点的指针
	SICHARNODE *nextp;	///<指向链表后一个节点的指针

	friend class SITEXT;
	SICHARNODE(SICHAR_T tch, SICHARNODE* tprevp = NULL, SICHARNODE* tnextp = NULL
		, SICHAR_INFO_P tchar_infop = NULL, SIDRAW_INFO_P tdraw_infop = NULL)	///<构造函数1
	{
		ch = tch;
		char_infop = new SICHAR_INFO;
		draw_infop = new SIDRAW_INFO;
		if (tchar_infop != NULL) *char_infop = *tchar_infop;
		if (tdraw_infop != NULL) *draw_infop = *tdraw_infop;
		prevp = tprevp;
		nextp = tnextp;
	}

	SICHARNODE(SICHAR_T tch, int tswidth, int tsheight)	///<构造函数2
	{
		ch = tch;
		char_infop = new SICHAR_INFO;
		draw_infop = new SIDRAW_INFO;
		draw_infop->S.width = tswidth;
		draw_infop->S.height = tsheight;
	}
	~SICHARNODE()	///<析构函数
	{
		if (char_infop != NULL) delete char_infop;
		if (draw_infop != NULL) delete draw_infop;
	}
private:
	void calc_S_from_font();///<从当前的字体计算出绘制信息中的S的大小 @see S @see fontpc
public:
	void set_fontpc(SIFONT_P tfontpc);	///<设置char_infop中的fontpc并重新计算draw_infop中的S的大小
	void set_fontpc(SIFONT& tfont);
	void set_color(COLORERF tcolor);
	void set_size(CHARSIZE tsize);
	void set_draw_infop_S(const SIRECT& TS);
	void set_draw_infop_L(const SIRECT& TL);
	void set_draw_infop_P(const SIPOINT& TP);
	void set_align(SIALIGN align);
	/**
	@brief 在当前字符的前面插入一个节点\n
	@param[in] p 指向被插入节点的指针
	@note 该函数会把p指向的节点的字体信息改为和p的前一个节点相同
	*/
	void ins_prev(SICHARNODE* p);
	/**
	@brief 在当前字符的后面插入一个节点\n
	@param[in] p 指向被插入节点的指针
	@note 该函数会把p指向的节点的字体信息改为和p的前一个节点相同
	*/
	void ins_next(SICHARNODE* p);
	/**
	@brief 在当前字符的前面插入一段节点\n
	@param[in] ps 指向被插入节点段的头指针
	@param[in] pe 指向被插入节点段的尾指针
	@note 该函数不会改变被插入节点段的字体信息\n
	要求这段节点必须事先已经用链表的结构组织好了
	*/
	void ins_prev(SICHARNODE* ps, SICHARNODE* pe);
	/**
	@brief 在当前字符的后面插入一段节点\n
	@param[in] ps 指向被插入节点段的头指针
	@param[in] pe 指向被插入节点段的尾指针
	@note 该函数不会改变被插入节点段的字体信息\n
	要求这段节点必须事先已经用链表的结构组织好了
	*/
	void ins_next(SICHARNODE* ps, SICHARNODE* pe);
	void ins_prev(const SIRANGE& range);	///<@see ins_prev
	void ins_next(const SIRANGE& range);	///<@see ins_next
	/**
	@brief 从链表中删除一个节点\n
	@param[in] p 待删除的节点
	@note p不能是链表的头节点或尾节点
	*/
	friend void del(SICHARNODE* p);
	/**
	@brief 从链表中删除一段节点\n
	@param[in] ps 指向被删除节点段的头节点
	@param[in] pe 指向被删除节点段的尾节点
	@note 该节点段不能包含链表的头节点或尾节点
	*/
	friend void del(SICHARNODE* ps, SICHARNODE* pe);	///
	friend void del(const SIRANGE& range);	///<@see del
	///<interface>
	const SICHAR_INFO_P get_char_infop();	///<得到一个char_infop的const副本 @see char_infop
	const SIDRAW_INFO_P get_draw_infop();	///<得到一个draw_infop的const副本 @see draw_infop
	///<\interface>
	void print_info();	///<输出信息
	void read_info();	///<输入信息

};


/**
@brief 文本链表\n
把文本从头到尾抽象成一个链表
*/
class SITEXT
{
public:

	string save_path;	///<保存路径
	string open_path;	///<打开路径

	SICHARNODE_P headp;	///<文本链表头指针 @see SICHARNODE_P
	SICHARNODE_P tailp;	///<文本链表尾指针 @see SICHARNODE_P

	/**
	@brief 光标位置\n
	一个指向链表中一个节点的指针，用来表示光标目前所在的位置
	@note 该指针指向的节点代表屏幕上显示的光标的后一个字符
	@see SICURSORP
	*/
	SICURSORP cursorp;
	SISELECT select;	///<当前选中的区间 @see SISELECT

	PAGEWIDTH pagewidth;	///<页面宽度，用于计算字符的位置 @see PAGEWIDTH

	SIFONT_P curfontpc;	
	SIFONT default_font;	///<初始的默认字体 @see SIFONT

	bool inselect;	
	int fwdnum;
	std::vector<SILINE> vlinep;	///<按顺序储存屏幕上从上到下的每一行 @see SILINE
	std::vector<SIPARAGRAPH> vparap;	///<按顺序储存屏幕上从上到下每一段 @see SIPARAGRAPH

	//set true when text changed specifically when \
				effectable methods are called		\
	  set false when repaint() is called
	bool text_changed_f;	///<文本改变标志
	//set true when set_curfontp() is called \
			  set false when cursor moved
	bool set_curfontp_f;

private:

	void _init();	///<初始化方法
	void _destroy();	///<清除数据并释放内存
	/**
	@brief 行计算函数\n
	用于计算一行字符的绘制信息
	@param[in] ps 指向该行头节点的指针
	@param[in] pe 指向该行尾节点的指针
	@param[in] sx 该行左上角的x坐标
	@param[in] y  该行左上角的y坐标
	@param[in] line_height 行高
	@param[in] delta 每个字符除了自身的宽度外的附加宽度(只在分散对齐时不为0)
	*/
	void draw_line_from_left(SICHARNODE_P ps, SICHARNODE_P pe, int sx, int y, int line_height, int deltax);
	/**
	@brief 行处理函数\n
	根据不同对齐方式用于计算一行字符的绘制信息
	@param[in] ps 指向该行头节点的指针
	@param[in] pe 指向该行尾节点的指针
	@param[in] n  该行的字符总数(不包括换行符)
	@param[in] y  该行左上角的坐标
	@param[in] line_height 行高
	@param[in] tot_width 该行字符自身的宽度总和
	@param[in] align 该行的对齐方式
	@todo 补充对align的介绍
	*/
	void proc_line(SICHARNODE_P ps, SICHARNODE_P pe, int n, int y, int line_height, int tot_weight, SIALIGN align);
	/**
	@brief 预处理函数\n
	对文本做预处理(主要是添加分段符)
	*/
	void pre_proc();
	void proc_text();	///<文本处理函数
	inline std::vector<SILINE>::iterator point_to_line(const SIPOINT& P);	///<求包含屏幕上某一点的那一行
	inline void set_line_align(const SILINE& line, SIALIGN align);	///<设置某一行的对齐方式

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
	SITEXT()	///<构造函数 @see _init
	{
		_init();
	}
	~SITEXT()	///<析构函数 @see _destroy
	{
		_destroy();
	}
	
	void save();	///<保存文本
	void open();	///<打开文本
	void ins_char(SICHAR_T);	///<在光标前方插入一个字符
	void ins_char(SICHAR_T, int, int);	///<在光标前方插入一个字符，指定S的大小
	/**
	@brief 删除字符\n
	@param[in] backwards
	@todo 补充对backwards可能的取值的说明
	*/
	void del_char(bool backwards);
	void start_select();	///<进入选择状态
	void end_select();	///<结束选择状态
	void del_select();	///<删除被选中的字符
	void replace_select(const SIRANGE&);	///<替换被选中的字符(重载1)
	void replace_select(SICHARNODE_P ps, SICHARNODE_P pe);	///<替换被选中的字符(重载2)
	/**
	@brief 取消选中\n
	@note 该函数把选中区域赋为NULL，不会对文本做出更改
	*/
	void cancel_select();
	void mov_select(SICURSORP);	///<把选中字符移到光标区域
	/**
	@brief 移动光标(重载1)\n
	把光标移到参数指定的节点处
	@param[in] tcursorp 移动的目标节点
	*/
	void mov_cursorp(SICURSORP);	
	/**
	@brief 移动光标(重载2)\n
	把光标往上/下/左/右移动一格
	@param[in] tdir 移动方向
	*/
	void mov_cursorp(SIDIRECT);
	/**
	@移动光标(重载3)\n
	把光标移到屏幕上一点给定的位置
	@param[in] P 目标位置
	*/
	void mov_cursorp(const SIPOINT&);
	
	void set_default_font(SIFONT& tfont);	///<设置默认字体(重载1)
	void set_default_font(SIFONT_P tfontp);	///<设置默认字体(重载2)
	void set_select_font(SIFONT_P tfontpc);	///<设置选中区域的字体(重载1)
	void set_select_font(SIFONT& tfont);	///<设置选中区域的字体(重载2)
	void set_curfont(SIFONT_P tcurfontpc);	
	void set_curfont(SIFONT& tcurfont);
	void set_select_color(COLORERF tcolor);	///<设置选中区域的颜色
	void set_select_lspace(LINESPACE tlspace);	///<设置选中区域的行距
	void set_select_cspace(CHARSPACE tcspace);	///<设置选中区域的字间距
	void set_pagewidth(PAGEWIDTH tpagewidth);	///<设置页面宽度
	void set_select_align(SIALIGN align);	///<设置选中区域的对齐方式
	void set_cursorp_align(SIALIGN align);	///<设置光标所在行的对其方式
	/**
	@brief 得到一段节点的对齐方式(重载1)\n
	@param[in] 该节点段的头节点
	@param[in] 该节点段的尾节点
	@note 如果这段节点有多种非默认的对齐方式，选择最靠前的节点的对齐方式
	*/
	SIALIGN get_range_align(SICHARNODE_P ps,SICHARNODE_P pe);	
	SIALIGN get_range_align(const SIRANGE& range);	///<得到一段节点的对齐方式(重载2) @see get_range_align

	void set_save_path(string tsave_path);	///<设置保存路径
	void set_open_path(string topen_path);	///<设置打开路径
	SICURSORP point_to_cursorp(const SIPOINT& P);	///<把屏幕上的点转换为光标位置
	void repaint();	///<重新计算所有信息
	void print_info();	///<输出信息
	void read_info();	///<读入信息
	void anticolor(SICHARNODE_P ps, SICHARNODE_P pe);	///<把一段字符反色

	/**
	@brief 判断一个屏幕上的点是否在某一行内\n
	@param[in] L 被判断的行
	@param[in] P 被判断的点
	@retval true 该点在这一行内
	@retval false 该点不在这一行内
	*/
	friend bool point_on_line(SILINE L, const SIPOINT& P);
	/**
	@brief 判断一个屏幕上的点是否在某一个字符所处的列内\n
	@param[in] np 指向被判断字符的节点指针
	@param[in] P  被判断的点
	@retval true 该点在该字符所在的列内
	@retval false 该点不在该字符所在列内
	@note 该函数判断的只有列，不是判断点是否在字符上
	*/
	friend bool point_on_char_col(SICHARNODE_P np, const SIPOINT& P);
};

//SICHAR_INFO
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

//SIDRAW_INFO
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

//SITEXT
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

#endif