#pragma once
#include "Tile.h"

// CCornersBoard
class CCornersGUIDlg;

class CCornersBoard : public CWnd
{
	DECLARE_DYNAMIC(CCornersBoard)

public:
	CCornersBoard();
	virtual ~CCornersBoard();

protected:
	DECLARE_MESSAGE_MAP()
private:
	bool RegisterClass();
public:
	afx_msg void OnPaint();
private:
	const unsigned int boardsize = 8;
	CCornersGUIDlg* manager;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void SetGameManager(CCornersGUIDlg* dlg) { this->manager = dlg; };
private:
	// From pixels to Global Coordinate System
	void FromPxToBCS(CPoint point, unsigned int& xpos, unsigned int& ypos);
private:
	int SelectedXpos;
	int SelectedYpos;
	CRect FromBCSToPxRect(unsigned int x, unsigned int y);
	void DrawWhitePiece(CPaintDC& dc, CRect rect);
	void DrawBlackPiece(CPaintDC& dc, CRect rect);
	void DrawEmptyTile(CPaintDC& dc, CRect rect);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
private:
	int MOverX;
	int MOverY;
	unsigned int AntiFlickeringTimer;
	void HighLightTile(CPaintDC& dc);
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};


