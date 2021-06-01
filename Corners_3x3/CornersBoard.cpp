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

