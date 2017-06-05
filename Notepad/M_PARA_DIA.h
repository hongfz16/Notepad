/**
@brief 声明一个用于设置行间距以及字间距的对话框类M_PARA_DIA \n
@file M_PARA_DIA.h
@author 洪方舟
@email hongfz16@163.com
@version 1.0
@date 2017.5.25
*/

#pragma once
#include "stdafx.h"
#include "Notepad.h"
#include "kernal.h"
#include "resource.h"
/**
@brief 设置行间距以及字间距的对话框类M_PARA_DIA \n
该对话框用于用户设置行间距以及字间距\n
如果用户选择了一段文字，则输入的行距字间距将被用于选中的文字\n
如果用户没有选择文字，那么输入的行间距字间距将被应用于之后将会打出来的文字上\n
*/
class M_PARA_DIA : public CDialogEx {
  DECLARE_DYNAMIC(M_PARA_DIA)

 public:
  ///默认构造函数
  M_PARA_DIA(CWnd* pParent = NULL);
  ///默认析构函数
  virtual ~M_PARA_DIA();

#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_PARA_DIALOG };
#endif

 protected:
  ///数据交换函数
  virtual void DoDataExchange(CDataExchange* pDX);

  DECLARE_MESSAGE_MAP()
 public:
  afx_msg void OnEnChangeEdit2();
  afx_msg void OnEnChangeEdit3();
  afx_msg void OnEnUpdateLine();
  afx_msg void OnEnUpdateCharac();
  ///当按下OK按钮的消息响应函数
  afx_msg void OnBnClickedOk();
  ///行间距
  int m_linespace;
  ///字间距
  int m_charaspace;
};
