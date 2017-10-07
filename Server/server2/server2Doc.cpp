
// server2Doc.cpp : Cserver2Doc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "server2.h"
#endif

#include "server2Doc.h"
#include "MainFrm.h"
#include "server2View.h"
#include "ChattingView.h"
#include "mysql.h"

#define DB_ADDRESS "localhost"
#define DB_ID "root"
#define DB_PASS "0000"
#define DB_NAME "mfc_catchmind"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Cserver2Doc

IMPLEMENT_DYNCREATE(Cserver2Doc, CDocument)

BEGIN_MESSAGE_MAP(Cserver2Doc, CDocument)
END_MESSAGE_MAP()


// Cserver2Doc 생성/소멸

Cserver2Doc::Cserver2Doc()
	: Connection(NULL)
	, sql_Result(NULL)
	, sql_Row(NULL)
	, Query_status(0)
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	m_PenColor = RGB(0, 0, 0);
	m_PenSize = 1;
	m_Element = PEN;
}

Cserver2Doc::~Cserver2Doc()
{
}

BOOL Cserver2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// Cserver2Doc serialization

void Cserver2Doc::Serialize(CArchive& ar)
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
void Cserver2Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void Cserver2Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void Cserver2Doc::SetSearchContent(const CString& value)
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

// Cserver2Doc 진단

#ifdef _DEBUG
void Cserver2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void Cserver2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Cserver2Doc 명령
WORD Cserver2Doc::GetElementType() const
{
	return m_Element;
}

// 펜 두께 반환
UINT Cserver2Doc::GetElementPenSize()const
{
	return m_PenSize;
}

// 펜 색깔 반환
COLORREF Cserver2Doc::GetElementPenColor()const
{
	return m_PenColor;
}
// 현재 선택된 도형 반환
UINT Cserver2Doc::GetCheckElement() const
{
	return m_CheckElement;
}

// 현재 선택된 펜 두께 반환
UINT Cserver2Doc::GetCheckPenSize()const
{
	return m_CheckPenSize;
}


void Cserver2Doc::OnConnectDB()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CChattingView* pRView = (CChattingView*)pFrame->m_wndSplitter.GetPane(0, 1);
	
	mysql_init(&Connect);
	Connection = mysql_real_connect(&Connect, DB_ADDRESS, DB_ID, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	if (!Connection) {
		CString str;
		str = mysql_error(&Connect);
		AfxMessageBox(str,MB_OK);
	} else {}

	int num = 0;
	srand((int)time(NULL));
	num = rand() % 55;

	CString strquery;
	strquery.Format(_T("select name from word where id=%d"), num);
	wchar_t* wc;
	wc = strquery.GetBuffer(strquery.GetLength());
	strquery.ReleaseBuffer(strquery.GetLength());
	int ac_num = WideCharToMultiByte(CP_ACP, 0, wc, -1, NULL, 0, NULL, NULL);
	char* ac = new char[ac_num];
	WideCharToMultiByte(CP_ACP, 0, wc, -1, ac, ac_num, 0, 0);

	mysql_query(&Connect, "set Names euckr");
	mysql_query(&Connect, ac);
	sql_Result = mysql_store_result(&Connect);
	Query_status = mysql_num_fields(sql_Result);
	if (sql_Result == NULL) {
		AfxMessageBox(_T("조회된 결과가 없다."));
	}
	else {
		while ((sql_Row = mysql_fetch_row(sql_Result)) != NULL)
		{
			CString row;

			for (int i = 0; i < Query_status; i++)
			{
				row += sql_Row[i];
			}
			pRView->m_CatchWord = row;
			int sel = pRView->m_listChat.InsertString(-1, row);
			pRView->m_listChat.SetCurSel(sel);
		}
	}
	mysql_free_result(sql_Result);
	mysql_close(&Connect);
	delete ac;
}

void Cserver2Doc::OnCatchWordDB()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CChattingView* pRView = (CChattingView*)pFrame->m_wndSplitter.GetPane(0, 1);

	mysql_init(&Connect);
	Connection = mysql_real_connect(&Connect, DB_ADDRESS, DB_ID, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	if (!Connection) {
		CString str;
		str = mysql_error(&Connect);
		AfxMessageBox(str, MB_OK);
	}
	else {}

	int num = 0;
	srand((int)time(NULL));
	num = rand() % 55;

	CString strquery;
	strquery.Format(_T("select name from word where id=%d"), num);
	wchar_t* wc;
	wc = strquery.GetBuffer(strquery.GetLength());
	strquery.ReleaseBuffer(strquery.GetLength());
	int ac_num = WideCharToMultiByte(CP_ACP, 0, wc, -1, NULL, 0, NULL, NULL);
	char* ac = new char[ac_num];
	WideCharToMultiByte(CP_ACP, 0, wc, -1, ac, ac_num, 0, 0);

	mysql_query(&Connect, "set Names euckr");
	mysql_query(&Connect, ac);
	sql_Result = mysql_store_result(&Connect);
	Query_status = mysql_num_fields(sql_Result);
	if (sql_Result == NULL) {
		AfxMessageBox(_T("조회된 결과가 없다."));
	}
	else {
		while ((sql_Row = mysql_fetch_row(sql_Result)) != NULL)
		{
			CString row;

			for (int i = 0; i < Query_status; i++)
			{
				row += sql_Row[i];
			}
			pRView->m_CatchWord = row;
		}
	}
	mysql_free_result(sql_Result);
	mysql_close(&Connect);
	delete ac;
}