
// server2.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "server2.h"
#include "MainFrm.h"
#include "ChattingView.h"

//#include "server2.h"
#include "server2Doc.h"
#include "server2View.h"
#include "Cserver2ChildView.h"
#include "mysql.h"

#define DB_ADDRESS "localhost:3306"
#define DB_ID "root"
#define DB_PASS "0000"
#define DB_NAME "mfc_catchmind"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cserver2App

BEGIN_MESSAGE_MAP(Cserver2App, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &Cserver2App::OnAppAbout)
	// ǥ�� ������ ���ʷ� �ϴ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// ǥ�� �μ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// Cserver2App ����

Cserver2App::Cserver2App()
	: pFrame(NULL)
	, pDoc(NULL)
	, pView(NULL)
	, pCView(NULL)
	, m_pDrawServer(NULL)
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
	SetAppID(_T("server2.AppID.NoVersion"));

	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}

// ������ Cserver2App ��ü�Դϴ�.

Cserver2App theApp;


// Cserver2App �ʱ�ȭ

BOOL Cserver2App::InitInstance()
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
		RUNTIME_CLASS(Cserver2Doc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ������ â�Դϴ�.
		RUNTIME_CLASS(Cserver2View));
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

int Cserver2App::ExitInstance()
{
	//TODO: �߰��� �߰� ���ҽ��� ó���մϴ�.
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// Cserver2App �޽��� ó����


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
void Cserver2App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// Cserver2App �޽��� ó����

//���� �� �ʱ�ȭ �۾�
void Cserver2App::InitServer()
{
	m_pServer = new CServerSock;
	m_pServer->Create(7777);
	m_pServer->Listen();
}
void Cserver2App::InitDrawServer()
{
	m_pDrawServer = new CDrawServerSock;
	m_pDrawServer->Create(7776);
	m_pDrawServer->Listen();
}
void Cserver2App::InitNameServer()
{
	m_pNameServer = new CNameServerSock;
	m_pNameServer->Create(7775);
	m_pNameServer->Listen();
}

//����
void Cserver2App::Accept()
{
	CClientSock* pClient = new CClientSock;
	POSITION pos = m_ClientList.GetHeadPosition();

	if (m_pServer->Accept(*pClient)) {
		m_ClientList.AddTail(pClient);	//����Ʈ�� Ŭ���̾�Ʈ ������ �߰�
	}
	CString strSock;
	UINT nPort;
	pClient->GetPeerName(strSock, nPort);
	((CChattingView*)m_pMainWnd)->Accept(strSock);

}
void Cserver2App::AcceptDraw()
{
	CDrawSock* pClient = new CDrawSock;
	POSITION pos = m_DrawList.GetHeadPosition();

	if (m_pDrawServer->Accept(*pClient)) {
		m_DrawList.AddTail(pClient);	//����Ʈ�� Ŭ���̾�Ʈ ������ �߰�
	}
}
void Cserver2App::AcceptName()
{
	CNameSock* pClient = new CNameSock;
	POSITION pos = m_DrawList.GetHeadPosition();

	if (m_pNameServer->Accept(*pClient)) {
		m_NameList.AddTail(pClient);	//����Ʈ�� Ŭ���̾�Ʈ ������ �߰�
	}
}

void Cserver2App::CleanUp()
{
	if (m_pServer)
		delete m_pServer;
	if (m_pClient)
		delete m_pClient;
}

void Cserver2App::ReceiveData(CClientSock* pSock)
{
	wchar_t temp[MAX_PATH];
	CString str;

	CClientSock* pClient;
	CClientSock* pOtherClient;
	POSITION pos = m_ClientList.Find(pSock);
	POSITION pos1 = m_ClientList.GetHeadPosition();

	if (pos != NULL) {
		pClient = ((CClientSock*)m_ClientList.GetAt(pos));
		pClient->Receive(temp, sizeof(temp));
		str.Format(_T("%s"), temp);
		((CChattingView*)m_pMainWnd)->ReceiveData(str);
	}
	
	while (pos1 != NULL) {
		if (pos != pos1) {
			pOtherClient = ((CClientSock*)m_ClientList.GetAt(pos1));
			pOtherClient->Send((LPCTSTR)str, sizeof(TCHAR)*(str.GetLength() + 1));
		}
		m_ClientList.GetNext(pos1);
	}
}

void Cserver2App::ReceiveDraw(CDrawSock * pSock)
{
	char *buf = new char[sizeof(DATA)];

	CDrawSock* pClient;
	POSITION pos = m_DrawList.Find(pSock);
	POSITION pos_Head = m_DrawList.GetHeadPosition();

	DATA data;
	if (pos != NULL) {
		pClient = ((CDrawSock*)m_DrawList.GetAt(pos));
		pClient->Receive(buf, sizeof(DATA));

		data.Event = *(DWORD*)buf;
		data.StartPoint = *(CPoint*)(buf + sizeof(data.Event) + sizeof(data.Element));
		data.EndPoint = *(CPoint*)(buf + sizeof(data.Event) + sizeof(data.Element) + sizeof(data.StartPoint));

		pFrame = (CMainFrame*)AfxGetMainWnd();
		pDoc = (Cserver2Doc*)pFrame->GetActiveDocument();
		pView = (Cserver2View*)pFrame->m_wndSplitter.GetPane(0, 0);
		pCView = (Cserver2ChildView*)pFrame->m_wndSplitter.GetPane(0, 0);

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
			((Cserver2ChildView*)pCView)->OnLButtonDown(0, data.StartPoint);
			break;

		case EVENT_LBUTTONUP:
			((Cserver2ChildView*)pCView)->OnLButtonUp(0, data.EndPoint);
			break;

		case EVENT_MOUSEMOVE:
			((Cserver2ChildView*)pCView)->OnMouseMove(MK_LBUTTON, data.EndPoint);
			break;

		case  EVENT_REMOVE:
			pView->OnEditUndo();
		}
	}
}

void Cserver2App::ReceiveName(CNameSock* pSock)
{
	wchar_t temp[MAX_PATH];
	CString str;

	CNameSock* pName;
	POSITION pos = m_NameList.Find(pSock);

	((Cserver2App*)AfxGetApp())->m_pos = pos;

	if (pos != NULL) {
		pName = ((CNameSock*)m_NameList.GetAt(pos));
		pName->Receive(temp, sizeof(temp));
		str.Format(_T("%s"), temp);
		CString strSock;
		UINT nPort;
		pName->GetPeerName(strSock, nPort);
		((CChattingView*)m_pMainWnd)->GetName(str, strSock);
	}
}

void Cserver2App::SendNotice(CString strData)
{
	CNameSock* pClient;

	pClient = ((CNameSock*)m_NameList.GetAt(m_pos));
	pClient->Send((LPCTSTR)strData, sizeof(TCHAR)*(strData.GetLength() + 1));
}

void Cserver2App::SendData(CString strData)
{
	CClientSock* pClient;
	POSITION pos = m_ClientList.GetHeadPosition();

	while (pos != NULL) {
		pClient = ((CClientSock*)m_ClientList.GetAt(pos));
		pClient->Send((LPCTSTR)strData, sizeof(TCHAR)*(strData.GetLength() + 1));
		m_ClientList.GetNext(pos);
	}
}
void Cserver2App::SendNext(CString strData)
{
	CNameSock* pOtherClient;
	POSITION pos = m_NameList.GetHeadPosition();

	while (pos != NULL) {
		if (pos != m_pos) {
			pOtherClient = ((CNameSock*)m_NameList.GetAt(pos));
			pOtherClient->Send((LPCTSTR)strData, sizeof(TCHAR)*(strData.GetLength() + 1));
		}
		m_NameList.GetNext(pos);
	}
}
void Cserver2App::SendDraw(DWORD Event, WORD Element, CPoint StartPoint, CPoint EndPoint, COLORREF PenColor, UINT PenSize, UINT EraseSize)
{
	CDrawSock* pClient;
	POSITION pos = m_DrawList.GetHeadPosition();

	while (pos != NULL)
	{

		pClient = ((CDrawSock*)m_DrawList.GetAt(pos));
		
		MyPacket *mp = new MyPacket();

		mp->EnPacket(&Event, sizeof(DWORD));
		mp->EnPacket(&Element, sizeof(WORD));
		mp->EnPacket(&StartPoint, sizeof(CPoint));
		mp->EnPacket(&EndPoint, sizeof(CPoint));
		mp->EnPacket(&PenColor, sizeof(COLORREF));
		mp->EnPacket(&PenSize, sizeof(UINT));
		mp->EnPacket(&EraseSize, sizeof(UINT));

		pClient->Send(mp->GetBase(), mp->GetSize());

		delete mp;

		m_DrawList.GetNext(pos);
	}

}
void Cserver2App::CloseChild(CClientSock* pSock)
{
	CClientSock* pClient;
	POSITION pos = m_ClientList.Find(pSock);
	if (pos != NULL) {
		pClient = ((CClientSock*)m_ClientList.GetAt(pos));
		m_ClientList.RemoveAt(pos);
		delete pClient;
	}
}

void Cserver2App::Close(CDrawSock * pSock)
{
	CDrawSock* pClient;
	POSITION pos = m_DrawList.Find(pSock);
	if (pos != NULL) {
		pClient = ((CDrawSock*)m_DrawList.GetAt(pos));
		m_DrawList.RemoveAt(pos);
		delete pClient;
	}
}
void Cserver2App::CloseName(CNameSock * pSock)
{
	CNameSock* pClient;
	POSITION pos = m_NameList.Find(pSock);
	if (pos != NULL) {
		pClient = ((CNameSock*)m_NameList.GetAt(pos));
		m_NameList.RemoveAt(pos);
		delete pClient;
	}
}


