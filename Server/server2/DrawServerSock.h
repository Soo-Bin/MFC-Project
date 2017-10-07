#pragma once

// CDrawServerSock 명령 대상입니다.

class CDrawServerSock : public CAsyncSocket
{
public:
	CDrawServerSock();
	virtual ~CDrawServerSock();
	virtual void OnAccept(int nErrorCode);
};


