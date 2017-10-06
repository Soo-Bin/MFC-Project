// SendSocket.cpp : 구현 파일입니다.
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


// SendSocket 멤버 함수


void CDrawSock::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	((Cpaintchat2App*)AfxGetApp())->ReceiveDraw();
	CAsyncSocket::OnReceive(nErrorCode);
}


void CDrawSock::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CAsyncSocket::OnClose(nErrorCode);
}
