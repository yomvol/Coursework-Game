// CCornersBoard.cpp : implementation file
//
#include "pch.h"
#include "Corners_GUI.h"
#include "CCornersBoard.h"
#include "Corners_GUIDlg.h"

#define CORNERSBOARD_CLASSNAME L"CornersBoard"
// CCornersBoard

IMPLEMENT_DYNAMIC(CCornersBoard, CWnd)

CCornersBoard::CCornersBoard()
{
	manager = nullptr;

	AntiFlickeringTimer = GetTickCount64();
	SelectedXpos = -1;
	SelectedYpos = -1;
	MOverX = -1;
	MOverY = -1;
	if (!this->RegisterClassW())
	{
		// Nothing to free?
	}

}

CCornersBoard::~CCornersBoard()
{}


BEGIN_MESSAGE_MAP(CCornersBoard, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()



// CCornersBoard message handlers




bool CCornersBoard::RegisterClass()
{
	WNDCLASS wndcls;
	HINSTANCE hInst = AfxGetInstanceHandle();

	if (!(::GetClassInfo(hInst, CORNERSBOARD_CLASSNAME, &wndcls))) //returns true - the following is done automatically
	{
		// Otherwise register a new one
		wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
		wndcls.lpfnWndProc = ::DefWindowProc;
		wndcls.cbClsExtra = wndcls.cbWndExtra = 0;
		wndcls.hInstance = hInst;
		wndcls.hIcon = NULL;
		wndcls.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		wndcls.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
		wndcls.lpszMenuName = NULL;
		wndcls.lpszClassName = CORNERSBOARD_CLASSNAME;
	}

	if (!AfxRegisterClass(&wndcls))
	{
		AfxThrowResourceException();
		return FALSE;
	}

	return TRUE;
}


void CCornersBoard::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CWnd::OnPaint() for painting messages
	CRect rect;
	GetClientRect(&rect);
	CPen MyPen, MyPen2;
	HGDIOBJ DefaultPen;
	MyPen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	MyPen2.CreatePen(PS_SOLID, 1, RGB(50, 50, 50));
	DefaultPen = dc.SelectObject(MyPen);

	dc.MoveTo(1, 1);
	dc.LineTo(rect.right - 1, 1);
	dc.LineTo(rect.right - 1, rect.bottom - 1);
	dc.LineTo(1, rect.bottom - 1);
	dc.LineTo(1, 1);

	int Offset = 20; //px
	int HorGridSize = (rect.right - 2 * Offset) / boardsize;
	int VerGridSize = (rect.bottom - 2 * Offset) / boardsize;

	this->HighLightTile(dc);

	for (int i = 0; i < boardsize + 1; i++)
	{
		if (i == 1)
			dc.SelectObject(MyPen2);
		if (i == 8)
			dc.SelectObject(MyPen);
		dc.MoveTo(Offset + i * HorGridSize, Offset);
		dc.LineTo(Offset + i * HorGridSize, rect.bottom - Offset);
		dc.MoveTo(Offset, i * VerGridSize + Offset);
		dc.LineTo(rect.right - Offset, i * VerGridSize + Offset);
	}

	dc.SetTextColor(RGB(168, 86, 3));
	dc.SetTextAlign(TA_TOP | TA_LEFT);
	dc.SetBkMode(TRANSPARENT);
	CString str;
	for (int i = 0; i < boardsize; i++)
	{
		str.Format(L"%d", 8 - i);
		dc.TextOutW(Offset / 2 - 5, Offset + i * VerGridSize + 15, str);
		str.Empty();
		str.Format(L"%c", 65 + i);
		dc.TextOutW(Offset + i * HorGridSize + 0.5 * HorGridSize - 10, Offset / 2 - 10, str);
		str.Empty();
	}

	if (this->manager == nullptr || this->manager->GetBoardMod() == nullptr)
		return;

	for (unsigned int i = 0; i < boardsize; i++)
		for (unsigned int j = 0; j < boardsize; j++)
		{
			switch (this->manager->GetBoardMod()->GetTile(i, j))
			{
			case Tile_White:
				this->DrawWhitePiece(dc, this->FromBCSToPxRect(i, j));
				break;
			case Tile_Black:
				this->DrawBlackPiece(dc, this->FromBCSToPxRect(i, j));
				break;
			case Tile_Empty:
				this->DrawEmptyTile(dc, this->FromBCSToPxRect(i, j));
				break;
			}
		}

	dc.SelectObject(DefaultPen);
	MyPen.DeleteObject();
	MyPen2.DeleteObject();
}

// From pixels to Board Coordinate System
void CCornersBoard::FromPxToBCS(CPoint point, unsigned int& xpos, unsigned int& ypos)
{
	CRect rect;
	GetClientRect(&rect);
	int Offset = 20; //px
	int HorGridSize = (rect.right - 2 * Offset) / boardsize;
	int VerGridSize = (rect.bottom - 2 * Offset) / boardsize;
	for (unsigned int i = 0; i < boardsize; i++)
	{
		if ((point.x >= Offset + i * HorGridSize) && (point.x < Offset + (i + 1) * HorGridSize))
			xpos = i;
		if ((point.y >= Offset + i * VerGridSize) && (point.y < Offset + (i + 1) * VerGridSize))
			ypos = i;
	}
}

void CCornersBoard::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (this->manager->GetGameInProgress() == false || this->manager->GetCurPlayer()->IsHuman() == false)
	{
		CWnd::OnLButtonDown(nFlags, point);
		return;
	}
	
	unsigned int x, y;
	this->FromPxToBCS(point, x, y);
	if ((SelectedXpos == -1 || SelectedYpos == -1) && this->manager->GetBoardMod()->GetTile(x, y) != Tile_Empty && this->manager->GetCurPlayer()->GetDidHop() == false) // temporary logic
	{
		if (this->manager->GetBoardMod()->CheckLegalPick(x, y, this->manager->GetCurPlayer()->GetPColor()))
		{
			SelectedXpos = x;
			SelectedYpos = y;
			Invalidate();
		}
		else
		{
			this->manager->GetLog()->AddString(L"Try picking your own pieces, please.");
			CWnd::OnLButtonDown(nFlags, point);
			return;
		}
	}
	else if (SelectedXpos >= 0 && SelectedYpos >= 0) //If clicked on empty tile, flow won`t pass
	{
		if (SelectedXpos != x || SelectedYpos != y)
		{
			if (this->manager->GetCurPlayer()->MakeMove(SelectedYpos, SelectedXpos, y, x, 0, 0) == true)
			{
				this->manager->Judge();
				SelectedXpos = x;
				SelectedYpos = y;
			}
			else
			{
				this->manager->GetLog()->AddString(L"Incorrect move.");
			}
		}
		if (this->manager->GetCurPlayer()->GetDidHop() == false)
		{
			SelectedXpos = SelectedYpos = -1;
		}
		
		this->Invalidate();
	}

	CWnd::OnLButtonDown(nFlags, point);
}


CRect CCornersBoard::FromBCSToPxRect(unsigned int x, unsigned int y)
{
	CRect rect;
	CRect CustomCtrlRect;
	GetClientRect(CustomCtrlRect);
	int Offset = 20; //px
	int HorGridSize = (CustomCtrlRect.right - 2 * Offset) / boardsize;
	int VerGridSize = (CustomCtrlRect.bottom - 2 * Offset) / boardsize;

	rect.left = Offset + HorGridSize * x + 1;
	rect.top = Offset + VerGridSize * y + 1;
	rect.right = Offset + HorGridSize * (x + 1) - 1;
	rect.bottom = Offset + VerGridSize * (y + 1) - 1;

	return rect;
}


void CCornersBoard::DrawWhitePiece(CPaintDC& dc, CRect rect)
{
	CPen pen;
	CBrush brush;
	brush.CreateSolidBrush(RGB(246, 232, 202));
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HGDIOBJ DefaultPen = dc.SelectObject(pen);
	HGDIOBJ DefaultBrush = dc.SelectObject(brush);

	dc.Ellipse(rect.left + 6, rect.top + 10, rect.right - 6, rect.bottom - 10);

	dc.SelectObject(DefaultPen);
	dc.SelectObject(DefaultBrush);
	pen.DeleteObject();
	brush.DeleteObject();
}


void CCornersBoard::DrawBlackPiece(CPaintDC& dc, CRect rect)
{
	CPen pen;
	CBrush brush;
	brush.CreateSolidBrush(RGB(30, 30, 30));
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HGDIOBJ DefaultPen = dc.SelectObject(pen);
	HGDIOBJ DefaultBrush = dc.SelectObject(brush);

	dc.Ellipse(rect.left + 6, rect.top + 10, rect.right - 6, rect.bottom - 10);

	dc.SelectObject(DefaultPen);
	dc.SelectObject(DefaultBrush);
	pen.DeleteObject();
	brush.DeleteObject();
}


void CCornersBoard::DrawEmptyTile(CPaintDC& dc, CRect rect)
{
	HGDIOBJ DefaultPen = dc.SelectObject(GetStockObject(NULL_PEN));
	HGDIOBJ DefaultBrush = dc.SelectObject(GetStockObject(HOLLOW_BRUSH));
	dc.Rectangle(rect.left + 2, rect.top + 2, rect.right - 2, rect.bottom - 2);
	dc.SelectObject(DefaultBrush);
	dc.SelectObject(DefaultPen);
}


void CCornersBoard::OnMouseMove(UINT nFlags, CPoint point)
{
	unsigned int diff = GetTickCount64() - AntiFlickeringTimer;
	if (diff > 50)
	{
		unsigned int x, y;
		FromPxToBCS(point, x, y);
		if (x != MOverX || y != MOverY)
		{
			MOverX = x;
			MOverY = y;
			this->Invalidate();
		}
		AntiFlickeringTimer = GetTickCount64();
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = this->m_hWnd;
		tme.dwFlags = TME_LEAVE;
		tme.dwHoverTime = HOVER_DEFAULT;
		TrackMouseEvent(&tme);
	}

	CWnd::OnMouseMove(nFlags, point);
}


void CCornersBoard::OnMouseLeave()
{
	MOverX = -1;
	MOverY = -1;
	this->Invalidate();
	CWnd::OnMouseLeave();
}


void CCornersBoard::HighLightTile(CPaintDC& dc)
{
	if (MOverX >= 0 && MOverY >= 0)
	{
		CRect rect = FromBCSToPxRect(MOverX, MOverY);
		CBrush brush;
		brush.CreateSolidBrush(RGB(255, 10, 251));
		HGDIOBJ DefaultBrush = dc.SelectObject(brush);

		dc.Rectangle(rect);

		dc.SelectObject(DefaultBrush);
		brush.DeleteObject();
	}

	if (this->manager == nullptr || this->manager->GetBoardMod() == nullptr)
		return;

	if (SelectedXpos >= 0 && SelectedYpos >= 0)
	{
		CRect rect = FromBCSToPxRect(SelectedXpos, SelectedYpos);
		CBrush brush;
		brush.CreateSolidBrush(RGB(18, 196, 44));
		HGDIOBJ DefaultBrush = dc.SelectObject(brush);

		dc.Rectangle(rect);

		dc.SelectObject(DefaultBrush);
		brush.DeleteObject();
	}
}


void CCornersBoard::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (this->manager->GetGameInProgress() == false || this->manager->GetCurPlayer()->IsHuman() == false || this->manager->GetCurPlayer()->GetDidHop() == false)
	{
		CWnd::OnRButtonDown(nFlags, point);
		return;
	}

	CornersPlayer* P = this->manager->GetCurPlayer();
	if (P->IsHuman() == true)
	{
		P->SetIsPassingTurn(true);
		manager->Judge();
		SelectedXpos = -1;
		SelectedYpos = -1;
		Invalidate();
	}

	CWnd::OnRButtonDown(nFlags, point);
}


void CCornersBoard::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (this->manager->GetGameInProgress() == false || this->manager->GetCurPlayer()->IsHuman() == false)
	{
		CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
		return;
	}

	if (nChar == 'S' || nChar == 's')
	{
		CornersPlayer* P = this->manager->GetCurPlayer();
		P->SetIsSurrendering(true);
		manager->Judge();
	}

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}
