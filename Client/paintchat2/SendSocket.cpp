// SendSocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "paintchat2.h"
#include "SendSocket.h"


// SendSocket

CDrawSock::CDrawSock()
{
}

CDrawSock::~CDrawSock()
{
}


// SendSocket ��� �Լ�


void CDrawSock::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	((Cpaintchat2App*)AfxGetApp())->ReceiveDraw();
	CAsyncSocket::OnReceive(nErrorCode);
}


void CDrawSock::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	CAsyncSocket::OnClose(nErrorCode);
}
