
// paintchat2.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
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
	// 표준 파일을 기초로 하는 문서 명령입니다.
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// 표준 인쇄 설정 명령입니다.
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// Cpaintchat2App 생성

Cpaintchat2App::Cpaintchat2App()
	: pFrame(NULL)
	, pDoc(NULL)
	, pView(NULL)
	, pCView(0)
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
	SetAppID(_T("paintchat2.AppID.NoVersion"));

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}

// 유일한 Cpaintchat2App 개체입니다.

Cpaintchat2App theApp;


// Cpaintchat2App 초기화

BOOL Cpaintchat2App::InitInstance()
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
		RUNTIME_CLASS(Cpaintchat2Doc),
		RUNTIME_CLASS(CMainFrame),       // 주 SDI 프레임 창입니다.
		RUNTIME_CLASS(Cpaintchat2View));
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

int Cpaintchat2App::ExitInstance()
{
	//TODO: 추가한 추가 리소스를 처리합니다.
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// Cpaintchat2App 메시지 처리기


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
void Cpaintchat2App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// Cpaintchat2App 메시지 처리기

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

