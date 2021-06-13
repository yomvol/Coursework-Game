#include "pch.h"
#include "CornersHumanPlayer.h"

CornersHumanPlayer::CornersHumanPlayer()
{}

CornersHumanPlayer::~CornersHumanPlayer()
{}

bool CornersHumanPlayer::MakeMove(unsigned int startrow, unsigned int startcol, unsigned int endrow, unsigned int endcol, unsigned int numWhiteTurns, unsigned int numBlackTurns)
{
	unsigned int StartRow, StartCol, EndRow, EndCol;
	if (this->DidHop == false)
	{
		StartRow = startrow;
		StartCol = startcol;
		EndRow = endrow;
		EndCol = endcol;
	}
	else
	{
		StartCol = prevcol;
		StartRow = prevrow;
		EndCol = endcol;
		EndRow = endrow;
	}

	if (this->board->CheckLegal(StartCol, StartRow, EndCol, EndRow))
	{
		unsigned int adiffx = abs(int(EndCol - StartCol));
		unsigned int adiffy = abs(int(EndRow - StartRow));
		if (DidHop == true && !(adiffy == 2 || adiffx == 2))
		{
			return false;
		}
		this->board->SetTile(EndCol, EndRow, this->tile);
		this->board->SetTile(StartCol, StartRow, Tile_Empty);
		if (adiffy == 2 || adiffx == 2)
		{
			prevcol = EndCol;
			prevrow = EndRow;
			DidHop = true;
		}
		return true;
	}
	
	return false;
	
}