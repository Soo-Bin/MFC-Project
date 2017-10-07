
// server2View.cpp : Cserver2View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "server2.h"
#endif

#include "MainFrm.h"
#include "server2Doc.h"
#include "server2View.h"

#include "CPen.h"
#include "Erase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cserver2View

IMPLEMENT_DYNCREATE(Cserver2View, CView)

BEGIN_MESSAGE_MAP(Cserver2View, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()

	ON_COMMAND(ID_EDIT_UNDO, &Cserver2View::OnEditUndo)

END_MESSAGE_MAP()

// Cserver2View ����/�Ҹ�

Cserver2View::Cserver2View()
	: m_ptNow(0)
	, m_ptOld(0)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_TempElement = 0;

}

Cserver2View::~Cserver2View()
{
}

BOOL Cserver2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// Cserver2View �׸���

void Cserver2View::OnDraw(CDC* /*pDC*/)
{
	Cserver2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// Cserver2View �μ�

BOOL Cserver2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void Cserver2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void Cserver2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// Cserver2View ����

#ifdef _DEBUG
void Cserver2View::AssertValid() const
{
	CView::AssertValid();
}

void Cserver2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cserver2Doc* Cserver2View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cserver2Doc)));
	return (Cserver2Doc*)m_pDocument;
}
#endif //_DEBUG


// Cserver2View �޽��� ó����
void Cserver2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	Cserver2View* pView = (Cserver2View*)pFrame->m_wndSplitter.GetPane(0, 0);

	m_ptOld = point;
	m_ptNow = point;

	Cserver2Doc* pDoc = GetDocument();
	CClientDC aDC(this);

	CRect rect;
	this->GetClientRect(&rect);

	// ��� Ŀ�� �� ���� �����Ѵ�.	
	if (pDoc->GetElementType() == PEN || pDoc->GetElementType() == ERASE)
	{
		m_TempElement = CreateElement();
		m_TempElement->Draw(&aDC, rect);
	}
	
	// ����� ������ ���� ���
	theApp.SendDraw(EVENT_LBUTTONDOWN, pDoc->GetElementType(), m_ptOld, m_ptNow,
		pDoc->GetElementPenColor(), pDoc->GetElementPenSize(), 50);

	SetCapture();

	CView::OnLButtonDown(nFlags, point);
}


void Cserver2View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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


	CView::OnLButtonUp(nFlags, point);
}
void Cserver2View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CClientDC aDC(this);

	Cserver2Doc* pDoc = GetDocument();
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();


	// ���̾�α׹� ��ư ����
	pFrame->OnPaint();

	CRect rect;
	GetClientRect(&rect);

	CPen pen;

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
		// ����� ������ ���� ���
		theApp.SendDraw(EVENT_MOUSEMOVE, pDoc->GetElementType(), m_ptOld, m_ptNow,
				pDoc->GetElementPenColor(), pDoc->GetElementPenSize(), 50);
		
	}
	
	CView::OnMouseMove(nFlags, point);
}

CElement * Cserver2View::CreateElement()
{
	Cserver2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	switch (pDoc->GetElementType())
	{
	case PEN:
		return new CCPen(m_ptOld, m_ptNow, pDoc->GetElementPenSize(), pDoc->GetElementPenColor());

	case ERASE:
		return new CErase(m_ptOld, m_ptNow);

	default:
		AfxMessageBox(_T("Bad Element code", MB_OK));
		AfxAbort();
		return NULL;
	}
}

void Cserver2View::OnEditUndo()
{
	Cserver2Doc *pDoc = GetDocument();

	if (pDoc->P_Container.GetCount())
	{
		pDoc->P_Container.RemoveTail();
		Invalidate();
	}

	theApp.SendDraw(EVENT_REMOVE, pDoc->GetElementType(), m_ptOld, m_ptNow,
		pDoc->GetElementPenColor(), pDoc->GetElementPenSize(), 50);

}