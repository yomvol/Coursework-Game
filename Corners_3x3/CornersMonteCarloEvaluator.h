#pragma once
#include "CornersBoard.h"

class CornersMonteCarloEvaluator //Win: Black wins, White loses; Lose: White wins, Black loses
{
private:
	CornersBoard* board;
	int numGames;
	int numVictories;
	int numLosses;
	int numDraws;
	unsigned int startcol, startrow, endcol, endrow;
	Tile StartTurn;
	unsigned int NumWhiteTurns, NumBlackTurns;
	bool DidHop = false;;

public:
	CornersMonteCarloEvaluator(CornersBoard* board, int numIterations, Tile StartTurn, unsigned int startcol, unsigned int startrow, unsigned int endcol, unsigned int endrow, unsigned int NumWhiteTurns, unsigned int NumBlackTurns);
	~CornersMonteCarloEvaluator();
	void Evaluate();
	void EvaluateBoard();
	int GetVictories() { return numVictories; };
	int GetLosses() { return numLosses; };
	int GetDraws() { return numDraws; };
	unsigned int GetStartCol() { return startcol; };
	unsigned int GetStartRow() { return startrow; };
	unsigned int GetEndCol() { return endcol; };
	unsigned int GetEndRow() { return endrow; };
};

