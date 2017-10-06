// Erase.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "paintchat2.h"
#include "Erase.h"
#include "resource.h"
#include "MainFrm.h"
#include "paintchat2Doc.h"

// CErase

CErase::CErase()
{
}

CErase::~CErase()
{
}


// CErase 멤버 함수
CErase::CErase(const CPoint &start, const CPoint &end)
{
	m_StartPoint = start;
	m_EndPoint = end;
}

void CErase::Draw(CDC *pDC, CRect &rect)
{
	pDC->SetROP2(R2_WHITE);
	CPen aPen, *pOldPen;
	COLORREF m_EraseCOLOR = RGB(255, 255, 255);

	aPen.CreatePen(PS_SOLID, 50, m_EraseCOLOR);

	// 커서 변경
	hCursor = AfxGetApp()->LoadCursor(IDC_ERASECURSOR);
	SetCursor(hCursor);

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
