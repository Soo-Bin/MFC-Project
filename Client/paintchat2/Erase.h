#pragma once
#include "element.h"
// CErase ��� ����Դϴ�.

class CErase : public CElement
{
	HCURSOR hCursor;
public:
	CErase();
	CErase(const CPoint &start, const CPoint &end);
	virtual ~CErase();
	virtual void Draw(CDC *pDC, CRect &rect);
};


