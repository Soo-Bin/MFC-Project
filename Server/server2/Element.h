#pragma once

// CElement 명령 대상입니다.

class CElement : public CObject
{
protected:
	CPoint m_StartPoint, m_EndPoint, m_PrevPoint;
	COLORREF m_PenColor;
	UINT m_PenSize;
	UINT m_EraseSize;
	CArray<CPoint, CPoint&> m_ptArray;

public:
	CElement();
	virtual ~CElement();
	virtual void Draw(CDC *pDC, CRect &rect);
	void ChangePoint(CPoint &Pos);
	void ChangePenSize(UINT Pen);
	void ChangeEraseSize(UINT Erase);
	void ChangePenColor(COLORREF Pen);

};


