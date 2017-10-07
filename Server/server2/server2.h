
// server2.h : server2 응용 프로그램에 대한 주 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.

#include "ClientSock.h"
#include "ServerSock.h"
#include "DrawSock.h"
#include "DrawServerSock.h"
#include "NameServerSock.h"
#include "NameSock.h"

#include "MainFrm.h"
#include "server2Doc.h"
#include "server2View.h"
#include "Cserver2ChildView.h"
#include "afxcoll.h"

// Cserver2App:
// 이 클래스의 구현에 대해서는 server2.cpp을 참조하십시오.
//

class Cserver2App : public CWinApp
{
public:
	Cserver2App();


// 재정의입니다.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 구현입니다.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
public:
	CServerSock* m_pServer;
	CClientSock* m_pClient;
	CDrawServerSock* m_pDrawServer;
	CDrawSock* m_pDrawClient;
	CNameServerSock* m_pNameServer;
	CNameSock* m_pName;

	void InitServer();
	void InitDrawServer();
	void InitNameServer();
	void Accept();
	void AcceptDraw();
	void AcceptName();
	void CleanUp();
	void ReceiveData(CClientSock* pSock);
	void ReceiveDraw(CDrawSock* pSock);
	void ReceiveName(CNameSock* pSock);
	void SendNotice(CString strData);
	void SendData(CString strData);
	void SendNext(CString strData);
	void SendDraw(DWORD Event, WORD Element, CPoint startPoint, CPoint EndPoint, COLORREF PenColor, UINT PenSize, UINT EraseSize = 50);
	void CloseChild(CClientSock* pSock);
	void Close(CDrawSock* pSock);
	void CloseName(CNameSock* pSock);

	CObList m_ClientList;
	CObList m_DrawList;
	CObList m_NameList;

	CMainFrame* pFrame;
	Cserver2Doc* pDoc;
	Cserver2View* pView;
	Cserver2ChildView* pCView;

	POSITION m_pos;
};

extern Cserver2App theApp;
