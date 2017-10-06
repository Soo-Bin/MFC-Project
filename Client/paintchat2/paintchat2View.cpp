
// paintchat2View.cpp : Cpaintchat2View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
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

// Cpaintchat2View 생성/소멸

Cpaintchat2View::Cpaintchat2View()
	: m_ptNow(0)
	, m_ptOld(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_TempElement = 0;
	Connect = FALSE;
}

Cpaintchat2View::~Cpaintchat2View()
{
}

BOOL Cpaintchat2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// Cpaintchat2View 그리기

void Cpaintchat2View::OnDraw(CDC* pDC)
{
	Cpaintchat2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	POSITION pos = pDoc->P_Container.GetHeadPosition();

	CRect rect;
	GetClientRect(&rect);

	while (pos) {
		CElement *me = (CElement*)pDoc->P_Container.GetNext(pos);
		me->Draw(pDC, rect);
	}
}


// Cpaintchat2View 인쇄

BOOL Cpaintchat2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void Cpaintchat2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void Cpaintchat2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// Cpaintchat2View 진단

#ifdef _DEBUG
void Cpaintchat2View::AssertValid() const
{
	CView::AssertValid();
}

void Cpaintchat2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cpaintchat2Doc* Cpaintchat2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cpaintchat2Doc)));
	return (Cpaintchat2Doc*)m_pDocument;
}
#endif //_DEBUG


// Cpaintchat2View 메시지 처리기
void Cpaintchat2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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

		// 펜과 커브 일 때만 생성한다.	
		if (pDoc->GetElementType() == PEN || pDoc->GetElementType() == ERASE)
		{
			m_TempElement = CreateElement();
			m_TempElement->Draw(&aDC, rect);
		}
		// 상대방과 컨넥이 됐을 경우

		((Cpaintchat2App*)AfxGetApp())->SendDraw(EVENT_LBUTTONDOWN, pDoc->GetElementType(), m_ptOld, m_ptNow,
			pDoc->GetElementPenColor(), pDoc->GetElementPenSize(), 50);


		SetCapture();
	}
	CView::OnLButtonDown(nFlags, point);
}


void Cpaintchat2View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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

// 체크 표시 변경
void Cpaintchat2View::OnUpdateFigure(CCmdUI * pCmdUI)
{
	Cpaintchat2Doc *pDoc = GetDocument();
	pCmdUI->SetRadio(pDoc->GetCheckElement() == pCmdUI->m_nID);
}


void Cpaintchat2View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CClientDC aDC(this);

	Cpaintchat2Doc* pDoc = GetDocument();
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	Cpaintchat2View* pView = (Cpaintchat2View*)pFrame->m_wndSplitter.GetPane(0, 0);

	// 다이얼로그바 버튼 색상
	pFrame->OnPaint();
	
	if (pView->Connect)
	{
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
			// 상대방과 연결이 됐을 경우

			((Cpaintchat2App*)AfxGetApp())->SendDraw(EVENT_MOUSEMOVE, pDoc->GetElementType(), m_ptOld, m_ptNow,
				pDoc->GetElementPenColor(), pDoc->GetElementPenSize(), 50);
		}
	}
	// 상태바에 마우스 좌표 출력
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

// 펜 색깔 버튼
void Cpaintchat2View::OnBnClickedPencolor()
{
	Cpaintchat2Doc *pDoc = GetDocument();
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();

	pDoc->OnPen();

	ChangeButtonColor(pDoc->GetElementPenColor(), IDV_PENCOLOR);
}

// 다이얼 로그바에 있는 버튼 색깔 변경하기
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
// 펜 버튼
void Cpaintchat2View::OnBnClickedPen()
{
	Cpaintchat2Doc *pDoc = GetDocument();
	
	pDoc->StatusBarElementName(IDC_FIGURE_PEN);
}
// 지우개 버튼
void Cpaintchat2View::OnBnClickedErase()
{
	Cpaintchat2Doc *pDoc = GetDocument();

	pDoc->StatusBarElementName(IDC_FIGURE_ERASE);
}
// 펜 사이즈 버튼
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
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
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
