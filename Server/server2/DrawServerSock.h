#pragma once

// CDrawServerSock ��� ����Դϴ�.

class CDrawServerSock : public CAsyncSocket
{
public:
	CDrawServerSock();
	virtual ~CDrawServerSock();
	virtual void OnAccept(int nErrorCode);
};


