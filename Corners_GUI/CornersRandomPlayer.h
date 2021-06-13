#pragma once
#include "CornersPlayer.h"

class CornersRandomPlayer :  public CornersPlayer
{
private:
	unsigned int* PiecesCoords; //unsigned int PiecesCoords[18];  Array of x1, y1, x2, y2, x3, y3 ... for every piece
	unsigned int prevprevcol, prevprevrow;
public:
	CornersRandomPlayer();
	virtual ~CornersRandomPlayer();
	virtual bool MakeMove(unsigned int startrow, unsigned int startcol, unsigned int endrow, unsigned int endcol, unsigned int numWhiteTurns, unsigned int numBlackTurns);
	void SetPrevCol(unsigned int value) { this->prevcol = value; };
	void SetPrevRow(unsigned int value) { this->prevrow = value; };
	void SetPrevPrevCol(unsigned int value) { this->prevprevcol = value; };
	void SetPrevPrevRow(unsigned int value) { this->prevprevrow = value; };
	bool IsHuman() { return false; };
};

struct Turn
{
	unsigned int startrow, startcol, endrow, endcol;
	int FlowCorrectionValue = 0;
};
