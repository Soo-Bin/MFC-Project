// ChattingView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "server2.h"
#include "ChattingView.h"
#include "MainFrm.h"
#include "string.h"

// CChattingView

IMPLEMENT_DYNCREATE(CChattingView, CFormView)

CChattingView::CChattingView()
	: CFormView(IDD_FORMVIEW)
	, m_strMyIP(_T(""))
	, m_CatchWord(_T(""))
{

}

CChattingView::~CChattingView()
{
}

void CChattingView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS_SERVER, m_IPAddress);
	DDX_Control(pDX, IDC_LIST, m_listChat);
}

BEGIN_MESSAGE_MAP(CChattingView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CChattingView::OnClickedButtonOpen)
END_MESSAGE_MAP()


// CChattingView 진단입니다.

#ifdef _DEBUG
void CChattingView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CChattingView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CChattingView 메시지 처리기입니다.

void CChattingView::GetName(CString strName, CString strIP)
{
	CString strServerIP;
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CChattingView* pRView = (CChattingView*)pFrame->m_wndSplitter.GetPane(0, 1);
	if (strName == " ") {}
	else {
		CString str;
		str.Format(_T("--------[%s]님이 입장하셨습니다.--------"), strName);
		int sel = pRView->m_listChat.InsertString(-1, str);
		pRView->m_listChat.SetCurSel(sel);
		((Cserver2App*)AfxGetApp())->SendData(str);

		pRView->GetDlgItemText(IDC_IPADDRESS_SERVER, strServerIP);
		if (strIP == strServerIP) {
			CString strEquals;
			strEquals.Format(_T("Equals Server!%s!"), pRView->m_CatchWord);
			((Cserver2App*)AfxGetApp())->SendNotice(strEquals);
		}
	}
}

void CChattingView::ReceiveData(CString strReceive)
{
	CString strInsert;
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	Cserver2Doc* pDoc = (Cserver2Doc*)pFrame->GetActiveDocument();
	CChattingView* pRView = (CChattingView*)pFrame->m_wndSplitter.GetPane(0, 1);

	strInsert.Format(_T("%s"), strReceive);
	int sel = pRView->m_listChat.InsertString(-1, strInsert);
	pRView->m_listChat.SetCurSel(sel);

	int cnt = 0;
	CString tmp;

	wchar_t* wc;
	wc = pRView->m_CatchWord.GetBuffer(pRView->m_CatchWord.GetLength());
	pRView->m_CatchWord.ReleaseBuffer(pRView->m_CatchWord.GetLength());
	int ac_num = WideCharToMultiByte(CP_ACP, 0, wc, -1, NULL, 0, NULL, NULL);
	char* ac = new char[ac_num];
	WideCharToMultiByte(CP_ACP, 0, wc, -1, ac, ac_num, 0, 0);

	while (FALSE != AfxExtractSubString(tmp, strReceive, cnt++, ' ')) {
		wchar_t* wc_tmp;
		wc_tmp = tmp.GetBuffer(tmp.GetLength());
		tmp.ReleaseBuffer(tmp.GetLength());
		int ac_num1 = WideCharToMultiByte(CP_ACP, 0, wc_tmp, -1, NULL, 0, NULL, NULL);
		char* ac1 = new char[ac_num1];
		WideCharToMultiByte(CP_ACP, 0, wc_tmp, -1, ac1, ac_num1, 0, 0);

		if (0 == strcmp(ac, ac1)) {
			CString strCorrect;
			strCorrect.Format(_T("--------정답입니다! 정답은 [%s]였습니다.--------"), pRView->m_CatchWord);
			((Cserver2App*)AfxGetApp())->SendData(strCorrect);
			strCorrect.Format(_T("정답"));
			((Cserver2App*)AfxGetApp())->SendNotice(strCorrect);
			strCorrect.Format(_T("다음턴"));
			((Cserver2App*)AfxGetApp())->SendNext(strCorrect);
			pDoc->OnCatchWordDB();
			strCorrect.Format(_T("nw!%s!"), pRView->m_CatchWord);
			((Cserver2App*)AfxGetApp())->SendNotice(strCorrect);
		}
		delete ac1;
	}
	delete ac;
}

void CChattingView::OnClickedButtonOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();

	CString strIP;
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	Cserver2Doc* pDoc = (Cserver2Doc*)pFrame->GetActiveDocument();
	CChattingView* pRView = (CChattingView*)pFrame->m_wndSplitter.GetPane(0, 1);

	pRView->GetDlgItemText(IDC_IPADDRESS_SERVER, strIP);

	if (strIP != _T("0.0.0.0")) {
		((Cserver2App*)AfxGetApp())->InitServer();
		((Cserver2App*)AfxGetApp())->InitDrawServer();
		((Cserver2App*)AfxGetApp())->InitNameServer();
		GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(FALSE);
		GetDlgItem(IDC_IPADDRESS_SERVER)->EnableWindow(FALSE);
	}
	else {
		AfxMessageBox(_T("접속할 서버의 IP주소를 입력하세요."));
	}
	pDoc->OnConnectDB();
}


void CChattingView::Accept(CString strIP)
{
	
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CChattingView* pRView = (CChattingView*)pFrame->m_wndSplitter.GetPane(0, 1);

	CString str;
	str.Format(_T("접속 IP: %s"), strIP);
	int sel = pRView->m_listChat.InsertString(-1, str);
	pRView->m_listChat.SetCurSel(sel);
}

BOOL CChattingView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN) {
			if (pMsg->hwnd == GetDlgItem(IDC_IPADDRESS_SERVER)->GetSafeHwnd()) {
				OnClickedButtonOpen();
			}
			
			return FALSE;
		}
	}
	return CFormView::PreTranslateMessage(pMsg);
}
