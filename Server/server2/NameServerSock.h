#pragma once

// CNameServerSock ��� ����Դϴ�.

class CNameServerSock : public CAsyncSocket
{
public:
	CNameServerSock();
	virtual ~CNameServerSock();
	virtual void OnAccept(int nErrorCode);
};


