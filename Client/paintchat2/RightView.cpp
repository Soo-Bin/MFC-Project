// RightView.cpp : ���� �����Դϴ�.
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


// CRightView �����Դϴ�.

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


// CRightView �޽��� ó�����Դϴ�.

void CChattingView::OnClickedButtonConnect()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
		AfxMessageBox(_T("������ ������ IP�ּҸ� �Է��ϼ���."));
	}

}


void CChattingView::OnClickedButtonSend()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strSend, strInsert, strName, strPlus, strSpace;
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CChattingView* pRView = (CChattingView*)pFrame->m_wndSplitter.GetPane(0, 1);

	GetDlgItemText(IDC_EDIT, strSend);
	pRView->GetDlgItemText(IDC_EDIT_NAME, strName);
	strPlus.Format(_T("[" + strName + "]: " + strSend));
	strInsert.Format(_T("[��]: %s"), strSend);
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
		message.Format(_T("%s�� �׸�����."), token);
		AfxMessageBox(message);
		message.Format(_T("���� : %s"), token);
		pRView->SetDlgItemText(IDC_STATIC_NAME1, message);
	}

	CString strServerIP;
	strServerIP.Format(_T("Equals Server"));
	if (token == strServerIP) {
		CString message;
		AfxExtractSubString(token, strReceive, 1, '!');
		AfxMessageBox(_T("ù��° �����Դϴ�."));
		pView->Connect = TRUE;
		message.Format(_T("%s�� �׸�����."), token);
		AfxMessageBox(message);
		message.Format(_T("���� : %s"), token);
		pRView->SetDlgItemText(IDC_STATIC_NAME1, message);
	}
	CString strCorrect;
	strCorrect.Format(_T("����"));
	if (strReceive == strCorrect) {
		pView->Connect = TRUE;
		pView->OnBnClickedClear();
	}
	CString strNext;
	strNext.Format(_T("������"));
	if (strReceive == strNext) {
		pView->Connect = FALSE;
		CString message;
		message.Format(_T("���� : "));
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
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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
