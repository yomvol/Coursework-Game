#pragma once
#include "Tile.h"

class CornersBoard
{
private:
	const int boardsize = 8;
	Tile** tiles;
	bool Victory = false;

public:
	CornersBoard();
	CornersBoard(CornersBoard* board);
	virtual ~CornersBoard();
	void Show();
	void SetTile(unsigned int xpos, unsigned int ypos, Tile t);
	bool CheckLegal(unsigned int startxpos, unsigned int startypos, unsigned int endxpos, unsigned int endypos);
	bool CheckEndCondition();
	bool IsVictory();
	bool CheckLegalPick(unsigned int startxpos, unsigned int startypos, Tile t);
};

