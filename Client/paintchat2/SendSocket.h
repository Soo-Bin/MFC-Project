#pragma once

// SendSocket ��� ����Դϴ�.

class CDrawSock : public CAsyncSocket
{
public:
	CDrawSock();
	virtual ~CDrawSock();
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


