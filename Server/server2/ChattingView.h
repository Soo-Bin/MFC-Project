#pragma once



// CChattingView �� ���Դϴ�.

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
	CIPAddressCtrl m_IPAddress;
	CListBox m_listChat;
	CString m_strMyIP;
	CString m_strName;
	void ReceiveData(CString strReceive);
	void GetName(CString strName, CString strIP);
	void SendStart(CString strIP);
	afx_msg void OnClickedButtonOpen();
	CString m_CatchWord;
	void Accept(CString strIP);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


