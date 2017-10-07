
// server2View.h : Cserver2View Ŭ������ �������̽�
//

#pragma once

#include "Element.h"

class Cserver2View : public CView
{
protected: // serialization������ ��������ϴ�.
	Cserver2View();
	DECLARE_DYNCREATE(Cserver2View)

// Ư���Դϴ�.
public:
	Cserver2Doc* GetDocument() const;

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
	virtual ~Cserver2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
	CPoint m_ptNow;
	CPoint m_ptOld;
	CElement *m_TempElement;
	BOOL Connect;
	COLORREF m_colLine;
	COLORREF m_colLineXor;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

public:
	afx_msg void OnEditUndo();
};

#ifndef _DEBUG  // server2View.cpp�� ����� ����
inline Cserver2Doc* Cserver2View::GetDocument() const
   { return reinterpret_cast<Cserver2Doc*>(m_pDocument); }
#endif

