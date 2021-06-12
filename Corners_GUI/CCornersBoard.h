#pragma once
#include "Tile.h"

// CCornersBoard

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
	static const unsigned int boardsize = 8;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
private:
	// From pixels to Global Coordinate System
	void FromPxToBCS(CPoint point, unsigned int& xpos, unsigned int& ypos);
	Tile tiles[boardsize][boardsize];
public:
	void SetTile(unsigned int xpos, unsigned int ypos, Tile tile);
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
};


