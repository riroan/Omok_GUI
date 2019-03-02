
// Omok_MFCView.cpp: COmokMFCView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Omok_MFC.h"
#endif

#include "Omok_MFCDoc.h"
#include "Omok_MFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define BOARD_SIZE 19
#define NONE 0
#define BLACK 1
#define WHITE 2

// COmokMFCView

IMPLEMENT_DYNCREATE(COmokMFCView, CView)

BEGIN_MESSAGE_MAP(COmokMFCView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COmokMFCView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// COmokMFCView 생성/소멸

COmokMFCView::COmokMFCView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_player = BLACK;
	m_board = new int*[BOARD_SIZE];
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		m_board[i] = new int[BOARD_SIZE];
		for (int j = 0; j < BOARD_SIZE; j++)
			m_board[i][j] = NONE;
	}
	m_win = NONE;
}

COmokMFCView::~COmokMFCView()
{
	for (int i = 0; i < BOARD_SIZE; i++)
		delete[] m_board[i];
	delete[] m_board;
}

BOOL COmokMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// COmokMFCView 그리기

void COmokMFCView::OnDraw(CDC* pDC)
{
	COmokMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	CBrush brush, *oldBrush;
	brush.CreateSolidBrush(RGB(239, 228, 176));
	oldBrush = pDC->SelectObject(&brush);

	CRect border;
	border.left = 15;
	border.top = 15;
	border.right = 15 + 30 * BOARD_SIZE;
	border.bottom = 15 + 30 * BOARD_SIZE;
	pDC->Rectangle(border.left, border.top, border.right, border.bottom);
	pDC->SelectObject(oldBrush);
	brush.DeleteObject();

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		CPoint point;
		point.x = 30 * (i + 1);
		point.y = 30;
		pDC->MoveTo(point);
		point.y = 30 * BOARD_SIZE;
		pDC->LineTo(point);

		point.y = 30 * (i + 1);
		point.x = 30;
		pDC->MoveTo(point);
		point.x = 30 * BOARD_SIZE;
		pDC->LineTo(point);
	}

	CPen pen, *oldPen;

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (m_board[i][j] != NONE)
			{
				if (m_board[i][j] == BLACK)
				{
					brush.CreateSolidBrush(RGB(0, 0, 0));
					pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				}
				else if (m_board[i][j] == WHITE)
				{
					brush.CreateSolidBrush(RGB(255, 255, 255));
					pen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
				}
				oldPen = pDC->SelectObject(&pen);
				oldBrush = pDC->SelectObject(&brush);

				pDC->Ellipse(30 * j + 15, 30 * i + 15, 30 * (j + 1) + 15, 30 * (i + 1) + 15);

				pDC->SelectObject(oldPen);
				pDC->SelectObject(oldBrush);
				pen.DeleteObject();
				brush.DeleteObject();
			}
		}
	}

	Winner();
	if (m_win)
	{
		if(m_win == BLACK)
			MessageBox(_T("black win"), _T("Game Over"), MB_ICONASTERISK);
		if (m_win == WHITE)
			MessageBox(_T("white win"), _T("Game Over"), MB_ICONASTERISK);

		exit(0);
	}
}


// COmokMFCView 인쇄


void COmokMFCView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL COmokMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void COmokMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void COmokMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void COmokMFCView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void COmokMFCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// COmokMFCView 진단

#ifdef _DEBUG
void COmokMFCView::AssertValid() const
{
	CView::AssertValid();
}

void COmokMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COmokMFCDoc* COmokMFCView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COmokMFCDoc)));
	return (COmokMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// COmokMFCView 메시지 처리기


void COmokMFCView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnChar(nChar, nRepCnt, nFlags);
}


void COmokMFCView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnLButtonDown(nFlags, point);
}


void COmokMFCView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int x_ = point.x;
	int y_ = point.y;

	if (x_ < 15 || x_>15 + 30 * BOARD_SIZE || y_ < 15 || y_>15 + 30 * BOARD_SIZE)
		return;

	x_ -= 15; y_ -= 15;
	x_ /= 30; y_ /= 30;

	if (m_board[y_][x_] != NONE)
		return;

	m_board[y_][x_] = m_player;

	m_player = BLACK + WHITE - m_player;

	Invalidate(false);

	CView::OnLButtonUp(nFlags, point);
}

void COmokMFCView::Winner()
{
	// TODO: 여기에 구현 코드 추가.
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 2; j < BOARD_SIZE - 2; j++)
			if (m_board[i][j - 2] == m_board[i][j - 1] && m_board[i][j - 1] == m_board[i][j] && m_board[i][j] == m_board[i][j + 1] && m_board[i][j + 1] == m_board[i][j + 2])
			{
				if (m_board[i][j] == BLACK)
				{
					m_win = BLACK;
					return;
				}
				else if (m_board[i][j] == WHITE)
				{
					m_win = WHITE;
					return;
				}
			}

	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 2; j < BOARD_SIZE - 2; j++)
			if (m_board[j - 2][i] == m_board[j - 1][i] && m_board[j - 1][i] == m_board[j][i] && m_board[j][i] == m_board[j + 1][i] && m_board[j + 1][i] == m_board[j + 2][i])
			{
				if (m_board[j][i] == BLACK)
				{
					m_win = BLACK;
					return;
				}
				else if (m_board[j][i] == WHITE)
				{
					m_win = WHITE;
					return;
				}
			}

	for (int i = 2; i < BOARD_SIZE - 2; i++)
		for (int j = 2; j < BOARD_SIZE - 2; j++)
			if (m_board[i - 2][j - 2] == m_board[i - 1][j - 1] && m_board[i - 1][j - 1] == m_board[i][j] && m_board[i][j] == m_board[i + 1][j + 1] && m_board[i + 1][j + 1] == m_board[i + 2][j + 2])
			{
				if (m_board[i][j] == BLACK)
				{
					m_win = BLACK;
					return;
				}
				else if (m_board[i][j] == WHITE)
				{
					m_win = WHITE;
					return;
				}
			}

	for (int i = 2; i < BOARD_SIZE - 2; i++)
		for (int j = 2; j < BOARD_SIZE - 2; j++)
			if (m_board[i - 2][j + 2] == m_board[i - 1][j + 1] && m_board[i - 1][j + 1] == m_board[i][j] && m_board[i][j] == m_board[i + 1][j - 1] && m_board[i + 1][j - 1] == m_board[i + 2][j - 2])
			{
				if (m_board[i][j] == BLACK)
				{
					m_win = BLACK;
					return;
				}
				else if (m_board[i][j] == WHITE)
				{
					m_win = WHITE;
					return;
				}
			}
}