// DrawServerSock.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "server2.h"
#include "DrawServerSock.h"


// CDrawServerSock

CDrawServerSock::CDrawServerSock()
{
}

CDrawServerSock::~CDrawServerSock()
{
}


void CDrawServerSock::OnAccept(int nErrorCode)
{
	//	���� ����� ���� ȣ��
	((Cserver2App*)AfxGetApp())->AcceptDraw();

	CAsyncSocket::OnAccept(nErrorCode);
}

// CDrawServerSock ��� �Լ�
