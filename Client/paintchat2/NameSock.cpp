// NameSock.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "paintchat2.h"
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
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	((Cpaintchat2App*)AfxGetApp())->ReceiveNotice();
	CAsyncSocket::OnReceive(nErrorCode);
}

void CNameSock::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	((Cpaintchat2App*)AfxGetApp())->CloseChild();
	CAsyncSocket::OnClose(nErrorCode);
}