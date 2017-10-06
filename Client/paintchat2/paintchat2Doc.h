
// paintchat2Doc.h : Cpaintchat2Doc Ŭ������ �������̽�
//


#pragma once


class Cpaintchat2Doc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	Cpaintchat2Doc();
	DECLARE_DYNCREATE(Cpaintchat2Doc)

// Ư���Դϴ�.
public:
	UINT	m_PenSize;
	UINT	m_EraseSize;
	UINT	m_CheckPenSize;
	UINT	m_CheckElement;
	UINT	m_CheckErase;
	COLORREF	m_PenColor;
	WORD		m_Element;
	CPtrList	P_Container;
// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	WORD GetElementType() const;		//���� ���� Ÿ�� ��ȯ
	UINT GetElementPenSize()const;		//�� ������ ��ȯ
	COLORREF GetElementPenColor()const;	//�� ���� ��ȯ
	UINT GetCheckElement()const;		//���� ���õ� ���� ��ȯ
	UINT GetCheckPenSize()const;		//���� ���õ� �� ������ ��ȯ
	void StatusBarElementName(UINT nID);
	void StatusBarPenSize(UINT nID);
	virtual ~Cpaintchat2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPen();							//�� ���� ����

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
