// NameSock.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "server2.h"
#include "NameSock.h"


// CNameSock

CNameSock::CNameSock()
{
}

CNameSock::~CNameSock()
{
}


// CNameSock ��� �Լ�

void CNameSock::OnReceive(int nErrorCode)
{
	((Cserver2App*)AfxGetApp())->ReceiveName(this);
	CAsyncSocket::OnReceive(nErrorCode);
}

void CNameSock::OnClose(int nErrorCode)
{
	((Cserver2App*)AfxGetApp())->CloseName(this);
	CAsyncSocket::OnClose(nErrorCode);
}
