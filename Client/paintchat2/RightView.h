#pragma once



// CRightView �� ���Դϴ�.

class CChattingView : public CFormView
{
	DECLARE_DYNCREATE(CChattingView)

protected:
	CChattingView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CChattingView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CIPAddressCtrl m_IPAdress;
	int m_nChatMode;
	CString m_strMyIP;
	CString m_strOtherIP;
	CString m_strName;
	afx_msg void OnClickedButtonConnect();
	afx_msg void OnClickedButtonSend();
	void ReceiveData(CString strReceive);
	void ReceiveNotice(CString strReceive);
	void Accept(CString strSock);
	CListBox m_listChat;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
//	CString m_strSatic;
};


