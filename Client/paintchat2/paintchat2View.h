
// paintchat2View.h : Cpaintchat2View 클래스의 인터페이스
//

#pragma once

#include "Element.h"

class Cpaintchat2View : public CView
{
protected: // serialization에서만 만들어집니다.
	Cpaintchat2View();
	DECLARE_DYNCREATE(Cpaintchat2View)

// 특성입니다.
public:
	Cpaintchat2Doc* GetDocument() const;

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
	virtual ~Cpaintchat2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
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

#ifndef _DEBUG  // paintchat2View.cpp의 디버그 버전
inline Cpaintchat2Doc* Cpaintchat2View::GetDocument() const
   { return reinterpret_cast<Cpaintchat2Doc*>(m_pDocument); }
#endif

