
// server2.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
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
	// 표준 파일을 기초로 하는 문서 명령입니다.
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// 표준 인쇄 설정 명령입니다.
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// Cserver2App 생성

Cserver2App::Cserver2App()
	: pFrame(NULL)
	, pDoc(NULL)
	, pView(NULL)
	, pCView(NULL)
	, m_pDrawServer(NULL)
{
	// 다시 시작 관리자 지원
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 응용 프로그램을 공용 언어 런타임 지원을 사용하여 빌드한 경우(/clr):
	//     1) 이 추가 설정은 다시 시작 관리자 지원이 제대로 작동하는 데 필요합니다.
	//     2) 프로젝트에서 빌드하려면 System.Windows.Forms에 대한 참조를 추가해야 합니다.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 아래 응용 프로그램 ID 문자열을 고유 ID 문자열로 바꾸십시오(권장).
	// 문자열에 대한 서식: CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("server2.AppID.NoVersion"));

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}

// 유일한 Cserver2App 개체입니다.

Cserver2App theApp;


// Cserver2App 초기화

BOOL Cserver2App::InitInstance()
{
	// 응용 프로그램 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다. 
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// OLE 라이브러리를 초기화합니다.
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// RichEdit 컨트롤을 사용하려면  AfxInitRichEdit2()가 있어야 합니다.	
	// AfxInitRichEdit2();

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 응용 프로그램 마법사에서 생성된 응용 프로그램"));
	LoadStdProfileSettings(4);  // MRU를 포함하여 표준 INI 파일 옵션을 로드합니다.


	// 응용 프로그램의 문서 템플릿을 등록합니다.  문서 템플릿은
	//  문서, 프레임 창 및 뷰 사이의 연결 역할을 합니다.
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(Cserver2Doc),
		RUNTIME_CLASS(CMainFrame),       // 주 SDI 프레임 창입니다.
		RUNTIME_CLASS(Cserver2View));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// 표준 셸 명령, DDE, 파일 열기에 대한 명령줄을 구문 분석합니다.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// 명령줄에 지정된 명령을 디스패치합니다.
	// 응용 프로그램이 /RegServer, /Register, /Unregserver 또는 /Unregister로 시작된 경우 FALSE를 반환합니다.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 창 하나만 초기화되었으므로 이를 표시하고 업데이트합니다.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

int Cserver2App::ExitInstance()
{
	//TODO: 추가한 추가 리소스를 처리합니다.
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// Cserver2App 메시지 처리기


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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

// 대화 상자를 실행하기 위한 응용 프로그램 명령입니다.
void Cserver2App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// Cserver2App 메시지 처리기

//소켓 및 초기화 작업
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

//접속
void Cserver2App::Accept()
{
	CClientSock* pClient = new CClientSock;
	POSITION pos = m_ClientList.GetHeadPosition();

	if (m_pServer->Accept(*pClient)) {
		m_ClientList.AddTail(pClient);	//리스트에 클라이언트 포인터 추가
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
		m_DrawList.AddTail(pClient);	//리스트에 클라이언트 포인터 추가
	}
}
void Cserver2App::AcceptName()
{
	CNameSock* pClient = new CNameSock;
	POSITION pos = m_DrawList.GetHeadPosition();

	if (m_pNameServer->Accept(*pClient)) {
		m_NameList.AddTail(pClient);	//리스트에 클라이언트 포인터 추가
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


