#include "pch.h"
#include "CornersBoardModel.h"

CornersBoardModel::CornersBoardModel()
{
	for (unsigned int i = 0; i < boardsize; i++)
		for (unsigned int j = 0; j < boardsize; j++)
			tiles[i][j] = Tile_Empty;
	for (unsigned int i = 0; i < 3; i++)
		for (unsigned int j = 5; j < boardsize; j++)
			tiles[j][i] = Tile_White;
	for (unsigned int i = 5; i < boardsize; i++)
		for (unsigned int j = 0; j < 3; j++)
			tiles[j][i] = Tile_Black;
}

CornersBoardModel::CornersBoardModel(CornersBoardModel* board)
{
	for (unsigned int i = 0; i < boardsize; i++)
		for (unsigned int j = 0; j < boardsize; j++)
			tiles[i][j] = board->tiles[i][j];
}

CornersBoardModel::~CornersBoardModel()
{}

void CornersBoardModel::SetTile(unsigned int xpos, unsigned int ypos, Tile t)
{
	tiles[ypos][xpos] = t;
}

bool CornersBoardModel::CheckLegalPick(unsigned int startxpos, unsigned int startypos, Tile t)
{
	if (t != tiles[startypos][startxpos])
		return false;
	else
		return true;
}

bool CornersBoardModel::CheckLegal(int startxpos, int startypos, int endxpos, int endypos)
{
	if ((startxpos < 0) || (startxpos > boardsize - 1) || (startypos < 0) || (startypos > boardsize - 1) || (endxpos < 0) || (endxpos > boardsize - 1) || (endypos < 0) || (endypos > boardsize - 1))
		return false;
	bool VerticalMove = (startxpos == endxpos ? true : false);
	bool HorizontalMove = (startypos == endypos ? true : false);
	if ((VerticalMove && HorizontalMove) || !(VerticalMove || HorizontalMove)) //Diagonal moves and idling are banned
		return false;
	int diffy = int(endypos - startypos);
	int diffx = int(endxpos - startxpos);
	unsigned int adiffy = abs(diffy);
	unsigned int adiffx = abs(diffx);
	if (VerticalMove)
		if (adiffy > 2)
			return false;
		else if (diffy == -2 && tiles[startypos - 1][startxpos] == Tile_Empty) //UP
			return false;
		else if (diffy == 2 && tiles[startypos + 1][startxpos] == Tile_Empty) //DOWN
			return false;
	if (HorizontalMove)
		if (adiffx > 2) //Check adjacent piece
			return false;
		else if (diffx == -2 && tiles[startypos][startxpos - 1] == Tile_Empty) //LEFT
			return false;
		else if (diffx == 2 && tiles[startypos][startxpos + 1] == Tile_Empty) //RIGHT
			return false;
	if (tiles[endypos][endxpos] != Tile_Empty)
		return false;

	return true;
}

unsigned int CornersBoardModel::WhitesOnBlackBase()
{
	unsigned int counter = 0;
	for (unsigned int i = 5; i < boardsize; i++)
		for (unsigned int j = 0; j < 3; j++)
			if (tiles[j][i] == Tile_White)
				counter++;
	return counter;
}

unsigned int CornersBoardModel::BlacksOnWhiteBase()
{
	unsigned int counter = 0;
	for (unsigned int i = 0; i < 3; i++)
		for (unsigned int j = 5; j < boardsize; j++)
			if (tiles[j][i] == Tile_Black)
				counter++;
	return counter;
}

unsigned int CornersBoardModel::WhitesOnWhiteBase()
{
	unsigned int counter = 0;
	for (unsigned int i = 0; i < 3; i++)
		for (unsigned int j = 5; j < boardsize; j++)
			if (tiles[j][i] == Tile_White)
				counter++;
	return counter;
}

unsigned int CornersBoardModel::BlacksOnBlackBase()
{
	unsigned int counter = 0;
	for (unsigned int i = 5; i < boardsize; i++)
		for (unsigned int j = 0; j < 3; j++)
			if (tiles[j][i] == Tile_Black)
				counter++;
	return counter;
}

unsigned int* CornersBoardModel::FindPieces(Tile tile)
{
	static unsigned int piecesCoords[18];
	unsigned int iter = 0;
	for (unsigned int i = 0; i < boardsize; i++)
		for (unsigned int j = 0; j < boardsize; j++)
			if (tiles[j][i] == tile)
			{
				piecesCoords[iter] = i; //X first, Y second
				piecesCoords[iter + 1] = j;
				iter = iter + 2;
			}
	return piecesCoords;
}

int CornersBoardModel::GetLegalHop(unsigned int startxpos, unsigned int startypos, unsigned int previousxpos, unsigned int previousypos)
{
	int dir;
	for (int i = 0; i < 10; i++)
	{
		dir = rand() % 4;
		switch (dir)
		{
		case 0: //DOWN
			if (startypos >= 6)
				break;
			if (tiles[startypos + 1][startxpos] != Tile_Empty && tiles[startypos + 2][startxpos] == Tile_Empty && previousypos != startypos + 2)
				return 0;
			break;
		case 1: //LEFT
			if (startxpos <= 1)
				break;
			if (tiles[startypos][startxpos - 1] != Tile_Empty && tiles[startypos][startxpos - 2] == Tile_Empty && previousxpos != startxpos - 2)
				return 1;
			break;
		case 2: //UP
			if (startypos <= 1)
				break;
			if (tiles[startypos - 1][startxpos] != Tile_Empty && tiles[startypos - 2][startxpos] == Tile_Empty && previousypos != startypos - 2)
				return 2;
			break;
		case 3: //RIGHT
			if (startxpos >= 6)
				break;
			if (tiles[startypos][startxpos + 1] != Tile_Empty && tiles[startypos][startxpos + 2] == Tile_Empty && previousxpos != startxpos + 2)
				return 3;
			break;
		default:
			throw;
			break;
		}
	}
	return -1; //Stand still
}

const int CornersBoardModel::mask[8][8] = {
	0, -3, -3, -3, -4, -5, -5, -5,
	3, 0, -2, -3, -4, -5, -5, -5, 
	3, 2, 0, -2, -4, -5, -5, -5,
	3, 3, 2, 0, -3, -4, -4, -4,
	4, 4, 4, 3, 0, -2, -3, -3,
	5, 5, 5, 4, 2, 0, -2, -3,
	5, 5, 5, 4, 3, 2, 0, -3,
	5, 5, 5, 4, 3, 3, 3, 0
};

int CornersBoardModel::GetField(unsigned int xpos, unsigned int ypos)
{
	return mask[ypos][xpos];
}