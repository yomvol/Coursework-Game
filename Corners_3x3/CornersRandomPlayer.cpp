#include "pch.h"
#include "CornersRandomPlayer.h"

CornersRandomPlayer::CornersRandomPlayer()
{}

CornersRandomPlayer::~CornersRandomPlayer()
{}

int IRand(int a, int b) // Returns a random integer in sequence [a; b]
{
	return (rand() % (b - a + 1)) + a; // a + {0; b - a}
}

bool CornersRandomPlayer::MakeMove(unsigned int NumWhiteTurns, unsigned int NumBlackTurns)
{
	unsigned int startrow, startcol, endrow = 0, endcol = 0;
	if (DidHop == false)
	{
		this->PiecesCoords = this->board->FindPieces(this->tile);
		unsigned int Picking = rand() % 9;
		startcol = PiecesCoords[2 * Picking];
		startrow = PiecesCoords[2 * Picking + 1];

		short CoinFlip = rand() % 2;
		if (CoinFlip == 0)
		{
			endrow = startrow;
			do
				endcol = IRand(startcol - 2, startcol + 2);
			while (endcol == startcol);
		}
		else
		{
			endcol = startcol;
			do
				endrow = IRand(startrow - 2, startrow + 2);
			while (endrow == startrow);
		}
	}
	else
	{
		startcol = prevcol;
		startrow = prevrow;
		int code = this->board->GetLegalHop(startcol, startrow, prevprevcol, prevprevrow);
		switch (code)
		{
		case 0:
			endrow = startrow + 2;
			endcol = startcol;
			break;
		case 1:
			endrow = startrow;
			endcol = startcol - 2;
			break;
		case 2:
			endrow = startrow - 2;
			endcol = startcol;
			break;
		case 3:
			endrow = startrow;
			endcol = startcol + 2;
			break;
		case -1:
			this->IsPassingTurn = true;
			return true;
		}
	}
	

	if (this->board->CheckLegal(startcol, startrow, endcol, endrow))
	{
		unsigned int adiffx = abs(int(endcol - startcol));
		unsigned int adiffy = abs(int(endrow - startrow));
		this->board->SetTile(endcol, endrow, this->tile);
		this->board->SetTile(startcol, startrow, Tile_Empty);
		if (adiffy == 2 || adiffx == 2)
		{
			prevcol = endcol;
			prevrow = endrow;
			prevprevcol = startcol;
			prevprevrow = startrow;
			DidHop = true;
		}
		return true;
	}
	return false;
}