#pragma once
#include "element.h"
// CErase 명령 대상입니다.

class CErase : public CElement
{
	HCURSOR hCursor;
public:
	CErase();
	CErase(const CPoint &start, const CPoint &end);
	virtual ~CErase();
	virtual void Draw(CDC *pDC, CRect &rect);
};


