// Element.cpp : ���� �����Դϴ�.
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

// ������ ������ �� ����
void CElement::ChangePoint(CPoint &Pos)
{
	m_EndPoint = Pos;
}

// �� ������ ����
void CElement::ChangePenSize(UINT Pen)
{
	m_PenSize = Pen;
}
//���찳 ������ ����
void CElement::ChangeEraseSize(UINT Erase)
{
	m_EraseSize = Erase;
}

// �� ���� ����
void CElement::ChangePenColor(COLORREF Pen)
{
	m_PenColor = Pen;
}
// CElement ��� �Լ�
