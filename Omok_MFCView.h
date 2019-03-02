
// Omok_MFCView.h: COmokMFCView 클래스의 인터페이스
//

#pragma once


class COmokMFCView : public CView
{
protected: // serialization에서만 만들어집니다.
	COmokMFCView() noexcept;
	DECLARE_DYNCREATE(COmokMFCView)

// 특성입니다.
public:
	COmokMFCDoc* GetDocument() const;

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
	virtual ~COmokMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	short m_player;
	int **m_board;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void Winner();
	short m_win;
};

#ifndef _DEBUG  // Omok_MFCView.cpp의 디버그 버전
inline COmokMFCDoc* COmokMFCView::GetDocument() const
   { return reinterpret_cast<COmokMFCDoc*>(m_pDocument); }
#endif

