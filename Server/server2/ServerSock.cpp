// ServerSock.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "server2.h"
#include "ServerSock.h"


// CServerSock

CServerSock::CServerSock()
{
}

CServerSock::~CServerSock()
{
}


// CServerSock ��� �Լ�

void CServerSock::OnAccept(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	((Cserver2App*)AfxGetApp())->Accept();

	CAsyncSocket::OnAccept(nErrorCode);
}
