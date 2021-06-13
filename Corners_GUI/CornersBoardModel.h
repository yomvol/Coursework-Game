#pragma once
#include "Tile.h"

class CornersBoardModel
{
private:
	static const unsigned int boardsize = 8;
	Tile tiles[boardsize][boardsize];
	static const int mask[8][8];

public:
	CornersBoardModel();
	CornersBoardModel(CornersBoardModel* board);
	virtual ~CornersBoardModel();
	void SetTile(unsigned int xpos, unsigned int ypos, Tile t);
	bool CheckLegal(int startxpos, int startypos, int endxpos, int endypos);
	bool CheckLegalPick(unsigned int startxpos, unsigned int startypos, Tile t);
	unsigned int WhitesOnBlackBase(); //ALLYOURBASEAREBELONGTOUS
	unsigned int BlacksOnWhiteBase();
	unsigned int WhitesOnWhiteBase();
	unsigned int BlacksOnBlackBase();
	unsigned int* FindPieces(Tile tile);
	int GetLegalHop(unsigned int startxpos, unsigned int startypos, unsigned int previousxpos, unsigned int previousypos);
	static int GetField(unsigned int xpos, unsigned int ypos); // scalar field
	Tile GetTile(unsigned int xpos, unsigned int ypos) { return tiles[ypos][xpos]; };
};

