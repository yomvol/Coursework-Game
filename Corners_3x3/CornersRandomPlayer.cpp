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
	if (DidHop == false)
	{
		unsigned int* piecesCoords = this->board->FindPieces(this->tile);
		unsigned int arr[18];
		PiecesCoords = arr;
		for (int i = 0; i < 18; i++)
		{
			PiecesCoords[i] = *(piecesCoords + i);
		}
	}
	const int NumOfHypotheses = 10;
	int n = 0, counter = 0;
	Turn Turns[NumOfHypotheses];
	while (counter < NumOfHypotheses)
	{
		unsigned int startrow, startcol, endrow = 0, endcol = 0;
		if (DidHop == false)
		{
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
			for (int i = 0; i < counter; i++)
				if (Turns[i].endcol == endcol && Turns[i].endrow && Turns[i].startcol == startcol && Turns[i].startrow == startrow)
				{
					//counter++;
					continue;
				}
					
			int FieldDiff = CornersBoard::GetField(endcol, endrow) - CornersBoard::GetField(startcol, startrow); // Negative for whites
			// Positive for blacks
			double Correction;
			if (this->tile == Tile_White)
			{
				switch (FieldDiff)
				{
				case 0:
					Correction = 1.0;
					break;
				case -1:
					Correction = 1.25;
					break;
				case -2:
					Correction = 1.5;
					break;
				case -3:
					Correction = 1.75;
					break;
				case -4:
					Correction = 2.0;
					break;
				case -5:
					Correction = 2.0;
					break;
				case 1:
					Correction = 0.75;
					break;
				case 2:
					Correction = 0.5;
					break;
				case 3:
					Correction = 0.25;
					break;
				case 4:
					Correction = 0.25;
					break;
				case 5:
					Correction = 0.25;
					break;
				default:
					throw;
				}
			}
			else
			{
				switch (FieldDiff)
				{
				case 0:
					Correction = 1.0;
					break;
				case 1:
					Correction = 1.25;
					break;
				case 2:
					Correction = 1.5;
					break;
				case 3:
					Correction = 1.75;
					break;
				case 4:
					Correction = 2.0;
					break;
				case 5:
					Correction = 2.0;
					break;
				case -1:
					Correction = 0.75;
					break;
				case -2:
					Correction = 0.5;
					break;
				case -3:
					Correction = 0.25;
					break;
				case -4:
					Correction = 0.25;
					break;
				case -5:
					Correction = 0.25;
					break;
				default:
					throw;
				}
			}
			
			Turns[n].FlowCorrectionValue = int(100 * Correction);
			unsigned int adiffx = abs(int(endcol - startcol));
			unsigned int adiffy = abs(int(endrow - startrow));
			if (adiffy == 2 || adiffx == 2)
			{
				// + HOP BONUS
				Turns[n].FlowCorrectionValue += 50;
			}
			Turns[n].endcol = endcol;
			Turns[n].endrow = endrow;
			Turns[n].startcol = startcol;
			Turns[n].startrow = startrow;
			n++;
			counter++;
		}
	}
	unsigned int TotalWeight = 0;
	for (int j = 0; j < n; j++)
	{
		TotalWeight += Turns[j].FlowCorrectionValue;
	}
	if (TotalWeight == 0)
		return false;
	
	unsigned int RandomPick = rand() % TotalWeight + 1;
	unsigned int iter = 0;
	for (int i = 0; i < n; i++)
	{
		iter += Turns[i].FlowCorrectionValue;

		if (iter >= RandomPick)
		{
			unsigned int adiffx = abs(int(Turns[i].endcol - Turns[i].startcol));
			unsigned int adiffy = abs(int(Turns[i].endrow - Turns[i].startrow));
			this->board->SetTile(Turns[i].endcol, Turns[i].endrow, this->tile);
			this->board->SetTile(Turns[i].startcol, Turns[i].startrow, Tile_Empty);
			if (adiffy == 2 || adiffx == 2)
			{
				prevcol = Turns[i].endcol;
				prevrow = Turns[i].endrow;
				prevprevcol = Turns[i].startcol;
				prevprevrow = Turns[i].startrow;
				DidHop = true;
			}
			return true;
		}
	}
}
