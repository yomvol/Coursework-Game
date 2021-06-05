#pragma once
#include "CornersPlayer.h"
class CornersComputerPlayer :  public CornersPlayer
{
private:
	unsigned int* PiecesCoords; //Array of x1, y1, x2, y2, x3, y3 ... for every piece
	unsigned int prevprevcol, prevprevrow; //Coordinates from where a piece hopped are stored in order not to come back

public:
	CornersComputerPlayer();
	virtual ~CornersComputerPlayer();
	virtual bool MakeMove(unsigned int numWhiteTurns, unsigned int numBlackTurns);
	void SetBoard(CornersBoard* board);
};

