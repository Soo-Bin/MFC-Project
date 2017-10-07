
// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "server2.h"

#include "MainFrm.h"
#include "server2Doc.h"
#include "server2View.h"
#include "ChattingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.
	cs.x = 0;
	cs.y = 0;
	cs.cx = 350;
	cs.cy = 400;

	if (cs.hMenu != NULL) {
		::DestroyMenu(cs.hMenu);
		cs.hMenu = NULL;
	}

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기
// CMainFrame 메시지 처리기
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_wndSplitter.CreateStatic(this, 1, 2);
	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(Cserver2View), CSize(0, 0), pContext);
	m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CChattingView), CSize(310, 100), pContext);

	return TRUE;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}


void CMainFrame::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CFrameWnd::OnPaint()을(를) 호출하지 마십시오.
	/*
	CWnd* Cpen = m_wndDialogBar.GetDlgItem(IDV_PENCOLOR);

	CClientDC PenDC(Cpen);

	CRect PenRect;
	Cpen->GetClientRect(PenRect);

	Cpaintchat2Doc *PDoc = (Cpaintchat2Doc*)this->GetActiveDocument();
	CBrush Brush, *OldBrush;
	Brush.CreateSolidBrush(PDoc->GetElementPenColor());

	OldBrush = (CBrush*)PenDC.SelectObject(&Brush);
	PenDC.FillRect(PenRect, &Brush);
	PenDC.SelectObject(OldBrush);

	Cpaintchat2View *pView = (Cpaintchat2View*)this->GetActiveView();
	*/
	CFrameWnd::OnPaint();
}

