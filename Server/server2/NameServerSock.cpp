// NameServerSock.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "server2.h"
#include "NameServerSock.h"


// CNameServerSock

CNameServerSock::CNameServerSock()
{
}

CNameServerSock::~CNameServerSock()
{
}


// CNameServerSock ��� �Լ�

void CNameServerSock::OnAccept(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	((Cserver2App*)AfxGetApp())->AcceptName();

	CAsyncSocket::OnAccept(nErrorCode);
}