
// Notepad.cpp : 定义应用程序的类行为。
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


// CNotepadApp 构造

CNotepadApp::CNotepadApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则: 
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("Notepad.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CNotepadApp 对象

CNotepadApp theApp;


// CNotepadApp 初始化

BOOL CNotepadApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要 AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));


	// 若要创建主窗口，此代码将创建新的框架窗口
	// 对象，然后将其设置为应用程序的主窗口对象
	CMainFrame* pFrame = new CMainFrame;
	mainp = pFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// 创建并加载框架及其资源
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);





	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}

int CNotepadApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// CNotepadApp 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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

// 用于运行对话框的应用程序命令
void CNotepadApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CNotepadApp 消息处理程序





void CNotepadApp::OnAlignLeft()
{
	// TODO: 在此添加命令处理程序代码
	change_align(mainp->m_wndView.m_text->ALEFT);
}


void CNotepadApp::OnAlignCenter()
{
	// TODO: 在此添加命令处理程序代码
	change_align(mainp->m_wndView.m_text->ACENTER);
}




void CNotepadApp::OnAlignRight()
{
	// TODO: 在此添加命令处理程序代码
	change_align(mainp->m_wndView.m_text->ARIGHT);
}


void CNotepadApp::OnAlignDistribute()
{
	// TODO: 在此添加命令处理程序代码
	change_align(mainp->m_wndView.m_text->ADISTRIBUTED);
}


void CNotepadApp::OnOpen()
{
	// TODO: 在此添加命令处理程序代码
	BOOL isOpen = TRUE;     //是否打开(否则为保存)  
	CString defaultDir = L"C:";   //默认打开的文件路径  
	CString fileName = L"";         //默认打开的文件名  
	CString filter = L"文件 (*.orz;*.txt)|*.orz;*.txt||";   //文件过虑的类型  
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_READONLY, filter, NULL);
	INT_PTR result = openFileDlg.DoModal();
	CString filePath;
	if (result == IDOK) {
		filePath = openFileDlg.GetPathName();
	}

	//TODO:调用接口
}


void CNotepadApp::OnClose()
{
	// TODO: 在此添加命令处理程序代码
	BOOL isOpen = FALSE;        //是否打开(否则为保存)  
	CString defaultDir = L"C:\\";   //默认打开的文件路径  
	CString fileName = L"";         //默认打开的文件名  
	CString filter = L"文件 (*.orz;*.txt)|*.orz;*.txt||";   //文件过虑的类型  
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
	INT_PTR result = openFileDlg.DoModal();
	CString filePath;
	if (result == IDOK) {
		filePath = openFileDlg.GetPathName();
	}
}
