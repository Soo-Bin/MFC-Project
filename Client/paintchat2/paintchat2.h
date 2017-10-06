
// paintchat2.h : paintchat2 응용 프로그램에 대한 주 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.

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
// 이 클래스의 구현에 대해서는 paintchat2.cpp을 참조하십시오.
//

class Cpaintchat2App : public CWinApp
{
public:
	Cpaintchat2App();


// 재정의입니다.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 구현입니다.
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
