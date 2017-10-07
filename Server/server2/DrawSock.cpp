// DrawSock.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "server2.h"
#include "DrawSock.h"


// CDrawSock

CDrawSock::CDrawSock()
{
}

CDrawSock::~CDrawSock()
{
}


void CDrawSock::OnReceive(int nErrorCode)
{
	((Cserver2App*)AfxGetApp())->ReceiveDraw(this);
	CAsyncSocket::OnReceive(nErrorCode);
}

void CDrawSock::OnClose(int nErrorCode)
{
	((Cserver2App*)AfxGetApp())->Close(this);
	CAsyncSocket::OnClose(nErrorCode);
}

// CDrawSock 멤버 함수
