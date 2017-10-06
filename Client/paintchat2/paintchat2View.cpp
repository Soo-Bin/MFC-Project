
// paintchat2View.cpp : Cpaintchat2View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "paintchat2.h"
#endif

#include "paintchat2Doc.h"
#include "paintchat2View.h"

#include "CPen.h"
#include "Erase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cpaintchat2View

IMPLEMENT_DYNCREATE(Cpaintchat2View, CView)

BEGIN_MESSAGE_MAP(Cpaintchat2View, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)

	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()

	ON_COMMAND(ID_EDIT_UNDO, &Cpaintchat2View::OnEditUndo)
	ON_BN_CLICKED(IDB_PEN, &Cpaintchat2View::OnBnClickedPencolor)
	ON_BN_CLICKED(IDC_FIGURE_PEN, &Cpaintchat2View::OnBnClickedPen)
	ON_BN_CLICKED(IDC_FIGURE_ERASE, &Cpaintchat2View::OnBnClickedErase)
	ON_BN_CLICKED(ID_PEN1, &Cpaintchat2View::OnBnClickedPensize1)
	ON_BN_CLICKED(ID_PEN2, &Cpaintchat2View::OnBnClickedPensize2)
	ON_BN_CLICKED(ID_PEN3, &Cpaintchat2View::OnBnClickedPensize3)
	ON_BN_CLICKED(ID_PEN4, &Cpaintchat2View::OnBnClickedPensize4)
	ON_BN_CLICKED(ID_PEN5, &Cpaintchat2View::OnBnClickedPensize5)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &Cpaintchat2View::OnBnClickedClear)
END_MESSAGE_MAP()

// Cpaintchat2View ����/�Ҹ�

Cpaintchat2View::Cpaintchat2View()
	: m_ptNow(0)
	, m_ptOld(0)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_TempElement = 0;
	Connect = FALSE;
}

Cpaintchat2View::~Cpaintchat2View()
{
}

BOOL Cpaintchat2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// Cpaintchat2View �׸���

void Cpaintchat2View::OnDraw(CDC* pDC)
{
	Cpaintchat2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	POSITION pos = pDoc->P_Container.GetHeadPosition();

	CRect rect;
	GetClientRect(&rect);

	while (pos) {
		CElement *me = (CElement*)pDoc->P_Container.GetNext(pos);
		me->Draw(pDC, rect);
	}
}


// Cpaintchat2View �μ�

BOOL Cpaintchat2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void Cpaintchat2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void Cpaintchat2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// Cpaintchat2View ����

#ifdef _DEBUG
void Cpaintchat2View::AssertValid() const
{
	CView::AssertValid();
}

void Cpaintchat2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cpaintchat2Doc* Cpaintchat2View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cpaintchat2Doc)));
	return (Cpaintchat2Doc*)m_pDocument;
}
#endif //_DEBUG


// Cpaintchat2View �޽��� ó����
void Cpaintchat2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	Cpaintchat2View* pView = (Cpaintchat2View*)pFrame->m_wndSplitter.GetPane(0, 0);

	if (pView->Connect)
	{
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
		// ����� ������ ���� ���

		((Cpaintchat2App*)AfxGetApp())->SendDraw(EVENT_LBUTTONDOWN, pDoc->GetElementType(), m_ptOld, m_ptNow,
			pDoc->GetElementPenColor(), pDoc->GetElementPenSize(), 50);


		SetCapture();
	}
	CView::OnLButtonDown(nFlags, point);
}


void Cpaintchat2View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	Cpaintchat2View* pView = (Cpaintchat2View*)pFrame->m_wndSplitter.GetPane(0, 0);

	if (pView->Connect)
	{
		if (this == GetCapture())
			ReleaseCapture();

		Cpaintchat2Doc *pDoc = GetDocument();

		if (m_TempElement)
		{
			pDoc->P_Container.AddTail(m_TempElement);
			m_TempElement = 0;
		}
		
		((Cpaintchat2App*)AfxGetApp())->SendDraw(EVENT_LBUTTONUP, pDoc->GetElementType(), m_ptOld, m_ptNow,
			pDoc->GetElementPenColor(), pDoc->GetElementPenSize(), 50);
	}

	CView::OnLButtonUp(nFlags, point);
}

// üũ ǥ�� ����
void Cpaintchat2View::OnUpdateFigure(CCmdUI * pCmdUI)
{
	Cpaintchat2Doc *pDoc = GetDocument();
	pCmdUI->SetRadio(pDoc->GetCheckElement() == pCmdUI->m_nID);
}


void Cpaintchat2View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CClientDC aDC(this);

	Cpaintchat2Doc* pDoc = GetDocument();
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	Cpaintchat2View* pView = (Cpaintchat2View*)pFrame->m_wndSplitter.GetPane(0, 0);

	// ���̾�α׹� ��ư ����
	pFrame->OnPaint();
	
	if (pView->Connect)
	{
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
			// ����� ������ ���� ���

			((Cpaintchat2App*)AfxGetApp())->SendDraw(EVENT_MOUSEMOVE, pDoc->GetElementType(), m_ptOld, m_ptNow,
				pDoc->GetElementPenColor(), pDoc->GetElementPenSize(), 50);
		}
	}
	// ���¹ٿ� ���콺 ��ǥ ���
	CString sText;

	sText.Format(_T("x: %3d    y: %3d"), m_ptNow.x, m_ptNow.y);
	pFrame->m_wndStatusBar.SetPaneText(1, sText);

	CView::OnMouseMove(nFlags, point);
}

CElement * Cpaintchat2View::CreateElement()
{
	Cpaintchat2Doc* pDoc = GetDocument();
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

void Cpaintchat2View::OnEditUndo()
{
	Cpaintchat2Doc *pDoc = GetDocument();

	if (pDoc->P_Container.GetCount())
	{
		pDoc->P_Container.RemoveTail();
		Invalidate();
	}

	if (Connect)
	{
		((Cpaintchat2App*)AfxGetApp())->SendDraw(EVENT_REMOVE, pDoc->GetElementType(), m_ptOld, m_ptNow,
			pDoc->GetElementPenColor(), pDoc->GetElementPenSize(), 50);
	}
}

// �� ���� ��ư
void Cpaintchat2View::OnBnClickedPencolor()
{
	Cpaintchat2Doc *pDoc = GetDocument();
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();

	pDoc->OnPen();

	ChangeButtonColor(pDoc->GetElementPenColor(), IDV_PENCOLOR);
}

// ���̾� �α׹ٿ� �ִ� ��ư ���� �����ϱ�
void Cpaintchat2View::ChangeButtonColor(COLORREF Color, UINT DlgID)
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();

	CWnd *Wnd = pFrame->m_wndDialogBar.GetDlgItem(DlgID);
	CClientDC dc(Wnd);

	CRect rect;
	Wnd->GetClientRect(rect);

	CBrush Brush, *OldBrush;
	Brush.CreateSolidBrush(Color);

	OldBrush = (CBrush*)dc.SelectObject(&Brush);
	dc.FillRect(rect, &Brush);
	dc.SelectObject(OldBrush);
}
// �� ��ư
void Cpaintchat2View::OnBnClickedPen()
{
	Cpaintchat2Doc *pDoc = GetDocument();
	
	pDoc->StatusBarElementName(IDC_FIGURE_PEN);
}
// ���찳 ��ư
void Cpaintchat2View::OnBnClickedErase()
{
	Cpaintchat2Doc *pDoc = GetDocument();

	pDoc->StatusBarElementName(IDC_FIGURE_ERASE);
}
// �� ������ ��ư
void Cpaintchat2View::OnBnClickedPensize1()
{
	Cpaintchat2Doc *pDoc = GetDocument();
	
	pDoc->StatusBarPenSize(ID_PEN1);
}
void Cpaintchat2View::OnBnClickedPensize2()
{
	Cpaintchat2Doc *pDoc = GetDocument();
	
	pDoc->StatusBarPenSize(ID_PEN2);
}
void Cpaintchat2View::OnBnClickedPensize3()
{
	Cpaintchat2Doc *pDoc = GetDocument();

	pDoc->StatusBarPenSize(ID_PEN3);
}
void Cpaintchat2View::OnBnClickedPensize4()
{
	Cpaintchat2Doc *pDoc = GetDocument();

	pDoc->StatusBarPenSize(ID_PEN4);
}
void Cpaintchat2View::OnBnClickedPensize5()
{
	Cpaintchat2Doc *pDoc = GetDocument();

	pDoc->StatusBarPenSize(ID_PEN5);
}

void Cpaintchat2View::OnBnClickedClear()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	Cpaintchat2Doc *pDoc = GetDocument();

	if (pDoc->P_Container.GetCount())
	{
		pDoc->P_Container.RemoveAll();
		Invalidate();
	}

	if (Connect)
	{
		((Cpaintchat2App*)AfxGetApp())->SendDraw(EVENT_REMOVE, pDoc->GetElementType(), m_ptOld, m_ptNow,
			pDoc->GetElementPenColor(), pDoc->GetElementPenSize(), 50);
	}
}
