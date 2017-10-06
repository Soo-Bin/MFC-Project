
// paintchat2View.h : Cpaintchat2View Ŭ������ �������̽�
//

#pragma once

#include "Element.h"

class Cpaintchat2View : public CView
{
protected: // serialization������ ��������ϴ�.
	Cpaintchat2View();
	DECLARE_DYNCREATE(Cpaintchat2View)

// Ư���Դϴ�.
public:
	Cpaintchat2Doc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	CElement * CreateElement();
	virtual ~Cpaintchat2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	CPoint m_ptNow;
	CPoint m_ptOld;
	CElement *m_TempElement;
	BOOL Connect;
	COLORREF m_colLine;
	COLORREF m_colLineXor;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnUpdateFigure(CCmdUI *pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

public:
	afx_msg void OnEditUndo();
	afx_msg void OnBnClickedPencolor();
	afx_msg void OnBnClickedPen();
	afx_msg void OnBnClickedErase();
	afx_msg void OnBnClickedPensize1();
	afx_msg void OnBnClickedPensize2();
	afx_msg void OnBnClickedPensize3();
	afx_msg void OnBnClickedPensize4();
	afx_msg void OnBnClickedPensize5();
	afx_msg void OnBnClickedClear();
	void ChangeButtonColor(COLORREF Color, UINT DlgID);
};

#ifndef _DEBUG  // paintchat2View.cpp�� ����� ����
inline Cpaintchat2Doc* Cpaintchat2View::GetDocument() const
   { return reinterpret_cast<Cpaintchat2Doc*>(m_pDocument); }
#endif

