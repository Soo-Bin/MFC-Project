// ClientSock.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "paintchat2.h"
#include "ClientSock.h"


// CClientSock

CClientSock::CClientSock()
{
}

CClientSock::~CClientSock()
{
}


// CClientSock ��� �Լ�
void CClientSock::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	((Cpaintchat2App*)AfxGetApp())->ReceiveData();

	CAsyncSocket::OnReceive(nErrorCode);
}


void CClientSock::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	((Cpaintchat2App*)AfxGetApp())->CloseChild();
	CAsyncSocket::OnClose(nErrorCode);
}
