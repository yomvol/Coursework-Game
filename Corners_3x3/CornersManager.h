#pragma once
#include "CornersBoard.h"

class CornersManager
{
private:
	CornersBoard* board;
	bool GameFinished = false;

public:
	CornersManager();
	virtual ~CornersManager();
	void ShowBoard();
	void MakeMove();
	bool IsGameFinished();

};

