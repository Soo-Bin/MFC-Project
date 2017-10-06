#pragma once
#include "element.h"
// CCPen ��� ����Դϴ�.

class CCPen : public CElement
{
public:
	CCPen();
	CCPen(const CPoint &start, const CPoint &end, const UINT PenSize, const COLORREF PenColor);
	virtual ~CCPen();
	virtual void Draw(CDC *pDC, CRect &rect);
};


