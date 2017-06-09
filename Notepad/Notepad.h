/**\mainpage 基于MFC的文本编辑器
说明文档
===================

目标
-------------------
1. 不使用MFC文本框控件，实现一个简单的文本编辑器
2. 最低要求如下：
    * 带有图形界面
    * 能够比较方便的给不同的字符设置不同的字体、颜色和字号
    * 可以设置字与字之间的间距
3. 另外还实现了以下功能
    * 保存、打开自定义格式的文件
    * 设置对齐方式，包括左对齐、居中对齐、右对齐、分散对齐
    * 设置行间距

构件库
-------------------
详情请参见Class List

UI界面的交互实现方法说明
-------------------
1. 设置字体字号颜色 \n
通过`CFontDialog`窗口类，创建选择字体的窗口 \n
用户选择字体以及颜色后，获取字体信息`LOGFONT`以及颜色信息`REFCOLOR`\n
通过`set_select_font`与`set_select_col`函数将字体以及颜色信息传递给后端\n
2. 设置字间距行间距 \n
通过`M_PARA_DIA`对话框，获取用户设置的字间距与行间距的值 \n
通过`set_select_lspace`与`set_select_cspace`函数将字间距与行间距传给后端\n
3. 保存、打开文件 \n
通过`CFileDialog`类，返回用户需要保存或者打开文件的路径\n
通过`#`与`#`函数将路径作为字符串传给后端\n
4. 设置对齐方式 \n
直接通过消息响应函数，调用`set_select_align`函数,设置对齐方式\n


后端（kernal）实现方法说明
-------------------


UI及交互部分遇到的问题及解决方案
-------------------
1. 绘图过程闪烁的问题 \n
问题描述：使用过程中每当需要屏幕刷新的时候，画面会不停的闪烁 \n
可能原因：每次调用OnPaint函数的时候都会先将屏幕清空，由于绘制屏幕仍然需要一定的时间，所以每次重绘都会出现闪烁的情况 \n
解决方案：使用双缓冲绘图，分为两个部分：\n
(1)重载`BOOL CChildView::OnEraseBkgnd(CDC* pDC)`函数，使得画面不会被擦除\n
(2)先在使用内存DC上画图，画好后直接调用`BitBlt`函数将画面传给物理DC\n

2. 滚动条位置以及大小的问题\n
问题描述：滚动条大小以及位置随着窗口大小改变而随机变动\n
可能原因：由于滚动条控件需要手动设置大小以及位置，所以当改变窗口大小的时候会出现滚动条位置偏移的情况\n
解决方案：设置两个变量：`m_client_cy`记录页面长度，`scrolledpix`记录页面相对于窗口上端的偏移量\n
每次重绘的时候通过这两个量来重新计算滚动条的大小以及位置\n

3. 解析用户传入的键盘消息\n
问题描述：根据官方文档，键盘消息的对应关系很复杂，需要解析传入的参数才能获得字符信息\n
解决方案：使用`void CChildView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)`的消息响应函数\n
系统将键盘消息处理后返回用户输入的字符\n

4. 连按消息的问题\n
问题描述：通常连按一个按键，被认为是连续输入字符\n
解决方案：在`void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) `函数中\n
`nRepCnt`参数是用于标记连按消息的次数的，循环相应的次数即可实现连续输入\n

5. 获取字体的像素大小的问题\n
问题描述：`LOGFONT`结构体的成员`lfHeight`与`lfWidth`不是像素高度\n
解决方案：通过公式`pixHeight = -(lfHeight * 72) / GetDeviceCaps(hDC,LOGPIXELSY)`转换为像素高度\n
参考资料：[MSDN上关于LOGFONT的说明](https://msdn.microsoft.com/zh-cn/library/bb773327.aspx)\n


后端（kernal）遇到的问题及解决方案
-------------------


测试用例
-------------------


总结
-------------------
1. 程序具有一定的可使用性，实现了基本目标，在数据规模不太大的情况下可以达到较好效果
2. 当数据规模较大时（超过50000字符），会出现明显的卡顿现象，所以程序仍然有很大改进空间


作者信息
-------------------
- kernal部分作者：李仁杰\n
    + 学院：清华大学软件学院\n
    + 班级：软件62\n
    + 学号：\n
    + e-mail：\n
    + 电话：\n
- UI及交互部分作者：洪方舟\n
    + 学院：清华大学软件学院\n
    + 班级：软件62\n
    + 学号： 2016013259\n
    + e-mail: hongfz16@163.com\n
    + 电话：15062727188\n
*/

/**
@brief 声明程序大类CNotepadApp \n
@file Notepad.h
@author 洪方舟
@email hongfz16@163.com
@version 1.0
@date 2017.5.25
*/
#pragma once
#include "stdafx.h"
#include "MainFrm.h"
#include "resource.h"
#include <string>

/**
@brief 程序大类CNotepadApp\n
程序启动时创建,初始化函数中创建其他的对象\n
在初始化过程中创建菜单,主窗口\n
继承自CWinApp
*/
class CNotepadApp : public CWinApp {
 public:
  
  CNotepadApp();///<默认构造函数
  
  CMainFrame* mainp;///<指向主窗口的指针

 public:
  
  virtual BOOL InitInstance();///<初始化函数,实例化CMainFrame类,并且将mainp指针指向它
  
  virtual int ExitInstance();///<退出程序调用函数

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
  afx_msg void OnCut();
  afx_msg void OnCopy();
  afx_msg void OnPaste();

  SIRANGE m_cutBoard; ///<剪贴板,实际上是两个指向文字节点的指针组成的结构体

 public:
 	
  afx_msg void OnAppAbout();///<"关于"窗口的消息相应函数

  DECLARE_MESSAGE_MAP()
  
  afx_msg void OnAlignLeft();///<左对齐的消息响应函数
  
  afx_msg void OnAlignCenter();///<居中的消息响应函数农户
  
  afx_msg void OnAlignRight();///<右对齐的消息响应函数
  
  afx_msg void OnAlignDistribute();///<分散对齐的消息响应函数

  afx_msg void OnOpen();///<打开文件的消息响应函数
  
  afx_msg void OnClose();///<关闭文件的消息响应函数

  inline void change_align(int flag)
  {
	  if(mainp->m_wndView.m_text->select.ep!=NULL)
		mainp->m_wndView.m_text->set_select_align(flag);
	  else
		  mainp->m_wndView.m_text->set_cursorp_align(flag);
	  mainp->m_wndView.need_recompute = true;
	  mainp->m_wndView.m_changed();
	  mainp->m_wndView.curchanged();
  }///<改变对齐方式的函数

};

extern CNotepadApp theApp;
