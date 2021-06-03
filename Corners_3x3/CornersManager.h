#pragma once
#include "CornersBoard.h"
#include "CornersPlayer.h"

class CornersManager
{
private:
	CornersBoard* board;
	bool GameFinished = false;
	CornersPlayer* player1;
	CornersPlayer* player2;
	CornersPlayer* currentPlayer;

public:
	CornersManager();
	virtual ~CornersManager();
	void ShowBoard();
	void MakeMove();
	bool IsGameFinished();

};

