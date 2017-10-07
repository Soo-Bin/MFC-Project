#pragma once



// CChattingView 폼 뷰입니다.

class CChattingView : public CFormView
{
	DECLARE_DYNCREATE(CChattingView)

protected:
	CChattingView();           // 동적 만들기에 사용되는 protected 생성자입니다.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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


