// DrawSock.cpp : ���� �����Դϴ�.
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

// CDrawSock ��� �Լ�
