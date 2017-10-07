#pragma once
#include "element.h"
// CCPen 명령 대상입니다.

class CCPen : public CElement
{
public:
	CCPen();
	CCPen(const CPoint &start, const CPoint &end, const UINT PenSize, const COLORREF PenColor);
	virtual ~CCPen();
	virtual void Draw(CDC *pDC, CRect &rect);
};


