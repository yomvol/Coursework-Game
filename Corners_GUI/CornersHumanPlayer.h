#pragma once
#include "CornersPlayer.h"

class CornersHumanPlayer : public CornersPlayer
{
public:
	CornersHumanPlayer();
	virtual ~CornersHumanPlayer();
	virtual bool MakeMove(unsigned int startrow, unsigned int startcol, unsigned int endrow, unsigned int endcol, unsigned int numWhiteTurns, unsigned int numBlackTurnsunsigned);
	bool IsHuman() { return true; };
};

