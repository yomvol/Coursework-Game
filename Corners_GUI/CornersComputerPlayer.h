#pragma once
#include "CornersPlayer.h"
class CornersComputerPlayer :  public CornersPlayer
{
private:
	unsigned int* PiecesCoords; //Array of x1, y1, x2, y2, x3, y3 ... for every piece
	unsigned int prevprevcol, prevprevrow; //Coordinates from where a piece hopped are stored in order not to come back
	const unsigned int NumOfGames = 500;
public:
	CornersComputerPlayer();
	virtual ~CornersComputerPlayer();
	virtual bool MakeMove(unsigned int startrow, unsigned int startcol, unsigned int endrow, unsigned int endcol, unsigned int numWhiteTurns, unsigned int numBlackTurns);
	void SetBoard(CornersBoardModel* board);
	bool IsHuman() { return false; };
};

