// Cserver2ChildView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "server2.h"
#include "Cserver2ChildView.h"

#include "MainFrm.h"
#include "server2View.h"
#include "server2Doc.h"

// Cserver2ChildView

Cserver2ChildView::Cserver2ChildView()
{
}

Cserver2ChildView::~Cserver2ChildView()
{
}


// Cserver2ChildView 멤버 함수
void Cserver2ChildView::OnLButtonDown(UINT nFlags, CPoint point)
{

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	Cserver2View* pView = (Cserver2View*)pFrame->m_wndSplitter.GetPane(0, 0);

	m_ptOld = point;
	m_ptNow = point;

	Cserver2Doc* pDoc = GetDocument();
	CClientDC aDC(this);

	CRect rect;
	this->GetClientRect(&rect);

	// 펜과 커브 일 때만 생성한다.	
	if (pDoc->GetElementType() == PEN || pDoc->GetElementType() == ERASE)
	{
		m_TempElement = CreateElement();
		m_TempElement->Draw(&aDC, rect);
	}
	theApp.SendDraw(EVENT_LBUTTONDOWN, pDoc->GetElementType(), m_ptOld, m_ptNow,
		pDoc->GetElementPenColor(), pDoc->GetElementPenSize(), 50);

	SetCapture();
}

void Cserver2ChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC aDC(this);

	Cserver2Doc* pDoc = GetDocument();
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();


	// 다이얼로그바 버튼 색상
	pFrame->OnPaint();

	CRect rect;
	GetClientRect(&rect);

	CPen pen, *pOldPen;

	// 상대방이 연결 안 했을 경우
	m_ptNow = point;

	if ((nFlags & MK_LBUTTON) && (this == GetCapture()))
	{
		// 펜일 때는 포인터 값만 갱신한다.
		if (pDoc->GetElementType() == PEN || pDoc->GetElementType() == ERASE)
		{
			m_TempElement->ChangePoint(m_ptNow);
			m_TempElement->Draw(&aDC, rect);
		}
		else
		{
			if (m_TempElement)
			{
				m_TempElement->Draw(&aDC, rect);
				delete m_TempElement;
				m_TempElement = 0;
			}

			m_TempElement = CreateElement();
			m_TempElement->Draw(&aDC, rect);
		}
		theApp.SendDraw(EVENT_MOUSEMOVE, pDoc->GetElementType(), m_ptOld, m_ptNow,
			pDoc->GetElementPenColor(), pDoc->GetElementPenSize(), 50);
	}
}

void Cserver2ChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (this == GetCapture())
		ReleaseCapture();

	Cserver2Doc *pDoc = GetDocument();

	if (m_TempElement)
	{
		pDoc->P_Container.AddTail(m_TempElement);
		m_TempElement = 0;
	}
	theApp.SendDraw(EVENT_LBUTTONUP, pDoc->GetElementType(), m_ptOld, m_ptNow,
		pDoc->GetElementPenColor(), pDoc->GetElementPenSize(), 50);

}
