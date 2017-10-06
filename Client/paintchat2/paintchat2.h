
// paintchat2.h : paintchat2 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.

#include "ServerSock.h"
#include "ClientSock.h"
#include "SendSocket.h"
#include "NameSock.h"

#include "MainFrm.h"
#include "paintchat2Doc.h"
#include "paintchat2View.h"
#include "RightView.h"
#include "CpaintchatChildView.h"

// Cpaintchat2App:
// �� Ŭ������ ������ ���ؼ��� paintchat2.cpp�� �����Ͻʽÿ�.
//

class Cpaintchat2App : public CWinApp
{
public:
	Cpaintchat2App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

public:
	void CleanUp();
	void Connect(CString strIP);
	void ReceiveData();
	void SendData(CString strData);
	void SendName(CString strData);
	void CloseChild();
	CServerSock* m_pServer;
	CClientSock* m_pClient;
	CDrawSock* m_pSend;
	CNameSock* m_pName;
	void SendDraw(DWORD Event, WORD Element, CPoint startPoint, CPoint EndPoint, COLORREF PenColor, UINT PenSize, UINT EraseSize = 50);
	void ReceiveDraw();
	void ReceiveNotice();
	CMainFrame* pFrame;
	Cpaintchat2Doc* pDoc;
	Cpaintchat2View* pView;
	CpaintchatChildView* pCView;
};

extern Cpaintchat2App theApp;
