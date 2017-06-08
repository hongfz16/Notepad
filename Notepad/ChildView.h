/**
@brief 声明子视窗类CChildView \n
@file ChildView.h
@author 洪方舟
@email hongfz16@163.com
@version 1.0
@date 2017.5.25
*/

#pragma once
class CMainFrame;
#include "stdafx.h"
#include "kernal.h"


//#include "MainFrm.h"
/**
@brief 子视窗类CChildView \n
子视窗是程序中客户区部分，即文本编辑的画布部分
-此类继承自CWnd
*/
class CChildView : public CWnd {
 public:
  /// CChildView类构造函数
  CChildView();

 protected:
  ///创建窗口的预处理函数
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

 public:
  /// CChildView类析构函数
  virtual ~CChildView();

 protected:
  /**
  @brief 绘图函数 \n
  当程序接受到ON_WM_PAINT的消息的时候就会调用该函数\n
  该函数所做工作包括\n
    - 重新计算所有文字的位置
    - 重新绘制画面，包括所有文字以及背景色
    - 将需要重绘的flag(即text_changed_f)置为flase
  @note 请不要手动调用该函数，如需重绘画面请用Invalidate(false);函数
  */
  afx_msg void OnPaint();
  DECLARE_MESSAGE_MAP()

 public:
  ///自定义的文本文字类成员@see SITEXT
  SITEXT* m_text;

 public:
  /**
  @brief 绘制所有文字以及背景色的函数 \n
  @param[in] dc 当前绘图区的句柄
  @note 仅在OnPaint函数中调用
  @todo 绘制背景色
  */
  void m_paintText(CDC& dc);
  void m_paintText(CPaintDC& dc);

  /**
  @brief 绘制光标 \n
  @param[in] dc 当前绘图区的句柄
  @note 仅在OnPaint函数中调用
  @todo 绘制可以闪动的光标
  */
  void m_paintCur(CDC& dc);
  void m_paintCur(CPaintDC& dc);
 public:
  /**
  @brief 响应发送文字消息的函数 \n
  响应ON_WM_CHAR消息
  @param[in] nChar 用户发送给系统的字符，为UINT型，需要手动转化为wchar_t型
  @param[in] nRepCnt 重复发送同一个消息（用户按下一个键不松手）的次数
  @param[in] nFlags 各个符号位的具体作用参见MSDN官方文档
  @note 请不要手动调用该函数
  */
  afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
  /**
  @brief 判断是否为正常字符范围的输入
  @param[in] nChar @see OnChar
  @retval true 是正常范围的字符
  @retval false 不是正常范围的字符
  */
  inline bool is_input(UINT nChar);

 public:
  /**
  @brief 当文本内容根据用户的操作有变化的时候调用 \n
  操作如下\n
  - 设置画面变化的flag(即text_changed_f)为true
  - 调用Invalidate(false)函数向程序发送重绘消息
  */
  inline void m_changed();
  /**
  @brief 响应鼠标左键按下消息的函数 \n
  当程序收到ON_WM_LBUTTONDOWN消息时调用该函数\n
  主要处理两种情况\n
  -# 当没有文字被选中的时候，将光标位置调整为当前点击位置，进入选择状态
  -# 没有文字被选中的时候,不作任何动作
  @param[in] nFlags 各个符号位的具体作用参见MSDN官方文档
  @param[in] point 返回鼠标左键按下时的屏幕坐标
  @note 返回的坐标值是相对于客户区左上角而言的
  */
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  /**
  @brief 响应鼠标左键抬起消息的函数 \n
  当程序收到ON_WM_LBUTTONUP消息时调用该函数\n
  主要处理两种情况\n
  -#
  当没有文字被选中的时候，将光标位置调整为当前抬起的位置，结束选中状态。如果鼠标左键在按下与抬起之间有移动，则会有文字被选中
  -# 当有文字被选中的时候，将光标位置更新，并且取消选中状态
  @param[in] nFlags 各个符号位的具体作用参见MSDN官方文档
  @param[in] point 返回鼠标左键抬起时的屏幕坐标
  @note 返回的坐标值是相对于客户区左上角而言的
  */
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  /**
  @brief 响应鼠标移动消息的函数 \n
  当程序收到ON_WM_MOUSEMOVE消息时调用该函数\n
  进入函数之后需要鼠标左键被按下的flag为true才会做出操作\n
  操作主要为更新选择文字过程中的光标位置以及画面\n
  @param[in] nFlags 各个符号位的具体作用参见MSDN官方文档
  @param[in] point 返回鼠标移动时的屏幕坐标
  @note 返回的坐标值是相对于客户区左上角而言的
  @todo 目前这种写法是无法实现动态效果的，所以需要改进
  */
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);

 private:
  ///指示鼠标左键是否按下的flag
  bool LBuDown;

 public:
  /**
  @brief 键盘按下消息响应函数 \n
  此函数内部对nChar有判断，也就是说此函数只处理按下上下左右键的消息
  @param[in] nChar 用户按下的键值
  @param[in] nRepCnt 用户按下该键的重复次数（用户按住该键）
  @param[in] nFlags 各个符号位的具体作用参见MSDN官方文档
  @note 本函数只处理将光标上下左右移动的键盘消息，并且本函数只在用户按住一个键重复次数超过一的时候有效
  */ 
  afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  /**
  @brief 键盘抬起消息响应函数 \n
  此函数内部对nChar有判断，也就是说此函数只处理按下上下左右键的消息
  @param[in] nChar 用户按下后抬起的键值
  @param[in] nRepCnt 用处不明
  @param[in] nFlags 各个符号位的具体作用参见MSDN官方文档
  @note 本函数只处理将光标上下左右移动的键盘消息
  */ 
  afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);


  private:
	  ///按下Backspace的响应，即向反方向删除的flag
	  bool SIBACKSPACE = true;
	  ///按下delete的响应，即向正向删除的flag
	  bool SIDELETE = false;
public:
	///重载擦除屏幕函数，使它的返回值为false，即不擦除，配合双缓冲绘图使用
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	///指向主窗口的指针
	CMainFrame* mainframep;
  ///需要重新计算页面布局的flag
	bool need_recompute;
};



