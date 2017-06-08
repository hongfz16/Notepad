// M_PARA_DIA.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Notepad.h"
#include "M_PARA_DIA.h"
#include "afxdialogex.h"


// M_PARA_DIA �Ի���

IMPLEMENT_DYNAMIC(M_PARA_DIA, CDialogEx)

M_PARA_DIA::M_PARA_DIA(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PARA_DIALOG, pParent)
{
	m_linespace = 0;
	m_charaspace = 0;
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


// M_PARA_DIA ��Ϣ�������


void M_PARA_DIA::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void M_PARA_DIA::OnEnChangeEdit3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void M_PARA_DIA::OnEnUpdateLine()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// �������Խ� EM_SETEVENTMASK ��Ϣ���͵��ÿؼ���
	// ͬʱ�� ENM_UPDATE ��־�������㵽 lParam �����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void M_PARA_DIA::OnEnUpdateCharac()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// �������Խ� EM_SETEVENTMASK ��Ϣ���͵��ÿؼ���
	// ͬʱ�� ENM_UPDATE ��־�������㵽 lParam �����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void M_PARA_DIA::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	UpdateData(false);
	CDialogEx::OnOK();
}
