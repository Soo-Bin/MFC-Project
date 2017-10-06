#pragma once

// CNameSock 명령 대상입니다.

class CNameSock : public CAsyncSocket
{
public:
	CNameSock();
	virtual ~CNameSock();
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


