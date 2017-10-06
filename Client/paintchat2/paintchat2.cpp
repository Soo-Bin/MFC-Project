
// paintchat2.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "paintchat2.h"
#include "MainFrm.h"

#include "paintchat2Doc.h"
#include "paintchat2View.h"
#include "RightView.h"
#include "MyPacket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cpaintchat2App

BEGIN_MESSAGE_MAP(Cpaintchat2App, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &Cpaintchat2App::OnAppAbout)
	// ǥ�� ������ ���ʷ� �ϴ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// ǥ�� �μ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// Cpaintchat2App ����

Cpaintchat2App::Cpaintchat2App()
	: pFrame(NULL)
	, pDoc(NULL)
	, pView(NULL)
	, pCView(0)
{
	// �ٽ� ���� ������ ����
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���� ���α׷��� ���� ��� ��Ÿ�� ������ ����Ͽ� ������ ���(/clr):
	//     1) �� �߰� ������ �ٽ� ���� ������ ������ ����� �۵��ϴ� �� �ʿ��մϴ�.
	//     2) ������Ʈ���� �����Ϸ��� System.Windows.Forms�� ���� ������ �߰��ؾ� �մϴ�.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: �Ʒ� ���� ���α׷� ID ���ڿ��� ���� ID ���ڿ��� �ٲٽʽÿ�(����).
	// ���ڿ��� ���� ����: CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("paintchat2.AppID.NoVersion"));

	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}

// ������ Cpaintchat2App ��ü�Դϴ�.

Cpaintchat2App theApp;


// Cpaintchat2App �ʱ�ȭ

BOOL Cpaintchat2App::InitInstance()
{
	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControlsEx()�� �ʿ��մϴ�. 
	// InitCommonControlsEx()�� ������� ������ â�� ���� �� �����ϴ�.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ���� ���α׷����� ����� ��� ���� ��Ʈ�� Ŭ������ �����ϵ���
	// �� �׸��� �����Ͻʽÿ�.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// OLE ���̺귯���� �ʱ�ȭ�մϴ�.
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// RichEdit ��Ʈ���� ����Ϸ���  AfxInitRichEdit2()�� �־�� �մϴ�.	
	// AfxInitRichEdit2();

	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
	// ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));
	LoadStdProfileSettings(4);  // MRU�� �����Ͽ� ǥ�� INI ���� �ɼ��� �ε��մϴ�.


	// ���� ���α׷��� ���� ���ø��� ����մϴ�.  ���� ���ø���
	//  ����, ������ â �� �� ������ ���� ������ �մϴ�.
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(Cpaintchat2Doc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ������ â�Դϴ�.
		RUNTIME_CLASS(Cpaintchat2View));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// ǥ�� �� ���, DDE, ���� ���⿡ ���� ������� ���� �м��մϴ�.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// ����ٿ� ������ ����� ����ġ�մϴ�.
	// ���� ���α׷��� /RegServer, /Register, /Unregserver �Ǵ� /Unregister�� ���۵� ��� FALSE�� ��ȯ�մϴ�.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// â �ϳ��� �ʱ�ȭ�Ǿ����Ƿ� �̸� ǥ���ϰ� ������Ʈ�մϴ�.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

int Cpaintchat2App::ExitInstance()
{
	//TODO: �߰��� �߰� ���ҽ��� ó���մϴ�.
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// Cpaintchat2App �޽��� ó����


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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

// ��ȭ ���ڸ� �����ϱ� ���� ���� ���α׷� ����Դϴ�.
void Cpaintchat2App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// Cpaintchat2App �޽��� ó����

void Cpaintchat2App::CleanUp()
{
	if (m_pServer)
		delete m_pServer;
	if (m_pClient)
		delete m_pClient;
}


void Cpaintchat2App::Connect(CString strIP)
{
	m_pClient = new CClientSock;
	m_pClient->Create();
	m_pClient->Connect(strIP, 7777);

	pFrame = (CMainFrame*)AfxGetMainWnd();
	pDoc = (Cpaintchat2Doc*)pFrame->GetActiveDocument();
	pView = (Cpaintchat2View*)pFrame->m_wndSplitter.GetPane(0, 0);

	m_pSend = new CDrawSock;
	m_pSend->Create();
	m_pSend->Connect(strIP, 7776);
	
	m_pName = new CNameSock;
	m_pName->Create();
	m_pName->Connect(strIP, 7775);
}

void Cpaintchat2App::ReceiveNotice()
{
	wchar_t temp[MAX_PATH];
	m_pName->Receive(temp, sizeof(temp));
	CString str;
	str.Format(_T("%s"), temp);
	((CChattingView*)m_pMainWnd)->ReceiveNotice(str);
}

void Cpaintchat2App::ReceiveData()
{
	wchar_t temp[MAX_PATH];
	m_pClient->Receive(temp, sizeof(temp));
	CString str;
	str.Format(_T("%s"), temp);
	((CChattingView*)m_pMainWnd)->ReceiveData(str);

}

void Cpaintchat2App::SendName(CString strData)
{
	if (m_pName) {
		m_pName->Send((LPCTSTR)strData, sizeof(TCHAR)*(strData.GetLength() + 1));
	}
}
void Cpaintchat2App::SendData(CString strData)
{
	if (m_pClient) {
		m_pClient->Send((LPCTSTR)strData, sizeof(TCHAR)*(strData.GetLength() + 1));
	}
}


void Cpaintchat2App::CloseChild()
{
	delete m_pClient;
	delete m_pSend;
	delete m_pName;
	m_pSend = NULL;
	m_pClient = NULL;
	m_pName = NULL;
}

void Cpaintchat2App::SendDraw(DWORD Event, WORD Element, CPoint StartPoint, CPoint EndPoint, COLORREF PenColor, UINT PenSize, UINT EraseSize)
{
	if (m_pSend) 
	{
		MyPacket *mp = new MyPacket();

		mp->EnPacket(&Event, sizeof(DWORD));
		mp->EnPacket(&Element, sizeof(WORD));
		mp->EnPacket(&StartPoint, sizeof(CPoint));
		mp->EnPacket(&EndPoint, sizeof(CPoint));
		mp->EnPacket(&PenColor, sizeof(COLORREF));
		mp->EnPacket(&PenSize, sizeof(UINT));
		mp->EnPacket(&EraseSize, sizeof(UINT));

		m_pSend->Send(mp->GetBase(), mp->GetSize());

		delete mp;
	}

}

void Cpaintchat2App::ReceiveDraw()
{
	char *buf = new char[sizeof(DATA)];
	m_pSend->Receive(buf, sizeof(DATA));

	DATA data;

	data.Event = *(DWORD*)buf;
	data.StartPoint = *(CPoint*)(buf + sizeof(data.Event) + sizeof(data.Element));
	data.EndPoint = *(CPoint*)(buf + sizeof(data.Event) + sizeof(data.Element) + sizeof(data.StartPoint));

	pFrame = (CMainFrame*)AfxGetMainWnd();
	pDoc = (Cpaintchat2Doc*)pFrame->GetActiveDocument();
	pView = (Cpaintchat2View*)pFrame->m_wndSplitter.GetPane(0, 0);
	pCView = (CpaintchatChildView*)pFrame->m_wndSplitter.GetPane(0, 0);

	if (data.Event == EVENT_LBUTTONDOWN)
	{
		pDoc->m_Element = *(WORD*)(buf + sizeof(data.Event));
		pDoc->m_PenColor = *(COLORREF*)(buf + sizeof(data.Event) + sizeof(data.Element) + sizeof(data.StartPoint) + sizeof(data.EndPoint));
		pDoc->m_PenSize = *(UINT*)(buf + sizeof(data.Event) + sizeof(data.Element) + sizeof(data.StartPoint) + sizeof(data.EndPoint) + sizeof(data.PenColor));
		pDoc->m_EraseSize = *(UINT*)(buf + sizeof(data.Event) + sizeof(data.Element) + sizeof(data.StartPoint) + sizeof(data.EndPoint) + sizeof(data.PenColor) + sizeof(data.PenSize));
	}
	delete[] buf;

	switch (data.Event)
	{
	case EVENT_LBUTTONDOWN:
		((CpaintchatChildView*)pCView)->OnLButtonDown(0, data.StartPoint);
		break;

	case EVENT_LBUTTONUP:
		((CpaintchatChildView*)pCView)->OnLButtonUp(0, data.EndPoint);
		break;

	case EVENT_MOUSEMOVE:
		((CpaintchatChildView*)pCView)->OnMouseMove(MK_LBUTTON, data.EndPoint);
		break;

	case  EVENT_REMOVE:
		pView->OnEditUndo();
	}
}

