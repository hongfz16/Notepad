#ifndef kernal_h
#define kernal_h

/**
@brief ���±����ں�\n
@file kernal.h
@author ���ʽ�
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
@brief ��ɫ����\n
@param[in] c ��ǰ��ɫ
@retval ��ɫ�����ɫ
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
@brief ���νṹ��\n
���ڱ�ʾһ���ַ�ռ�ݵ���Ļ�ռ��С
*/
struct SIRECT
{
	int width;	///<���(px)
	int height;	///<�߶�(px)

	SIRECT(int twidth = 20, int theight = 20) ///<���캯��1(Ĭ��)
	{
		width = twidth;
		height = theight;
	}

	SIRECT(const SIRECT& trect)	///<���캯��2
	{
		width = trect.width;
		height = trect.height;
	}
	void print_info();	///<�����Ϣ
	void read_info();	///<������Ϣ
};
/**
@brief ��/�����ṹ��\n
���ڱ�ʾһ���ַ�(�����Ͻ�)����Ļ�ϵ�λ��
*/
struct SIPOINT
{
	int x;	///<x����(px)
	int y;	///<y����(px)
	SIPOINT(int tx = 0, int ty = 0)	///<���캯��
	{
		x = tx; y = ty;
	}
	friend SIPOINT operator + (const SIPOINT& A, const SIPOINT& B)	///<�����ӷ�
	{
		return SIPOINT(A.x + B.x, A.y + B.y);
	}
	friend SIPOINT operator - (const SIPOINT& A, const SIPOINT& B)	///<��������
	{
		return SIPOINT(A.x - B.x, A.y - B.y);
	}
	/**
	@brief �����������С�ڹ�ϵ
	@param[in] A �������
	@param[in] B �Ҳ�����
	@retval true A��x�����С �� AB��x���������A��y�����С
	@retval false B��x�����С �� AB��x���������B��y�����С
	*/
	friend bool operator < (const SIPOINT& A, const SIPOINT& B)
	{
		return	A.y < B.y ||
			A.y == B.y && (A.x < B.x);
	}
	friend bool operator > (const SIPOINT& A, const SIPOINT& B)	///<����������Ĵ��ڹ�ϵ����С�ڹ�ϵ�෴ @see operator <
	{
		return B < A;
	}
	void print_info();	///<�����Ϣ
	void read_info();	///<������Ϣ
};

/**
@brief ��ʾ�ı������е�һ�νڵ�
*/
struct SIRANGE
{
	SICHARNODE_P sp;	///<ָ����νڵ��ͷָ�� @see SICHARNODE_P
	SICHARNODE_P ep;	///<ָ����νڵ��βָ�� @see SICHARNODE_P
	SIRANGE(SICHARNODE_P tsp = NULL, SICHARNODE_P tep = NULL)	///<���캯��(Ĭ��)
	{
		sp = tsp;
		ep = tep;
	}
	/**
	@brief ��պ���\n
	@note �������ֻ�ǰ�sp��ep��ֵ��ΪNULL����������������еĽڵ�
	*/
	void _clear()
	{
		sp = ep = NULL;
	}
};

/**
@brief ��ʾһ���ַ����������ص���Ϣ\n
��ÿ���ַ������һ����Ļ�ϵľ��Σ�ÿ��������֮��û�з�϶
*/
class SIDRAW_INFO
{
public:
	/**
	@brief һ���ַ���ʼ���ε���״\n
	Ӱ������������\n
		-����
		-�ֺ�
	@see struct SIRECT
	*/
	SIRECT S;		//small rectangle	
	/**
	@brief һ���ַ�������Ļ�ϵ���״\n
	Ӱ������������\n
		-����
		-�ֺ�
		-�ּ��
		-�м��
		-���ַ���ǰ�����и߶���ߵ��ַ��ĸ߶�
	@see struct SIRECT
	*/
	SIRECT L;		//large rectangle	
	SIPOINT POS;	//coor. (left_top)	///<��ʾһ���ַ������Ͻ�����Ļ�ϵ�λ�� @see struct SIPOINT

	friend class SICHARNODE;
	SIDRAW_INFO()	///<���캯��1(Ĭ��)
	{
		S = SIRECT(); L = SIRECT(); POS = SIPOINT();
	}
	SIDRAW_INFO::SIDRAW_INFO(const SIRECT& TS, const SIRECT& TL, const SIPOINT& TPOS)	///<���캯��2
	{
		S = TS; L = TL; POS = TPOS;
	}	
	void set_S(const SIRECT&);	///<����S��ֵ(����:1)
	void set_S(int, int);	///<����S��ֵ(����:2)
	void set_L(const SIRECT&);	///<����L��ֵ
	void set_POS(const SIPOINT&);	///<����POS��ֵ
	const SIRECT& get_S();	///<���S��ֵ
	SIRECT& get_L();	///<���L��ֵ
	SIPOINT& get_POS();	///<���POS��ֵ
	///<interface>
	void print_info();	///<�����Ϣ
	void read_info();	///<������Ϣ

};

/**
@brief ��ʾһ���ַ��Ŀ���"����"����Ϣ
*/
class SICHAR_INFO
{
public:
	SIFONT_P fontpc;	///<������Ϣ,���MSDN @see SIFONT_P
	COLORERF color;	///<��ɫ��Ϣ @COLORERF
	COLORERF bgcolor;	///<������ɫ��Ϣ @COLORERF
	CHARSIZE size;	///<�����С������������ʶ�� @CHARSIZE
	CHARSPACE cspace;	///<�ּ�� @CHARSPACE
	LINESPACE lspace;	///<�м�� @LINESPACE
	SIALIGN align;	///<���뷽ʽ @SIALIGN

	friend class SICHARNODE;
	SICHAR_INFO() :fontpc(NULL)	///<���캯��1(Ĭ��)
	{
		//fontp = NULL;
		color = 0x000000;
		bgcolor = 0xffffff;
		size = cspace = lspace = 0;
		align = 0;
		fontpc = new SIFONT;
	};
	SICHAR_INFO(const SICHAR_INFO& tinfo)	///<���캯��2
	{

		*fontpc = *(tinfo.fontpc);
		color = tinfo.color;
		bgcolor = tinfo.bgcolor;
		cspace = tinfo.cspace;
		lspace = tinfo.lspace;
		align = tinfo.align;
	}
	~SICHAR_INFO()	///<��������
	{
		delete fontpc;
	}
	void set_fontpc(SIFONT_P tfontpc);	///<����fontpc��Ա(����:1) @see fontpc
	void set_fontpc(SIFONT& tfont);	///<����fontpc��Ա(����:2) @see fontpc
	void set_color(COLORERF tcolor);	///<����color��Ա @see color
	void set_size(CHARSIZE tsize);	///<����size��Ա @see size
	void set_cspace(CHARSPACE tcspace);	///<����cspace��Ա @see cspace
	void set_lspace(LINESPACE tlspace);	///<����lspace��Ա @see lspace
	///<interface>
	/**
	@brief �õ�������Ϣ\n
	@retval һ��ָ��SIFONT��ָ�룬��ʾ������Ϣ
	*/
	SIFONT_P get_fontpc();	
	/**
	@brief �õ���ɫ��Ϣ\n
	@retval һ��COLORREF���͵ı�������ʾ��ɫ
	*/
	COLORERF get_color();	
	/**
	@brief �õ������С\n
	@retval һ��CHARSIZE���͵ı�������ʾ�����С
	*/
	CHARSIZE get_size();
	///<interface>
	/**
	@brief �õ��ּ��\n
	@retval һ��CHARSPACE���͵ı�������ʾ�ּ��
	*/
	CHARSPACE get_cspace();
	/**
	@brief �õ��м��\n
	@retval һ��LINESPACE���͵ı�������ʾ�м��
	*/
	LINESPACE get_lspace();
	void print_info();	///<�����Ϣ
	void read_info();	///<������Ϣ
	/**
	@brief ���ظ�ֵ����\n
	@note ��������У�fontpc�Ǹ���ָ��ָ������ݶ�����ָ�뱾��
	@param[in] *this �������
	@param[in] tinfo �Ҳ�����
	@retval *this 
	*/
	SICHAR_INFO& operator = (const SICHAR_INFO& tinfo);	
};


/**
@brief ��ʾ�ı������һ���ڵ�\n
*/
class SICHARNODE
{
public:
	SICHAR_T ch;	///<�ַ� @see SICHAR_T
	/**
	@brief ������Ϣ\n
	һ��ָ��SICHAR_INFO���͵�ָ�룬������ַ���������Ϣ 
	@see class SICHAR_INFO
	*/
	SICHAR_INFO_P char_infop; 
	/**
	@brief ������Ϣ\n
	һ��ָ��SIDRAW_INFO���͵�ָ�룬������ַ��Ļ�����Ϣ
	@see class SIDRAW_INFO
	*/
	SIDRAW_INFO_P draw_infop;
	SICHARNODE *prevp;	///<ָ������ǰһ���ڵ��ָ��
	SICHARNODE *nextp;	///<ָ�������һ���ڵ��ָ��

	friend class SITEXT;
	SICHARNODE(SICHAR_T tch, SICHARNODE* tprevp = NULL, SICHARNODE* tnextp = NULL
		, SICHAR_INFO_P tchar_infop = NULL, SIDRAW_INFO_P tdraw_infop = NULL)	///<���캯��1
	{
		ch = tch;
		char_infop = new SICHAR_INFO;
		draw_infop = new SIDRAW_INFO;
		if (tchar_infop != NULL) *char_infop = *tchar_infop;
		if (tdraw_infop != NULL) *draw_infop = *tdraw_infop;
		prevp = tprevp;
		nextp = tnextp;
	}

	SICHARNODE(SICHAR_T tch, int tswidth, int tsheight)	///<���캯��2
	{
		ch = tch;
		char_infop = new SICHAR_INFO;
		draw_infop = new SIDRAW_INFO;
		draw_infop->S.width = tswidth;
		draw_infop->S.height = tsheight;
	}
	~SICHARNODE()	///<��������
	{
		if (char_infop != NULL) delete char_infop;
		if (draw_infop != NULL) delete draw_infop;
	}
private:
	void calc_S_from_font();///<�ӵ�ǰ����������������Ϣ�е�S�Ĵ�С @see S @see fontpc
public:
	void set_fontpc(SIFONT_P tfontpc);	///<����char_infop�е�fontpc�����¼���draw_infop�е�S�Ĵ�С
	void set_fontpc(SIFONT& tfont);
	void set_color(COLORERF tcolor);
	void set_size(CHARSIZE tsize);
	void set_draw_infop_S(const SIRECT& TS);
	void set_draw_infop_L(const SIRECT& TL);
	void set_draw_infop_P(const SIPOINT& TP);
	void set_align(SIALIGN align);
	/**
	@brief �ڵ�ǰ�ַ���ǰ�����һ���ڵ�\n
	@param[in] p ָ�򱻲���ڵ��ָ��
	@note �ú������pָ��Ľڵ��������Ϣ��Ϊ��p��ǰһ���ڵ���ͬ
	*/
	void ins_prev(SICHARNODE* p);
	/**
	@brief �ڵ�ǰ�ַ��ĺ������һ���ڵ�\n
	@param[in] p ָ�򱻲���ڵ��ָ��
	@note �ú������pָ��Ľڵ��������Ϣ��Ϊ��p��ǰһ���ڵ���ͬ
	*/
	void ins_next(SICHARNODE* p);
	/**
	@brief �ڵ�ǰ�ַ���ǰ�����һ�νڵ�\n
	@param[in] ps ָ�򱻲���ڵ�ε�ͷָ��
	@param[in] pe ָ�򱻲���ڵ�ε�βָ��
	@note �ú�������ı䱻����ڵ�ε�������Ϣ\n
	Ҫ����νڵ���������Ѿ�������Ľṹ��֯����
	*/
	void ins_prev(SICHARNODE* ps, SICHARNODE* pe);
	/**
	@brief �ڵ�ǰ�ַ��ĺ������һ�νڵ�\n
	@param[in] ps ָ�򱻲���ڵ�ε�ͷָ��
	@param[in] pe ָ�򱻲���ڵ�ε�βָ��
	@note �ú�������ı䱻����ڵ�ε�������Ϣ\n
	Ҫ����νڵ���������Ѿ�������Ľṹ��֯����
	*/
	void ins_next(SICHARNODE* ps, SICHARNODE* pe);
	void ins_prev(const SIRANGE& range);	///<@see ins_prev
	void ins_next(const SIRANGE& range);	///<@see ins_next
	/**
	@brief ��������ɾ��һ���ڵ�\n
	@param[in] p ��ɾ���Ľڵ�
	@note p�����������ͷ�ڵ��β�ڵ�
	*/
	friend void del(SICHARNODE* p);
	/**
	@brief ��������ɾ��һ�νڵ�\n
	@param[in] ps ָ��ɾ���ڵ�ε�ͷ�ڵ�
	@param[in] pe ָ��ɾ���ڵ�ε�β�ڵ�
	@note �ýڵ�β��ܰ��������ͷ�ڵ��β�ڵ�
	*/
	friend void del(SICHARNODE* ps, SICHARNODE* pe);	///
	friend void del(const SIRANGE& range);	///<@see del
	///<interface>
	const SICHAR_INFO_P get_char_infop();	///<�õ�һ��char_infop��const���� @see char_infop
	const SIDRAW_INFO_P get_draw_infop();	///<�õ�һ��draw_infop��const���� @see draw_infop
	///<\interface>
	void print_info();	///<�����Ϣ
	void read_info();	///<������Ϣ

};


/**
@brief �ı�����\n
���ı���ͷ��β�����һ������
*/
class SITEXT
{
public:

	string save_path;	///<����·��
	string open_path;	///<��·��

	SICHARNODE_P headp;	///<�ı�����ͷָ�� @see SICHARNODE_P
	SICHARNODE_P tailp;	///<�ı�����βָ�� @see SICHARNODE_P

	/**
	@brief ���λ��\n
	һ��ָ��������һ���ڵ��ָ�룬������ʾ���Ŀǰ���ڵ�λ��
	@note ��ָ��ָ��Ľڵ������Ļ����ʾ�Ĺ��ĺ�һ���ַ�
	@see SICURSORP
	*/
	SICURSORP cursorp;
	SISELECT select;	///<��ǰѡ�е����� @see SISELECT

	PAGEWIDTH pagewidth;	///<ҳ���ȣ����ڼ����ַ���λ�� @see PAGEWIDTH

	SIFONT_P curfontpc;	
	SIFONT default_font;	///<��ʼ��Ĭ������ @see SIFONT

	bool inselect;	
	int fwdnum;
	std::vector<SILINE> vlinep;	///<��˳�򴢴���Ļ�ϴ��ϵ��µ�ÿһ�� @see SILINE
	std::vector<SIPARAGRAPH> vparap;	///<��˳�򴢴���Ļ�ϴ��ϵ���ÿһ�� @see SIPARAGRAPH

	//set true when text changed specifically when \
				effectable methods are called		\
	  set false when repaint() is called
	bool text_changed_f;	///<�ı��ı��־
	//set true when set_curfontp() is called \
			  set false when cursor moved
	bool set_curfontp_f;

private:

	void _init();	///<��ʼ������
	void _destroy();	///<������ݲ��ͷ��ڴ�
	/**
	@brief �м��㺯��\n
	���ڼ���һ���ַ��Ļ�����Ϣ
	@param[in] ps ָ�����ͷ�ڵ��ָ��
	@param[in] pe ָ�����β�ڵ��ָ��
	@param[in] sx �������Ͻǵ�x����
	@param[in] y  �������Ͻǵ�y����
	@param[in] line_height �и�
	@param[in] delta ÿ���ַ���������Ŀ����ĸ��ӿ��(ֻ�ڷ�ɢ����ʱ��Ϊ0)
	*/
	void draw_line_from_left(SICHARNODE_P ps, SICHARNODE_P pe, int sx, int y, int line_height, int deltax);
	/**
	@brief �д�����\n
	���ݲ�ͬ���뷽ʽ���ڼ���һ���ַ��Ļ�����Ϣ
	@param[in] ps ָ�����ͷ�ڵ��ָ��
	@param[in] pe ָ�����β�ڵ��ָ��
	@param[in] n  ���е��ַ�����(���������з�)
	@param[in] y  �������Ͻǵ�����
	@param[in] line_height �и�
	@param[in] tot_width �����ַ�����Ŀ���ܺ�
	@param[in] align ���еĶ��뷽ʽ
	@todo �����align�Ľ���
	*/
	void proc_line(SICHARNODE_P ps, SICHARNODE_P pe, int n, int y, int line_height, int tot_weight, SIALIGN align);
	/**
	@brief Ԥ������\n
	���ı���Ԥ����(��Ҫ����ӷֶη�)
	*/
	void pre_proc();
	void proc_text();	///<�ı�������
	inline std::vector<SILINE>::iterator point_to_line(const SIPOINT& P);	///<�������Ļ��ĳһ�����һ��
	inline void set_line_align(const SILINE& line, SIALIGN align);	///<����ĳһ�еĶ��뷽ʽ

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
	SITEXT()	///<���캯�� @see _init
	{
		_init();
	}
	~SITEXT()	///<�������� @see _destroy
	{
		_destroy();
	}
	
	void save();	///<�����ı�
	void open();	///<���ı�
	void ins_char(SICHAR_T);	///<�ڹ��ǰ������һ���ַ�
	void ins_char(SICHAR_T, int, int);	///<�ڹ��ǰ������һ���ַ���ָ��S�Ĵ�С
	/**
	@brief ɾ���ַ�\n
	@param[in] backwards
	@todo �����backwards���ܵ�ȡֵ��˵��
	*/
	void del_char(bool backwards);
	void start_select();	///<����ѡ��״̬
	void end_select();	///<����ѡ��״̬
	void del_select();	///<ɾ����ѡ�е��ַ�
	void replace_select(const SIRANGE&);	///<�滻��ѡ�е��ַ�(����1)
	void replace_select(SICHARNODE_P ps, SICHARNODE_P pe);	///<�滻��ѡ�е��ַ�(����2)
	/**
	@brief ȡ��ѡ��\n
	@note �ú�����ѡ������ΪNULL��������ı���������
	*/
	void cancel_select();
	void mov_select(SICURSORP);	///<��ѡ���ַ��Ƶ��������
	/**
	@brief �ƶ����(����1)\n
	�ѹ���Ƶ�����ָ���Ľڵ㴦
	@param[in] tcursorp �ƶ���Ŀ��ڵ�
	*/
	void mov_cursorp(SICURSORP);	
	/**
	@brief �ƶ����(����2)\n
	�ѹ������/��/��/���ƶ�һ��
	@param[in] tdir �ƶ�����
	*/
	void mov_cursorp(SIDIRECT);
	/**
	@�ƶ����(����3)\n
	�ѹ���Ƶ���Ļ��һ�������λ��
	@param[in] P Ŀ��λ��
	*/
	void mov_cursorp(const SIPOINT&);
	
	void set_default_font(SIFONT& tfont);	///<����Ĭ������(����1)
	void set_default_font(SIFONT_P tfontp);	///<����Ĭ������(����2)
	void set_select_font(SIFONT_P tfontpc);	///<����ѡ�����������(����1)
	void set_select_font(SIFONT& tfont);	///<����ѡ�����������(����2)
	void set_curfont(SIFONT_P tcurfontpc);	
	void set_curfont(SIFONT& tcurfont);
	void set_select_color(COLORERF tcolor);	///<����ѡ���������ɫ
	void set_select_lspace(LINESPACE tlspace);	///<����ѡ��������о�
	void set_select_cspace(CHARSPACE tcspace);	///<����ѡ��������ּ��
	void set_pagewidth(PAGEWIDTH tpagewidth);	///<����ҳ����
	void set_select_align(SIALIGN align);	///<����ѡ������Ķ��뷽ʽ
	void set_cursorp_align(SIALIGN align);	///<���ù�������еĶ��䷽ʽ
	/**
	@brief �õ�һ�νڵ�Ķ��뷽ʽ(����1)\n
	@param[in] �ýڵ�ε�ͷ�ڵ�
	@param[in] �ýڵ�ε�β�ڵ�
	@note �����νڵ��ж��ַ�Ĭ�ϵĶ��뷽ʽ��ѡ���ǰ�Ľڵ�Ķ��뷽ʽ
	*/
	SIALIGN get_range_align(SICHARNODE_P ps,SICHARNODE_P pe);	
	SIALIGN get_range_align(const SIRANGE& range);	///<�õ�һ�νڵ�Ķ��뷽ʽ(����2) @see get_range_align

	void set_save_path(string tsave_path);	///<���ñ���·��
	void set_open_path(string topen_path);	///<���ô�·��
	SICURSORP point_to_cursorp(const SIPOINT& P);	///<����Ļ�ϵĵ�ת��Ϊ���λ��
	void repaint();	///<���¼���������Ϣ
	void print_info();	///<�����Ϣ
	void read_info();	///<������Ϣ
	void anticolor(SICHARNODE_P ps, SICHARNODE_P pe);	///<��һ���ַ���ɫ

	/**
	@brief �ж�һ����Ļ�ϵĵ��Ƿ���ĳһ����\n
	@param[in] L ���жϵ���
	@param[in] P ���жϵĵ�
	@retval true �õ�����һ����
	@retval false �õ㲻����һ����
	*/
	friend bool point_on_line(SILINE L, const SIPOINT& P);
	/**
	@brief �ж�һ����Ļ�ϵĵ��Ƿ���ĳһ���ַ�����������\n
	@param[in] np ָ���ж��ַ��Ľڵ�ָ��
	@param[in] P  ���жϵĵ�
	@retval true �õ��ڸ��ַ����ڵ�����
	@retval false �õ㲻�ڸ��ַ���������
	@note �ú����жϵ�ֻ���У������жϵ��Ƿ����ַ���
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