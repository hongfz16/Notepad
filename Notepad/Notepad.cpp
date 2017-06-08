
// Notepad.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Notepad.h"
#include "MainFrm.h"
#include "M_PARA_DIA.h"
#include "kernal.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNotepadApp

BEGIN_MESSAGE_MAP(CNotepadApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CNotepadApp::OnAppAbout)
	ON_COMMAND(ID_FONT,&CNotepadApp::OnFont)
	ON_COMMAND(ID_PARA,&CNotepadApp::OnPara)
	ON_COMMAND(ID_EDIT_CUT,&CNotepadApp::OnCut)
	ON_COMMAND(ID_EDIT_COPY,&CNotepadApp::OnCopy)
	ON_COMMAND(ID_EDIT_PASTE,&CNotepadApp::OnPaste)
	ON_COMMAND(ID_ALIGN_LEFT, &CNotepadApp::OnAlignLeft)
	ON_COMMAND(ID_ALIGN_CENTER, &CNotepadApp::OnAlignCenter)
	ON_COMMAND(ID_ALIGN_RIGHT, &CNotepadApp::OnAlignRight)
	ON_COMMAND(ID_ALIGN_DISTRIBUTE, &CNotepadApp::OnAlignDistribute)
	ON_COMMAND(ID_OPEN, &CNotepadApp::OnOpen)
	ON_COMMAND(ID_CLOSE, &CNotepadApp::OnClose)
END_MESSAGE_MAP()


// CNotepadApp ����

CNotepadApp::CNotepadApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���: 
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("Notepad.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CNotepadApp ����

CNotepadApp theApp;


// CNotepadApp ��ʼ��

BOOL CNotepadApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));


	// ��Ҫ���������ڣ��˴��뽫�����µĿ�ܴ���
	// ����Ȼ��������ΪӦ�ó���������ڶ���
	CMainFrame* pFrame = new CMainFrame;
	mainp = pFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// ���������ؿ�ܼ�����Դ
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);





	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}

int CNotepadApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// CNotepadApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

void CNotepadApp::OnFont()
{
	LOGFONT lf;
	CFontDialog dlg;
	COLORERF col;
	if (dlg.DoModal() == IDOK)
	{
		dlg.GetCurrentFont(&lf);
		col = dlg.GetColor();
		if (mainp->m_wndView.m_text->select.sp == NULL && mainp->m_wndView.m_text->select.ep == NULL)
		{
			mainp->m_wndView.m_text->set_curfont(lf);
			mainp->m_wndView.need_recompute = true;
			mainp->m_wndView.m_changed();
			mainp->m_wndView.curchanged();
		}
		else
		{
			mainp->m_wndView.m_text->set_select_font(lf);
			mainp->m_wndView.m_text->set_select_color(col);
			mainp->m_wndView.need_recompute = true;
			mainp->m_wndView.m_changed();
			mainp->m_wndView.curchanged();
		}
	}
	
}

void CNotepadApp::OnPara()
{
	M_PARA_DIA paraDlg;
	paraDlg.DoModal();
	if (mainp->m_wndView.m_text->select.sp == NULL && mainp->m_wndView.m_text->select.ep == NULL)
	{
		//TODO:set_cru_l/cspace???
	}
	else
	{
		mainp->m_wndView.m_text->set_select_lspace(paraDlg.m_linespace);
		mainp->m_wndView.m_text->set_select_cspace(paraDlg.m_charaspace);
		mainp->m_wndView.need_recompute = true;
		mainp->m_wndView.m_changed();
	}
}

void CNotepadApp::OnCut()
{
	SITEXT* b_text = mainp->m_wndView.m_text;
	m_cutBoard = b_text->select;
	b_text->del_select();
}

void CNotepadApp::OnCopy()
{
	SITEXT* b_text = mainp->m_wndView.m_text;
	m_cutBoard = b_text->select;
}

void CNotepadApp::OnPaste()
{
	//TODO:insert a text range
}

// �������жԻ����Ӧ�ó�������
void CNotepadApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CNotepadApp ��Ϣ�������





void CNotepadApp::OnAlignLeft()
{
	// TODO: �ڴ���������������
	change_align(mainp->m_wndView.m_text->ALEFT);
}


void CNotepadApp::OnAlignCenter()
{
	// TODO: �ڴ���������������
	change_align(mainp->m_wndView.m_text->ACENTER);
}




void CNotepadApp::OnAlignRight()
{
	// TODO: �ڴ���������������
	change_align(mainp->m_wndView.m_text->ARIGHT);
}


void CNotepadApp::OnAlignDistribute()
{
	// TODO: �ڴ���������������
	change_align(mainp->m_wndView.m_text->ADISTRIBUTED);
}


void CNotepadApp::OnOpen()
{
	// TODO: �ڴ���������������
	BOOL isOpen = TRUE;     //�Ƿ��(����Ϊ����)  
	CString defaultDir = L"C:";   //Ĭ�ϴ򿪵��ļ�·��  
	CString fileName = L"";         //Ĭ�ϴ򿪵��ļ���  
	CString filter = L"�ļ� (*.orz;*.txt)|*.orz;*.txt||";   //�ļ����ǵ�����  
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_READONLY, filter, NULL);
	INT_PTR result = openFileDlg.DoModal();
	CString filePath;
	if (result == IDOK) {
		filePath = openFileDlg.GetPathName();
	}

	//TODO:���ýӿ�
}


void CNotepadApp::OnClose()
{
	// TODO: �ڴ���������������
	BOOL isOpen = FALSE;        //�Ƿ��(����Ϊ����)  
	CString defaultDir = L"C:\\";   //Ĭ�ϴ򿪵��ļ�·��  
	CString fileName = L"";         //Ĭ�ϴ򿪵��ļ���  
	CString filter = L"�ļ� (*.orz;*.txt)|*.orz;*.txt||";   //�ļ����ǵ�����  
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
	INT_PTR result = openFileDlg.DoModal();
	CString filePath;
	if (result == IDOK) {
		filePath = openFileDlg.GetPathName();
	}
}
