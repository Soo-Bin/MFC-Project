// NameServerSock.cpp : 구현 파일입니다.
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


// CNameServerSock 멤버 함수

void CNameServerSock::OnAccept(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	((Cserver2App*)AfxGetApp())->AcceptName();

	CAsyncSocket::OnAccept(nErrorCode);
}