#pragma once
#include "paintchat2View.h"

// CpaintchatChildView

class CpaintchatChildView : public Cpaintchat2View
{
public:
	CpaintchatChildView();
	virtual ~CpaintchatChildView();
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
};


