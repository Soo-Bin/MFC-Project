#pragma once
#include "server2View.h"

// Cserver2ChildView 명령 대상입니다.

class Cserver2ChildView : public Cserver2View
{
public:
	Cserver2ChildView();
	virtual ~Cserver2ChildView();
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
};


