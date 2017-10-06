// CPen.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "paintchat2.h"
#include "CPen.h"


// CCPen

CCPen::CCPen()
{
}

CCPen::~CCPen()
{
}


// CCPen 멤버 함수
CCPen::CCPen(const CPoint &start, const CPoint &end, const UINT PenSize, const COLORREF PenColor)
{
	m_StartPoint = start;
	m_EndPoint = end;
	m_PenColor = PenColor;
	m_PenSize = PenSize;

}

void CCPen::Draw(CDC *pDC, CRect &rect)
{
	CPen aPen, *pOldPen;
	aPen.CreatePen(PS_SOLID, m_PenSize, m_PenColor);

	pOldPen = pDC->SelectObject(&aPen);

	m_ptArray.Add(m_StartPoint);
	m_ptArray.Add(m_EndPoint);

	if (m_ptArray.GetSize())
	{
		pDC->MoveTo(m_ptArray[0]);
		for (int i = 0; i<m_ptArray.GetSize(); i++)
		{
			pDC->LineTo(m_ptArray[i]);
		}
	}
	m_StartPoint = m_EndPoint;
	pDC->SelectObject(pOldPen);
}
