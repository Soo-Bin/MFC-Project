#pragma once

// CNameServerSock 명령 대상입니다.

class CNameServerSock : public CAsyncSocket
{
public:
	CNameServerSock();
	virtual ~CNameServerSock();
	virtual void OnAccept(int nErrorCode);
};


