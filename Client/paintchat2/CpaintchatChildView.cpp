// CpaintchatChildView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "paintchat2.h"
#include "CpaintchatChildView.h"

#include "MainFrm.h"
#include "paintchat2View.h"
#include "paintchat2Doc.h"

// CpaintchatChildView

CpaintchatChildView::CpaintchatChildView()
{

}

CpaintchatChildView::~CpaintchatChildView()
{
}

// CpaintchatChildView �޽��� ó�����Դϴ�.

void CpaintchatChildView::OnLButtonDown(UINT nFlags, CPoint point)
{

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	Cpaintchat2View* pView = (Cpaintchat2View*)pFrame->m_wndSplitter.GetPane(0, 0);

	m_ptOld = point;
	m_ptNow = point;

	Cpaintchat2Doc* pDoc = GetDocument();
	CClientDC aDC(this);

	CRect rect;
	this->GetClientRect(&rect);

	// ��� Ŀ�� �� ���� �����Ѵ�.	
	if (pDoc->GetElementType() == PEN || pDoc->GetElementType() == ERASE)
	{
		m_TempElement = CreateElement();
		m_TempElement->Draw(&aDC, rect);
	}
	SetCapture();
}

void CpaintchatChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC aDC(this);

	Cpaintchat2Doc* pDoc = GetDocument();
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();


	// ���̾�α׹� ��ư ����
	pFrame->OnPaint();

	CRect rect;
	GetClientRect(&rect);

	CPen pen, *pOldPen;

	// ������ ���� �� ���� ���
	m_ptNow = point;

	if ((nFlags & MK_LBUTTON) && (this == GetCapture()))
	{
		// ���� ���� ������ ���� �����Ѵ�.
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
	}
	// ���¹ٿ� ���콺 ��ǥ ���
	CString sText;

	sText.Format(_T("x: %3d    y: %3d"), m_ptNow.x, m_ptNow.y);
	pFrame->m_wndStatusBar.SetPaneText(1, sText);

}

void CpaintchatChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (this == GetCapture())
		ReleaseCapture();

	Cpaintchat2Doc *pDoc = GetDocument();

	if (m_TempElement)
	{
		pDoc->P_Container.AddTail(m_TempElement);
		m_TempElement = 0;
	}

}
