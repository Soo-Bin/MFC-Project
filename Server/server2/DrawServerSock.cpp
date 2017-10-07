// DrawServerSock.cpp : 구현 파일입니다.
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
	//	접속 허용을 위해 호출
	((Cserver2App*)AfxGetApp())->AcceptDraw();

	CAsyncSocket::OnAccept(nErrorCode);
}

// CDrawServerSock 멤버 함수
