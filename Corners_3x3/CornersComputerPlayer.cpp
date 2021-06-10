#include "pch.h"
#include "CornersComputerPlayer.h"
#include "CornersMonteCarloEvaluator.h"

CornersComputerPlayer::CornersComputerPlayer()
{}

void CornersComputerPlayer::SetBoard(CornersBoard* board)
{
	this->board = board;
	unsigned int* piecesCoords = this->board->FindPieces(this->tile);
	PiecesCoords = new unsigned int[18]; //Lives until destroyed deliberately
	for (int i = 0; i < 18; i++)
	{
		PiecesCoords[i] = *(piecesCoords + i);
	}
}

CornersComputerPlayer::~CornersComputerPlayer()
{
	delete[] PiecesCoords;
	PiecesCoords = nullptr;
}

bool CornersComputerPlayer::MakeMove(unsigned int numWhiteTurns, unsigned int numBlackTurns)
{
	int startrow, startcol, endrow, endcol;
	vector<CornersMonteCarloEvaluator*> evaluators;
	if (this->DidHop == true)
	{
		startcol = prevcol;
		startrow = prevrow;
		// Two possible horizontal moves + two possible vertical moves
		endrow = startrow;
		endcol = startcol - 2;
		if (this->board->CheckLegal(startcol, startrow, endcol, endrow) && !(endcol == prevprevcol && endrow == prevprevrow))
		{
			this->board->SetTile(endcol, endrow, this->tile); //Make this turn, evaluate the outcome and undo the turn
			this->board->SetTile(startcol, startrow, Tile_Empty); //Jump and pass
			if (this->tile == Tile_White)
			{
				evaluators.push_back(new CornersMonteCarloEvaluator(this->board, NumOfGames, Tile_Black, startcol, startrow, endcol, endrow, numWhiteTurns + 1, numBlackTurns));
			}
			if (this->tile == Tile_Black)
			{
				evaluators.push_back(new CornersMonteCarloEvaluator(this->board, NumOfGames, Tile_White, startcol, startrow, endcol, endrow, numWhiteTurns, numBlackTurns + 1));
			}
			this->board->SetTile(endcol, endrow, Tile_Empty);
			this->board->SetTile(startcol, startrow, this->tile);
		}
		endcol = startcol + 2;
		if (this->board->CheckLegal(startcol, startrow, endcol, endrow) && !(endcol == prevprevcol && endrow == prevprevrow))
		{
			this->board->SetTile(endcol, endrow, this->tile); //Make this turn, evaluate the outcome and undo the turn
			this->board->SetTile(startcol, startrow, Tile_Empty);
			if (this->tile == Tile_White)
			{
				evaluators.push_back(new CornersMonteCarloEvaluator(this->board, NumOfGames, Tile_Black, startcol, startrow, endcol, endrow, numWhiteTurns + 1, numBlackTurns));
			}
			if (this->tile == Tile_Black)
			{
				evaluators.push_back(new CornersMonteCarloEvaluator(this->board, NumOfGames, Tile_White, startcol, startrow, endcol, endrow, numWhiteTurns, numBlackTurns + 1));
			}
			this->board->SetTile(endcol, endrow, Tile_Empty);
			this->board->SetTile(startcol, startrow, this->tile);
		}
		endcol = startcol;
		endrow = startrow - 2;
		if (this->board->CheckLegal(startcol, startrow, endcol, endrow) && !(endcol == prevprevcol && endrow == prevprevrow))
		{
			this->board->SetTile(endcol, endrow, this->tile); //Make this turn, evaluate the outcome and undo the turn
			this->board->SetTile(startcol, startrow, Tile_Empty);
			if (this->tile == Tile_White)
			{
				evaluators.push_back(new CornersMonteCarloEvaluator(this->board, NumOfGames, Tile_Black, startcol, startrow, endcol, endrow, numWhiteTurns + 1, numBlackTurns));
			}
			if (this->tile == Tile_Black)
			{
				evaluators.push_back(new CornersMonteCarloEvaluator(this->board, NumOfGames, Tile_White, startcol, startrow, endcol, endrow, numWhiteTurns, numBlackTurns + 1));
			}
			this->board->SetTile(endcol, endrow, Tile_Empty);
			this->board->SetTile(startcol, startrow, this->tile);
		}
		endrow = startrow + 2;
		if (this->board->CheckLegal(startcol, startrow, endcol, endrow) && !(endcol == prevprevcol && endrow == prevprevrow))
		{
			this->board->SetTile(endcol, endrow, this->tile); //Make this turn, evaluate the outcome and undo the turn
			this->board->SetTile(startcol, startrow, Tile_Empty);
			if (this->tile == Tile_White)
			{
				evaluators.push_back(new CornersMonteCarloEvaluator(this->board, NumOfGames, Tile_Black, startcol, startrow, endcol, endrow, numWhiteTurns + 1, numBlackTurns));
			}
			if (this->tile == Tile_Black)
			{
				evaluators.push_back(new CornersMonteCarloEvaluator(this->board, NumOfGames, Tile_White, startcol, startrow, endcol, endrow, numWhiteTurns, numBlackTurns + 1));
			}
			this->board->SetTile(endcol, endrow, Tile_Empty);
			this->board->SetTile(startcol, startrow, this->tile);
		}
		if (evaluators.size() == 0)
		{
			this->IsPassingTurn = true;
			prevprevcol = 10;
			prevprevrow = 10;
			return true;
		}
	}
	else
	{
		for (int Picking = 0; Picking < 9; Picking++) // 0, 1, ..., 8 - For every its piece
		{
			startcol = PiecesCoords[2 * Picking];
			startrow = PiecesCoords[2 * Picking + 1];
			endrow = startrow;
			for (int i = startcol - 2; i < startcol + 3; i++) // All possible horizontal moves
			{
				endcol = i;
				if (endcol == startcol)
					continue;
				if (this->board->CheckLegal(startcol, startrow, endcol, endrow))
				{
					this->board->SetTile(endcol, endrow, this->tile); //Make this turn, evaluate the outcome and undo the turn
					this->board->SetTile(startcol, startrow, Tile_Empty);
					if (this->tile == Tile_White)
					{
						evaluators.push_back(new CornersMonteCarloEvaluator(this->board, NumOfGames, Tile_Black, startcol, startrow, endcol, endrow, numWhiteTurns + 1, numBlackTurns));
					}
					if (this->tile == Tile_Black)
					{
						evaluators.push_back(new CornersMonteCarloEvaluator(this->board, NumOfGames, Tile_White, startcol, startrow, endcol, endrow, numWhiteTurns, numBlackTurns + 1));
					}
					this->board->SetTile(endcol, endrow, Tile_Empty);
					this->board->SetTile(startcol, startrow, this->tile);
				}
			}

			endcol = startcol;
			for (int j = startrow - 2; j < startrow + 3; j++) //All possible vertical moves
			{
				endrow = j;
				if (endrow == startrow)
					continue;
				if (this->board->CheckLegal(startcol, startrow, endcol, endrow))
				{
					this->board->SetTile(endcol, endrow, this->tile); //Make this turn, evaluate the outcome and undo the turn
					this->board->SetTile(startcol, startrow, Tile_Empty);
					if (this->tile == Tile_White)
					{
						evaluators.push_back(new CornersMonteCarloEvaluator(this->board, NumOfGames, Tile_Black, startcol, startrow, endcol, endrow, numWhiteTurns + 1, numBlackTurns));
					}
					if (this->tile == Tile_Black)
					{
						evaluators.push_back(new CornersMonteCarloEvaluator(this->board, NumOfGames, Tile_White, startcol, startrow, endcol, endrow, numWhiteTurns, numBlackTurns + 1));
					}
					this->board->SetTile(endcol, endrow, Tile_Empty);
					this->board->SetTile(startcol, startrow, this->tile);
				}
			}
		}
	}
	

	for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); evaluator++)
		(*evaluator)->Evaluate();

	int biggestVictories = -1;

	for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); evaluator++)
		if (this->tile == Tile_Black)
		{
			if ((*evaluator)->GetVictories() > biggestVictories)
				biggestVictories = (*evaluator)->GetVictories();
		}
		else
		{
			if ((*evaluator)->GetLosses() > biggestVictories)
				biggestVictories = (*evaluator)->GetLosses();
		}

	vector<CornersMonteCarloEvaluator*> biggestWinEvaluators;
	for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); evaluator++)
	{
		int numVictories;
		if (this->tile == Tile_Black)
			numVictories = (*evaluator)->GetVictories();
		else
			numVictories = (*evaluator)->GetLosses();
		if (numVictories == biggestVictories)
			biggestWinEvaluators.push_back((*evaluator));
	}
	CornersMonteCarloEvaluator* BestTurn = biggestWinEvaluators[0];
	this->board->SetTile(BestTurn->GetEndCol(), BestTurn->GetEndRow(), this->tile); //Make the turn stored in biggestWinEvaluators[0]
	this->board->SetTile(BestTurn->GetStartCol(), BestTurn->GetStartRow(), Tile_Empty);
	unsigned int Picked;
	for (int Picked = 0; Picked < 9; Picked++) // Updating our map
	{
		if (PiecesCoords[Picked * 2] == BestTurn->GetStartCol() && PiecesCoords[Picked * 2 + 1] == BestTurn->GetStartRow())
		{
			PiecesCoords[Picked * 2] = BestTurn->GetEndCol();
			PiecesCoords[Picked * 2 + 1] = BestTurn->GetEndRow();
			break;
		}
	}

	unsigned int adiffy = abs(int(BestTurn->GetEndCol() - BestTurn->GetStartCol()));
	unsigned int adiffx = abs(int(BestTurn->GetEndRow() - BestTurn->GetStartRow()));
	if (DidHop == true && !(adiffy == 2 || adiffx == 2))
	{
		throw;
	}
	if (adiffy == 2 || adiffx == 2)
	{
		this->prevcol = BestTurn->GetEndCol();
		this->prevrow = BestTurn->GetEndRow();
		this->prevprevcol = BestTurn->GetStartCol();
		this->prevprevrow = BestTurn->GetStartRow();
		this->DidHop = true;
	}

	for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); evaluator++)
		delete (*evaluator);
	evaluators.clear();
	biggestWinEvaluators.clear();
	BestTurn = nullptr;
	cout << endl;

	return true;
}