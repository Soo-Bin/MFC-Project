#pragma once

// CNameSock ��� ����Դϴ�.

class CNameSock : public CAsyncSocket
{
public:
	CNameSock();
	virtual ~CNameSock();
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


