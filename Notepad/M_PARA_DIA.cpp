// M_PARA_DIA.cpp : 实现文件
//

#include "stdafx.h"
#include "Notepad.h"
#include "M_PARA_DIA.h"
#include "afxdialogex.h"


// M_PARA_DIA 对话框

IMPLEMENT_DYNAMIC(M_PARA_DIA, CDialogEx)

M_PARA_DIA::M_PARA_DIA(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PARA_DIALOG, pParent)
{
	
}

M_PARA_DIA::~M_PARA_DIA()
{
}

void M_PARA_DIA::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LINE, m_linespace);
	DDX_Text(pDX, IDC_CHARAC, m_charaspace);
}


BEGIN_MESSAGE_MAP(M_PARA_DIA, CDialogEx)
	ON_EN_CHANGE(IDC_LINE, &M_PARA_DIA::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_CHARAC, &M_PARA_DIA::OnEnChangeEdit3)
	ON_EN_UPDATE(IDC_LINE, &M_PARA_DIA::OnEnUpdateLine)
	ON_EN_UPDATE(IDC_CHARAC, &M_PARA_DIA::OnEnUpdateCharac)
	ON_BN_CLICKED(IDOK, &M_PARA_DIA::OnBnClickedOk)
END_MESSAGE_MAP()


// M_PARA_DIA 消息处理程序


void M_PARA_DIA::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void M_PARA_DIA::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void M_PARA_DIA::OnEnUpdateLine()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数，以将 EM_SETEVENTMASK 消息发送到该控件，
	// 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void M_PARA_DIA::OnEnUpdateCharac()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数，以将 EM_SETEVENTMASK 消息发送到该控件，
	// 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void M_PARA_DIA::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	UpdateData(false);
	CDialogEx::OnOK();
}
