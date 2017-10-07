#ifndef __CHANNEL_H
#define __CHANNEL_H

#define EVENT_LBUTTONDOWN		0x10010
#define EVENT_LBUTTONUP			0x10020
#define EVENT_MOUSEMOVE			0x10030
#define EVENT_REMOVE			0x10040

#define PORTNUMBER_SERVER			10020
#define PORTNUMBER_CLIENT			10050

struct DATA
{
	DWORD			Event;
	WORD			Element;
	CPoint			StartPoint;
	CPoint			EndPoint;
	COLORREF		PenColor;
	UINT			PenSize;
	UINT			EraseSize;
};

class MyPacket
{
	char *base;
	DWORD plen;

public:
	MyPacket()
	{
		base = 0;
		plen = 0;
	}

	virtual ~MyPacket()
	{
		if (base)
		{
			delete[] base;
		}
	}

	void EnPacket(void *data, int size)
	{
		base = (char *)realloc(base, plen + size);
		memcpy(base + plen, data, size);
		plen += size;
	}

	char* GetBase()
	{
		return base;
	}

	DWORD GetSize()
	{
		return plen;
	}
};

#endif