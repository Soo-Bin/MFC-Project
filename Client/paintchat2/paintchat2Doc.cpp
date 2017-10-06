
// paintchat2Doc.cpp : Cpaintchat2Doc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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


// Cpaintchat2Doc ����/�Ҹ�

Cpaintchat2Doc::Cpaintchat2Doc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.
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

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// Cpaintchat2Doc serialization

void Cpaintchat2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void Cpaintchat2Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
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

// �˻� ó���⸦ �����մϴ�.
void Cpaintchat2Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
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

// Cpaintchat2Doc ����

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


// Cpaintchat2Doc ���

// ���� ���� Ÿ�� ��ȯ
WORD Cpaintchat2Doc::GetElementType() const
{
	return m_Element;
}

// �� �β� ��ȯ
UINT Cpaintchat2Doc::GetElementPenSize()const
{
	return m_PenSize;
}

// �� ���� ��ȯ
COLORREF Cpaintchat2Doc::GetElementPenColor()const
{
	return m_PenColor;
}
// ���� ���õ� ���� ��ȯ
UINT Cpaintchat2Doc::GetCheckElement() const
{
	return m_CheckElement;
}

// ���� ���õ� �� �β� ��ȯ
UINT Cpaintchat2Doc::GetCheckPenSize()const
{
	return m_CheckPenSize;
}

// �� ���� ����
void Cpaintchat2Doc::OnPen()
{
	CColorDialog dlg(m_PenColor);
	if (dlg.DoModal() == IDOK)
	{
		m_PenColor = dlg.GetColor();
	}
}


// ���� Ÿ��  �� üũ ����, ���¹� ����
void Cpaintchat2Doc::StatusBarElementName(UINT nID)
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CString sText;

	switch (nID)
	{
	case IDC_FIGURE_PEN:
		m_Element = PEN;
		sText.Format(_T("����:  ��"));
		break;

	case IDC_FIGURE_ERASE:
		m_Element = ERASE;
		sText.Format(_T("����:  ���찳"));
	}
	m_CheckElement = nID;
	pFrame->m_wndStatusBar.SetPaneText(2, sText);
}

// �� ������ �� üũ ����, ���¹� ����
void Cpaintchat2Doc::StatusBarPenSize(UINT nID)
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CString sText;

	switch (nID)
	{
	case ID_PEN1:
		m_PenSize = 1;
		sText.Format(_T("�� ������:  1"));
		break;

	case ID_PEN2:
		m_PenSize = 2;
		sText.Format(_T("�� ������:  2"));
		break;

	case ID_PEN3:
		m_PenSize = 3;
		sText.Format(_T("�� ������:  3"));
		break;

	case ID_PEN4:
		m_PenSize = 4;
		sText.Format(_T("�� ������:  4"));
		break;

	case ID_PEN5:
		m_PenSize = 5;
		sText.Format(_T("�� ������:  5"));
	}
	m_CheckPenSize = nID;
	pFrame->m_wndStatusBar.SetPaneText(3, sText);
}