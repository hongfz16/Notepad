/**
@brief 声明程序主框架类CMainframe类 \n
@file MainFrame.h
@author 洪方舟
@email hongfz16@163.com
@version 1.0
@date 2017.5.25
*/

#pragma once
class CChildView;
#include "stdafx.h"
#include "ChildView.h"
#include "m_back_color.h"
#include "M_PARA_DIA.h"
/**
@brief 程序主框架类CMainFrame类 \n
主框架包括子视图类以及滚动条
继承自CFrameWnd类
*/
class CMainFrame : public CFrameWnd {
 public:
  /**
  @brief CMainFrame类构造函数\n
  初始化部分成员变量
  - m_client_cy = 10000
  - scrolledpix = 0
  */
  CMainFrame();

 protected:
  DECLARE_DYNAMIC(CMainFrame)

 public:
  ///绘图预处理函数,如果需要修改窗口样式则改写该函数
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
  ///主消息循环函数,无需修改
  virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra,
                        AFX_CMDHANDLERINFO* pHandlerInfo);

 public:
  ///默认析构函数
  virtual ~CMainFrame();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

  ///子视图类成员变量
public:
  CChildView m_wndView;

 protected:
  /**
  @brief 创建主窗口时调用的函数\n
  创建了两个实例\n
  - CChildView m_wndView @see CChildView
  - CScrollBar m_scrollBar 竖直滚动条实例
  @param[in] lpCreateStruct 至于这个是什么不重要,不需要自己调用这个函数
  */
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  ///当窗口被聚焦的时候调用,无需修改
  afx_msg void OnSetFocus(CWnd* pOldWnd);
  DECLARE_MESSAGE_MAP()

 public:
  ///用于存储客户区的大小的变量
  CRect m_client_rect;
  ///用于存储子视图的y方向的长度
  int m_client_cy;
  /**
  @brief 当窗口大小被调整之后调用的函数\n
  @param[in] cx 当前窗口x方向长度
  @param[in] cy 当前窗口y方向长度
  @note 该函数仅在OnSize函数中被调用,因为传入的参数需要用到OnSize函数的传入值
  @see OnSize
  */
  void UpdateClientRect();
  /**
  @brief 当窗口大小被调整之后调用的消息响应函数\n
  当窗口大小被调整,共有两个地方需要调整\n
  - 子窗口的大小\n通过调用UpdateClientRect函数 @see UpdateClientRect
  - 滚动条的一系列调整\n 滚动条的长度调整\n 滚动条上拖动块的位置调整
  @param[in] nType 参阅MSDN官方文档
  @param[in] cx 由系统传入当前窗口x方向的长度
  @param[in] cy 有系统传入当前窗口y方向的长度
  @note
  无需自己调用,当手动改变窗口大小的时候,系统会传入ON_WM_SIZE消息,此时会自动调用该函数
  */
  afx_msg void OnSize(UINT nType, int cx, int cy);

  // scroll bar
 protected:
  ///滚动条类实例
  CScrollBar m_scrollBar;
public:
  ///用于记录页面相对于上边界偏移量
  int scrolledpix;

 public:
  /**
  @brief 改变滚动块的位置时调用的函数\n
  调整两个地方\n
  - 子视图的位置
  - 滚动块的位置更新
  @param[in] nSBCode 参阅MSDN官方文档
  @param[in] nPos 参阅MSDN官方文档
  @param[in] pScrollBar 当前被滑动的滚动条的指针
  */
  afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
  /**
  @brief 当改变窗口大小时,调整滚动块的位置\n
  通过记录页面相对于上边界的偏移量来调整
  @note 此函数仅在OnSize函数中调用 @see OnSize
  */
  void UpdateScrollBarPos();

  int maincx;
  int maincy;
};


