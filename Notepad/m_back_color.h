/**
@brief 声明一个用于设置背景颜色的对话框类m_back_color \n
@file m_back_color.h
@author 洪方舟
@email hongfz16@163.com
@version 1.0
@date 2017.5.25
*/

#pragma once
#include "stdafx.h"

/**
@brief 设置背景颜色的对话框类m_back_color \n
该对话框用于用户选择当前文字的背景颜色\n
如果用户选择了一段文字，则选择的颜色将被应用于选中的文字\n
如果用户没有选择文字，那么选择的颜色将被应用于之后将会打出来的文字上\n
*/
class m_back_color : public CDialogEx {
  DECLARE_DYNAMIC(m_back_color)

 public:
  ///默认构造函数
  m_back_color(CWnd* pParent = NULL);
  ///默认析构函数
  virtual ~m_back_color();

#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_BACKGROND_COLOR };
#endif

 protected:
  //数据交换函数
  virtual void DoDataExchange(CDataExchange* pDX);

  DECLARE_MESSAGE_MAP()

 public:
  ///COLORREF型变量用于存储用户选定的颜色
  COLORREF color;
  ///响应按下OK键的消息函数
  afx_msg void OnBnClickedOk();
  ///响应按下颜色选择器的消息
  afx_msg void OnBnClickedMfccolorbutton1();
  ///MFC的颜色选择器
  CMFCColorButton m_colorPicker;
};
