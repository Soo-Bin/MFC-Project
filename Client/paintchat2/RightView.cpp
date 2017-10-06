// RightView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "paintchat2.h"
#include "RightView.h"
#include "afxsock.h"
#include "MainFrm.h"

#include "paintchat2View.h"
// CRightView

IMPLEMENT_DYNCREATE(CChattingView, CFormView)

CChattingView::CChattingView()
	: CFormView(IDD_FORMVIEW)
	, m_nChatMode(0)
	, m_strMyIP(_T(""))
	, m_strOtherIP(_T(""))
	, m_strName(_T(""))
{

}

CChattingView::~CChattingView()
{
}

void CChattingView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS_SERVER, m_IPAdress);
	DDX_Control(pDX, IDC_LIST, m_listChat);
	//  DDX_Text(pDX, IDC_STATIC_NAME1, m_strSatic);
}

BEGIN_MESSAGE_MAP(CChattingView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CChattingView::OnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CChattingView::OnClickedButtonSend)
END_MESSAGE_MAP()


// CRightView 진단입니다.

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


// CRightView 메시지 처리기입니다.

void CChattingView::OnClickedButtonConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();

	CString strIP, strName;
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CChattingView* pRView = (CChattingView*)pFrame->m_wndSplitter.GetPane(0, 1);

	pRView->GetDlgItemText(IDC_IPADDRESS_SERVER, strIP);
	pRView->GetDlgItemText(IDC_EDIT_NAME, strName);

	if (strIP != _T("0.0.0.0")) {
		GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);
		GetDlgItem(IDC_IPADDRESS_SERVER)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_NAME)->EnableWindow(FALSE);
		((Cpaintchat2App*)AfxGetApp())->Connect(strIP);
		((Cpaintchat2App*)AfxGetApp())->SendName(strName);
		pRView->m_strOtherIP = strIP;
		SetDlgItemText(IDC_BUTTON_CONNECT, _T("Success!"));
	}
	else {
		AfxMessageBox(_T("접속할 서버의 IP주소를 입력하세요."));
	}

}


void CChattingView::OnClickedButtonSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strSend, strInsert, strName, strPlus, strSpace;
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CChattingView* pRView = (CChattingView*)pFrame->m_wndSplitter.GetPane(0, 1);

	GetDlgItemText(IDC_EDIT, strSend);
	pRView->GetDlgItemText(IDC_EDIT_NAME, strName);
	strPlus.Format(_T("[" + strName + "]: " + strSend));
	strInsert.Format(_T("[나]: %s"), strSend);
	strSpace.Format(_T(" "));
	theApp.SendName(strSpace);
	theApp.SendData(strPlus);
	int sel = pRView->m_listChat.InsertString(-1, strInsert);
	pRView->m_listChat.SetCurSel(sel);
	SetDlgItemText(IDC_EDIT, _T(""));
}


void CChattingView::ReceiveData(CString strReceive)
{
	CString strInsert;
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CChattingView* pRView = (CChattingView*)pFrame->m_wndSplitter.GetPane(0, 1);

	strInsert.Format(_T("%s"), strReceive);
	int sel = pRView->m_listChat.InsertString(-1, strInsert);
	pRView->m_listChat.SetCurSel(sel);
}

void CChattingView::ReceiveNotice(CString strReceive)
{
	CString strInsert;
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CChattingView* pRView = (CChattingView*)pFrame->m_wndSplitter.GetPane(0, 1);
	Cpaintchat2View* pView = (Cpaintchat2View*)pFrame->m_wndSplitter.GetPane(0, 0);

	CString token;
	AfxExtractSubString(token, strReceive, 0, '!');
	if (token == "nw") {
		CString message;
		AfxExtractSubString(token, strReceive, 1, '!');
		message.Format(_T("%s를 그리세요."), token);
		AfxMessageBox(message);
		message.Format(_T("정답 : %s"), token);
		pRView->SetDlgItemText(IDC_STATIC_NAME1, message);
	}

	CString strServerIP;
	strServerIP.Format(_T("Equals Server"));
	if (token == strServerIP) {
		CString message;
		AfxExtractSubString(token, strReceive, 1, '!');
		AfxMessageBox(_T("첫번째 순서입니다."));
		pView->Connect = TRUE;
		message.Format(_T("%s를 그리세요."), token);
		AfxMessageBox(message);
		message.Format(_T("정답 : %s"), token);
		pRView->SetDlgItemText(IDC_STATIC_NAME1, message);
	}
	CString strCorrect;
	strCorrect.Format(_T("정답"));
	if (strReceive == strCorrect) {
		pView->Connect = TRUE;
		pView->OnBnClickedClear();
	}
	CString strNext;
	strNext.Format(_T("다음턴"));
	if (strReceive == strNext) {
		pView->Connect = FALSE;
		CString message;
		message.Format(_T("정답 : "));
		pRView->SetDlgItemText(IDC_STATIC_NAME1, message);
		pView->OnBnClickedClear();
	}
}

void CChattingView::Accept(CString strSock)
{
	m_strOtherIP = strSock;
}

BOOL CChattingView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN) {
			if (pMsg->hwnd == GetDlgItem(IDC_EDIT)->GetSafeHwnd()) {
				OnClickedButtonSend();
			}
			if (pMsg->hwnd == GetDlgItem(IDC_EDIT_NAME)->GetSafeHwnd()) {
				OnClickedButtonConnect();
			}

			return FALSE;
		}
	}
	return CFormView::PreTranslateMessage(pMsg);
}
