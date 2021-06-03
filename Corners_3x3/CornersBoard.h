#pragma once
#include "Tile.h"

class CornersBoard
{
private:
	const int boardsize = 8;
	Tile** tiles;

public:
	CornersBoard();
	CornersBoard(CornersBoard* board);
	virtual ~CornersBoard();
	void Show();
	void SetTile(unsigned int xpos, unsigned int ypos, Tile t);
	bool CheckLegal(unsigned int startxpos, unsigned int startypos, unsigned int endxpos, unsigned int endypos);
	bool CheckLegalPick(unsigned int startxpos, unsigned int startypos, Tile t);
	unsigned int WhitesOnBlackBase(); //ALLYOURBASEAREBELONGTOUS
	unsigned int BlacksOnWhiteBase();
	unsigned int WhitesOnWhiteBase();
	unsigned int BlacksOnBlackBase();
};

