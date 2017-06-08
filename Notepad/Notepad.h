/**
@brief 声明程序大类CNotepadApp \n
@file ChildView.h
@author 洪方舟
@email hongfz16@163.com
@version 1.0
@date 2017.5.25
*/
#pragma once
#include "stdafx.h"
#include "MainFrm.h"
#include "resource.h"


/**
@brief 程序大类CNotepadApp\n
程序启动时创建,初始化函数中创建其他的对象\n
在初始化过程中创建菜单,主窗口\n
继承自CWinApp
*/
class CNotepadApp : public CWinApp {
 public:
  ///默认构造函数
  CNotepadApp();
  ///指向主窗口的指针
  CMainFrame* mainp;

 public:
  ///初始化函数,实例化CMainFrame类,并且将mainp指针指向它
  virtual BOOL InitInstance();
  ///退出程序调用函数
  virtual int ExitInstance();

 public:
  /**
  @brief 选择字体消息响应函数\n
  - 实例化MFC字体选择对话框
  - 将用户选择的字体传入SITEXT实例中 @see SITEXT
  @note 该函数响应ID_FONT消息,当用户点击菜单栏中"字体"一项时发送该消息
  */
  afx_msg void OnFont();

 public:
  /**
  @brief 选择行间距字间距消息响应函数\n
  - 实例化选择行间距字间距的对话框
  - 将用户设置的行间距以及字间距传入SITEXT实例中 @see SITEXT
  @note 该函数响应ID_PARA消息,当用户点击菜单栏中"段落"一项时发送该消息
  */
  afx_msg void OnPara();

 public:
  /**
  @brief 剪切消息响应函数\n
  - 将用户选中的文字复制入剪贴板
  - 将选中的文字删除
  */
  afx_msg void OnCut();
  /**
  @brief 复制消息响应函数\n
  - 将用户选中的文字复制入剪贴板
  */
  afx_msg void OnCopy();
  /**
  @brief 粘贴消息响应函数\n
  - 如果有文字处于选中状态,先将选中的文字删除,再在光标处粘贴剪贴板中的文字
  - 如果没有文字处于选中状态,直接在光标处粘贴剪贴板中的文字
  */
  afx_msg void OnPaste();
  /**
  @brief 选择文字背景色的消息响应函数
  - 如果有文字处于选中状态,将选中的文字设置为选中的颜色
  - 如果没有文字处于选中状态,将默认背景色改为选中颜色
  */
  afx_msg void OnBackColor();
  ///剪贴板,实际上是两个指向文字节点的指针组成的结构体
  SIRANGE m_cutBoard;

 public:
 	///"关于"窗口的消息相应函数
  afx_msg void OnAppAbout();
  DECLARE_MESSAGE_MAP()
  ///左对齐的消息响应函数
  afx_msg void OnAlignLeft();
  ///居中的消息响应函数农户
  afx_msg void OnAlignCenter();
  ///右对齐的消息响应函数
  afx_msg void OnAlignRight();
  ///分散对齐的消息响应函数
  afx_msg void OnAlignDistribute();
};

extern CNotepadApp theApp;
