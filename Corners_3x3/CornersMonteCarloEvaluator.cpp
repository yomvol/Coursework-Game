#include "pch.h"
#include "CornersMonteCarloEvaluator.h"
#include "CornersRandomPlayer.h"

CornersMonteCarloEvaluator::CornersMonteCarloEvaluator(CornersBoard* board, int numIterations, Tile StartTurn, unsigned int startcol, unsigned int startrow, unsigned int endcol, unsigned int endrow, unsigned int NumWhiteTurns, unsigned int NumBlackTurns)
{
	this->board = board;
	this->numGames = numIterations;
	this->numDraws = 0;
	this->numLosses = 0;
	this->numVictories = 0;
	this->startcol = startcol;
	this->startrow = startrow;
	this->endrow = endrow;
	this->endcol = endcol;
	this->StartTurn = StartTurn;
	this->NumWhiteTurns = NumWhiteTurns;
	this->NumBlackTurns = NumBlackTurns;

	unsigned int adiffy = abs(int(endcol - startcol));
	unsigned int adiffx = abs(int(endrow - startrow));
	if (adiffy == 2 || adiffx == 2)
	{
		this->DidHop = true;
	}
}

CornersMonteCarloEvaluator::~CornersMonteCarloEvaluator()
{}

void CornersMonteCarloEvaluator::EvaluateBoard()
{
	CornersBoard* b = new CornersBoard(this->board);
	CornersRandomPlayer* player1 = new CornersRandomPlayer();
	CornersRandomPlayer* player2 = new CornersRandomPlayer();
	CornersRandomPlayer* currentPlayer;
	bool GameFinished = false;
	unsigned int WhiteTurns = NumWhiteTurns;
	unsigned int BlackTurns = NumBlackTurns;

	player1->SetupPlayer("RandomWhite", Tile_White);
	player2->SetupPlayer("RandomBlack", Tile_Black);
	player1->SetBoard(b);
	player2->SetBoard(b);
	if (DidHop == false)
	{
		currentPlayer = (StartTurn == Tile_White) ? player1 : player2;
	}
	else
	{
		currentPlayer = (StartTurn == Tile_White) ? player2 : player1; // If we did hop, we chain turns
		if (StartTurn == Tile_White)
		{
			BlackTurns--;
		}
		if (StartTurn == Tile_Black)
		{
			WhiteTurns--;
		}
		currentPlayer->SetDidHop(true);
		currentPlayer->SetPrevCol(endcol);
		currentPlayer->SetPrevRow(endrow);
		currentPlayer->SetPrevPrevCol(startcol);
		currentPlayer->SetPrevPrevRow(startrow);
	}
	

	while (!GameFinished)
	{
		if (BlackTurns > 15 && BlackTurns == WhiteTurns)
		{
			unsigned int WhiteProgress = b->WhitesOnBlackBase();
			unsigned int BlackProgress = b->BlacksOnWhiteBase();

			if (BlackTurns == 80)
			{
				if (WhiteProgress > BlackProgress)
				{
					numLosses++;
					GameFinished = true;
					continue;
				}
				else if (WhiteProgress == BlackProgress)
				{
					numDraws++;
					GameFinished = true;
					continue;
				}
				else
				{
					numVictories++;
					GameFinished = true;
					continue;
				}
			}
			else
			{
				if (WhiteProgress == 9)
				{
					numLosses++;
					GameFinished = true;
					continue;
				}
				if (BlackProgress == 9)
				{
					numVictories++;
					GameFinished = true;
					continue;
				}
			}
		}
		while (!currentPlayer->MakeMove(0, 0)) //Arguments are passed for compapability and have no meaning
		{} // If MakeMove returns false, it means that a random turn wasn`t doable
		// Check for consequential turns
		if (currentPlayer->GetDidHop() == false)
		{
			if (currentPlayer == player1)
				WhiteTurns++;
			else
				BlackTurns++;
			currentPlayer = (currentPlayer == player1) ? player2 : player1;
		}
		else if (currentPlayer->GetIsPassingTurn() == true)
		{
			if (currentPlayer == player1)
				WhiteTurns++;
			else
				BlackTurns++;
			currentPlayer->SetDidHop(false);
			currentPlayer->SetIsPassingTurn(false);
			currentPlayer = (currentPlayer == player1) ? player2 : player1;
		}
	}

	delete b;
	delete player1;
	delete player2;
}

void CornersMonteCarloEvaluator::Evaluate()
{
	for (int i = 0; i < numGames; i++)
		EvaluateBoard();
}