
// paintchat2Doc.h : Cpaintchat2Doc 클래스의 인터페이스
//


#pragma once


class Cpaintchat2Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	Cpaintchat2Doc();
	DECLARE_DYNCREATE(Cpaintchat2Doc)

// 특성입니다.
public:
	UINT	m_PenSize;
	UINT	m_EraseSize;
	UINT	m_CheckPenSize;
	UINT	m_CheckElement;
	UINT	m_CheckErase;
	COLORREF	m_PenColor;
	WORD		m_Element;
	CPtrList	P_Container;
// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	WORD GetElementType() const;		//현재 도형 타입 반환
	UINT GetElementPenSize()const;		//펜 사이즈 반환
	COLORREF GetElementPenColor()const;	//펜 색깔 반환
	UINT GetCheckElement()const;		//현재 선택된 도형 반환
	UINT GetCheckPenSize()const;		//현재 선택된 펜 사이즈 반환
	void StatusBarElementName(UINT nID);
	void StatusBarPenSize(UINT nID);
	virtual ~Cpaintchat2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPen();							//펜 색깔 변경

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
