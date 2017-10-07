
// server2View.h : Cserver2View 클래스의 인터페이스
//

#pragma once

#include "Element.h"

class Cserver2View : public CView
{
protected: // serialization에서만 만들어집니다.
	Cserver2View();
	DECLARE_DYNCREATE(Cserver2View)

// 특성입니다.
public:
	Cserver2Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	CElement * CreateElement();
	virtual ~Cserver2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
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

#ifndef _DEBUG  // server2View.cpp의 디버그 버전
inline Cserver2Doc* Cserver2View::GetDocument() const
   { return reinterpret_cast<Cserver2Doc*>(m_pDocument); }
#endif

