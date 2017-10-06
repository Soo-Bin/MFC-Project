
// paintchat2Doc.cpp : Cpaintchat2Doc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "paintchat2.h"
#endif

#include "paintchat2Doc.h"
#include "MainFrm.h"
#include "paintchat2View.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Cpaintchat2Doc

IMPLEMENT_DYNCREATE(Cpaintchat2Doc, CDocument)

BEGIN_MESSAGE_MAP(Cpaintchat2Doc, CDocument)
	ON_COMMAND(ID_PENCLE, &Cpaintchat2Doc::OnPen)
END_MESSAGE_MAP()


// Cpaintchat2Doc 생성/소멸

Cpaintchat2Doc::Cpaintchat2Doc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	m_PenColor = RGB(0, 0, 0);
	m_PenSize = 1;
	m_Element = PEN;

	m_CheckPenSize = ID_PENSIZE1;
	m_CheckElement = ID_PENCLE;
}

Cpaintchat2Doc::~Cpaintchat2Doc()
{
}

BOOL Cpaintchat2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// Cpaintchat2Doc serialization

void Cpaintchat2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void Cpaintchat2Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void Cpaintchat2Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void Cpaintchat2Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Cpaintchat2Doc 진단

#ifdef _DEBUG
void Cpaintchat2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void Cpaintchat2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Cpaintchat2Doc 명령

// 현재 도형 타입 반환
WORD Cpaintchat2Doc::GetElementType() const
{
	return m_Element;
}

// 펜 두께 반환
UINT Cpaintchat2Doc::GetElementPenSize()const
{
	return m_PenSize;
}

// 펜 색깔 반환
COLORREF Cpaintchat2Doc::GetElementPenColor()const
{
	return m_PenColor;
}
// 현재 선택된 도형 반환
UINT Cpaintchat2Doc::GetCheckElement() const
{
	return m_CheckElement;
}

// 현재 선택된 펜 두께 반환
UINT Cpaintchat2Doc::GetCheckPenSize()const
{
	return m_CheckPenSize;
}

// 펜 색깔 변경
void Cpaintchat2Doc::OnPen()
{
	CColorDialog dlg(m_PenColor);
	if (dlg.DoModal() == IDOK)
	{
		m_PenColor = dlg.GetColor();
	}
}


// 도형 타입  및 체크 상태, 상태바 변경
void Cpaintchat2Doc::StatusBarElementName(UINT nID)
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CString sText;

	switch (nID)
	{
	case IDC_FIGURE_PEN:
		m_Element = PEN;
		sText.Format(_T("도형:  펜"));
		break;

	case IDC_FIGURE_ERASE:
		m_Element = ERASE;
		sText.Format(_T("도형:  지우개"));
	}
	m_CheckElement = nID;
	pFrame->m_wndStatusBar.SetPaneText(2, sText);
}

// 펜 사이즈 및 체크 상태, 상태바 변경
void Cpaintchat2Doc::StatusBarPenSize(UINT nID)
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CString sText;

	switch (nID)
	{
	case ID_PEN1:
		m_PenSize = 1;
		sText.Format(_T("펜 사이즈:  1"));
		break;

	case ID_PEN2:
		m_PenSize = 2;
		sText.Format(_T("펜 사이즈:  2"));
		break;

	case ID_PEN3:
		m_PenSize = 3;
		sText.Format(_T("펜 사이즈:  3"));
		break;

	case ID_PEN4:
		m_PenSize = 4;
		sText.Format(_T("펜 사이즈:  4"));
		break;

	case ID_PEN5:
		m_PenSize = 5;
		sText.Format(_T("펜 사이즈:  5"));
	}
	m_CheckPenSize = nID;
	pFrame->m_wndStatusBar.SetPaneText(3, sText);
}