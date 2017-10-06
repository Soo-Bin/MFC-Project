// Element.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "paintchat2.h"
#include "Element.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// CElement

CElement::CElement()
{
}

CElement::~CElement()
{
}

void CElement::Draw(CDC *pDC, CRect &rect)
{

}

// 마지막 포인터 값 변경
void CElement::ChangePoint(CPoint &Pos)
{
	m_EndPoint = Pos;
}

// 펜 사이즈 변경
void CElement::ChangePenSize(UINT Pen)
{
	m_PenSize = Pen;
}
//지우개 사이즈 변경
void CElement::ChangeEraseSize(UINT Erase)
{
	m_EraseSize = Erase;
}

// 펜 색깔 변경
void CElement::ChangePenColor(COLORREF Pen)
{
	m_PenColor = Pen;
}
// CElement 멤버 함수
