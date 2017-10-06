#pragma once

// SendSocket 명령 대상입니다.

class CDrawSock : public CAsyncSocket
{
public:
	CDrawSock();
	virtual ~CDrawSock();
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


