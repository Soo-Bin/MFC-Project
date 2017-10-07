
// server2View.cpp : Cserver2View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()

	ON_COMMAND(ID_EDIT_UNDO, &Cserver2View::OnEditUndo)

END_MESSAGE_MAP()

// Cserver2View 생성/소멸

Cserver2View::Cserver2View()
	: m_ptNow(0)
	, m_ptOld(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_TempElement = 0;

}

Cserver2View::~Cserver2View()
{
}

BOOL Cserver2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// Cserver2View 그리기

void Cserver2View::OnDraw(CDC* /*pDC*/)
{
	Cserver2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// Cserver2View 인쇄

BOOL Cserver2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void Cserver2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void Cserver2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// Cserver2View 진단

#ifdef _DEBUG
void Cserver2View::AssertValid() const
{
	CView::AssertValid();
}

void Cserver2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cserver2Doc* Cserver2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cserver2Doc)));
	return (Cserver2Doc*)m_pDocument;
}
#endif //_DEBUG


// Cserver2View 메시지 처리기
void Cserver2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
	
	// 상대방과 컨넥이 됐을 경우
	theApp.SendDraw(EVENT_LBUTTONDOWN, pDoc->GetElementType(), m_ptOld, m_ptNow,
		pDoc->GetElementPenColor(), pDoc->GetElementPenSize(), 50);

	SetCapture();

	CView::OnLButtonDown(nFlags, point);
}


void Cserver2View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CClientDC aDC(this);

	Cserver2Doc* pDoc = GetDocument();
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();


	// 다이얼로그바 버튼 색상
	pFrame->OnPaint();

	CRect rect;
	GetClientRect(&rect);

	CPen pen;

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