#include "pch.h"
#include "CornersBoard.h"

CornersBoard::CornersBoard()
{
	tiles = new Tile * [boardsize];
	for (unsigned int i = 0; i < boardsize; i++)
		tiles[i] = new Tile [boardsize];
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

CornersBoard::CornersBoard(CornersBoard* board) 
{
	tiles = new Tile * [boardsize];
	for (unsigned int i = 0; i < boardsize; i++)
		tiles[i] = new Tile[boardsize];
	for (unsigned int i = 0; i < boardsize; i++)
		for (unsigned int j = 0; j < boardsize; j++)
			tiles[i][j] = board->tiles[i][j];
}

CornersBoard::~CornersBoard()
{
	for (unsigned int i = 0; i < boardsize; i++)
		delete[] tiles[i];
	delete[] tiles;
	tiles = nullptr;
}

void CornersBoard::Show()
{
	cout << "  ";
	cout << "	  A B C D E F G H";
	cout << endl;
	short counter = boardsize;
	for (unsigned int i = 0; i < boardsize; i++)
	{
		cout << "	" << counter << " ";
		for (unsigned int j = 0; j < boardsize; j++)
		{
			switch (tiles[i][j])
			{
			case Tile_White:
				cout << "@";
				break;
			case Tile_Black:
				cout << "*";
				break;
			case Tile_Empty:
				cout << ".";
				break;
			}
			cout << " ";
		}
		cout << endl;
		counter--;
	}
	cout << "	  A B C D E F G H";
	cout << endl;
}

void CornersBoard::SetTile(unsigned int xpos, unsigned int ypos, Tile t)
{
	tiles[ypos][xpos] = t;
}

bool CornersBoard::CheckLegalPick(unsigned int startxpos, unsigned int startypos, Tile t)
{
	if (t != tiles[startypos][startxpos])
		return false;
	else
		return true;
}

bool CornersBoard::CheckLegal(int startxpos, int startypos, int endxpos, int endypos)
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

unsigned int CornersBoard::WhitesOnBlackBase()
{
	unsigned int counter = 0;
	for (unsigned int i = 5; i < boardsize; i++)
		for (unsigned int j = 0; j < 3; j++)
			if (tiles[j][i] == Tile_White)
				counter++;
	return counter;
}

unsigned int CornersBoard::BlacksOnWhiteBase()
{
	unsigned int counter = 0;
	for (unsigned int i = 0; i < 3; i++)
		for (unsigned int j = 5; j < boardsize; j++)
			if (tiles[j][i] == Tile_Black)
				counter++;
	return counter;
}

unsigned int CornersBoard::WhitesOnWhiteBase()
{
	unsigned int counter = 0;
	for (unsigned int i = 0; i < 3; i++)
		for (unsigned int j = 5; j < boardsize; j++)
			if (tiles[j][i] == Tile_White)
				counter++;
	return counter;
}

unsigned int CornersBoard::BlacksOnBlackBase()
{
	unsigned int counter = 0;
	for (unsigned int i = 5; i < boardsize; i++)
		for (unsigned int j = 0; j < 3; j++)
			if (tiles[j][i] == Tile_Black)
				counter++;
	return counter;
}

unsigned int* CornersBoard::FindPieces(Tile tile)
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

int CornersBoard::GetLegalHop(unsigned int startxpos, unsigned int startypos, unsigned int previousxpos, unsigned int previousypos)
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