#pragma once
#include "Tile.h"

class CornersBoard
{
private:
	const unsigned int boardsize = 8;
	Tile** tiles;
	static const int mask[8][8];

public:
	CornersBoard();
	CornersBoard(CornersBoard* board);
	virtual ~CornersBoard();
	void Show();
	void SetTile(unsigned int xpos, unsigned int ypos, Tile t);
	bool CheckLegal(int startxpos, int startypos, int endxpos, int endypos);
	bool CheckLegalPick(unsigned int startxpos, unsigned int startypos, Tile t);
	unsigned int WhitesOnBlackBase(); //ALLYOURBASEAREBELONGTOUS
	unsigned int BlacksOnWhiteBase();
	unsigned int WhitesOnWhiteBase();
	unsigned int BlacksOnBlackBase();
	unsigned int* FindPieces(Tile tile);
	int GetLegalHop(unsigned int startxpos, unsigned int startypos, unsigned int previousxpos, unsigned int previousypos);
	static int GetField(unsigned int xpos, unsigned int ypos);
};

